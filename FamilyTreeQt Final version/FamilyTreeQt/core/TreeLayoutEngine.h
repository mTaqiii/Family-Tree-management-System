#pragma once

#include <QList>
#include <QSet>
#include <QHash>
#include <QPointF>

#include "Person.h"

// Computes a 2D layout for an entire family tree, so QML only has to
// place a Repeater at pre-computed coordinates -- no layout algorithm
// lives in QML. This mirrors the advice given during planning: family
// tree auto-layout is a real (if small) algorithm, worth doing once
// in C++ rather than re-deriving it in every view.
//
// Rules encoded here:
//   - y = generation depth from the tree's root (root is 0, each
//     child level is +1).
//   - A person and their spouse are treated as one visual "couple
//     unit": they sit side by side (spouse offset +COUPLE_GAP) and
//     share a single x-slot for the purposes of centering their
//     children underneath them.
//   - A childless person/couple consumes exactly one leaf slot;
//     a person/couple with children is centered above the average
//     x of their own children -- the standard recursive tree-layout
//     approach, adapted for couples.
class TreeLayoutEngine
{
public:

    struct Placement
    {
        Person* person = nullptr;
        qreal x = 0;
        qreal y = 0;
        bool hasChildren = false;
        bool collapsed = false;
    };

    // Lays out every person reachable *downward* from `root` (root,
    // root's spouse, their children, grandchildren, ...). Does not
    // walk upward to root's own parents -- consistent with "View
    // Family Tree" always being rooted at one chosen tree, exactly
    // like the console version's printFamilyTree().
    //
    // `collapsedIds` holds the ids of people whose own children
    // should not be descended into or placed -- their branch is
    // still shown as a single node, just without its subtree, so
    // large families don't have to be fully expanded at once.
    //
    // `excludedIds` holds the ids of people who should not appear
    // in the layout at all (Timeline Mode: not yet born as of the
    // selected year) -- unlike a collapsed person, an excluded
    // person's subtree is also excluded entirely, since a person
    // can't have visible descendants before they themselves exist.
    static QList<Placement> layout(Person* root,
                                    const QSet<int>& collapsedIds = {},
                                    const QSet<int>& excludedIds = {})
    {
        QList<Placement> result;

        if(root == nullptr || excludedIds.contains(root->id()))
            return result;

        QSet<Person*> visited;
        QHash<Person*, QPointF> positions;
        qreal nextLeafSlot = 0;

        place(root, 0, visited, positions, nextLeafSlot, collapsedIds, excludedIds);

        for(auto it = positions.constBegin(); it != positions.constEnd(); ++it)
        {
            Placement p;
            p.person = it.key();
            p.x = it.value().x() * HORIZONTAL_SPACING;
            p.y = it.value().y() * VERTICAL_SPACING;
            p.hasChildren = !it.key()->children().isEmpty();
            p.collapsed = collapsedIds.contains(it.key()->id());
            result.append(p);
        }

        return result;
    }

    static constexpr qreal HORIZONTAL_SPACING = 190.0;
    static constexpr qreal VERTICAL_SPACING = 170.0;
    static constexpr qreal COUPLE_GAP = 0.55;

private:

    // Returns the x-slot (pre-spacing) of `person`'s couple unit,
    // and fills in `positions` for person (+ spouse, if any) and
    // everything below them.
    static qreal place(Person* person,
                        int level,
                        QSet<Person*>& visited,
                        QHash<Person*, QPointF>& positions,
                        qreal& nextLeafSlot,
                        const QSet<int>& collapsedIds,
                        const QSet<int>& excludedIds)
    {
        if(person == nullptr || visited.contains(person))
            return positions.value(person).x();

        visited.insert(person);

        Person* partner = person->spouse();
        bool hasPartner = (partner != nullptr &&
                            !visited.contains(partner) &&
                            !excludedIds.contains(partner->id()));

        if(hasPartner)
            visited.insert(partner);

        // A couple's children are the same set from either side
        // (Relationships::registerChildUnder appends the child to
        // both parents), so person's own list is already complete.
        // A collapsed node is treated as childless for layout
        // purposes -- its subtree simply isn't placed. Excluded
        // children (not yet born, per Timeline Mode) are filtered
        // out the same way.
        bool isCollapsed = collapsedIds.contains(person->id());
        QList<Person*> children;

        if(!isCollapsed)
        {
            for(Person* child : person->children())
            {
                if(!excludedIds.contains(child->id()))
                    children.append(child);
            }
        }

        qreal centerX;

        if(children.isEmpty())
        {
            centerX = nextLeafSlot;
            nextLeafSlot += 1.0;
        }
        else
        {
            qreal sum = 0;
            int count = 0;

            for(Person* child : children)
            {
                if(visited.contains(child))
                    continue;

                sum += place(child, level + 1, visited, positions, nextLeafSlot, collapsedIds, excludedIds);
                count++;
            }

            centerX = (count > 0) ? (sum / count) : nextLeafSlot++;
        }

        if(hasPartner)
        {
            positions[person] = QPointF(centerX - COUPLE_GAP, level);
            positions[partner] = QPointF(centerX + COUPLE_GAP, level);
        }
        else
        {
            positions[person] = QPointF(centerX, level);
        }

        return centerX;
    }
};
