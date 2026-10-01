#pragma once

#include <QSet>
#include <QList>

#include "Person.h"
#include "Types.h"

// Free functions containing exactly the relationship rules validated
// in the console version (Chapter 7 of the project documentation):
// one father, one mother, one active spouse, no duplicate children,
// no self-relationships, gender-consistent parent/spouse roles.
//
// Every function here is pure logic: it takes Person pointers, checks
// or mutates relationship pointers, and returns a Result. Nothing in
// this file prints, reads input, or knows that a GUI exists -- exactly
// the same separation of concerns the documentation (Chapter 5.6)
// argued for.
namespace Relationships
{
    inline bool isSamePerson(Person* a, Person* b)
    {
        return a != nullptr && a == b;
    }

    inline bool hasFather(Person* person)
    {
        return person != nullptr && person->father() != nullptr;
    }

    inline bool hasMother(Person* person)
    {
        return person != nullptr && person->mother() != nullptr;
    }

    inline bool hasSpouse(Person* person)
    {
        return person != nullptr && person->spouse() != nullptr;
    }

    inline bool childAlreadyExists(Person* parent, Person* child)
    {
        return parent != nullptr && parent->children().contains(child);
    }

    // True if `candidate` is anywhere above `person` in the family
    // tree (parent, grandparent, ...). Used to stop a descendant
    // from being registered as their own ancestor's parent, and to
    // stop someone from marrying their own ancestor.
    inline bool isAncestorOf(Person* candidate, Person* person)
    {
        if(candidate == nullptr || person == nullptr)
            return false;

        QSet<Person*> visited;
        QList<Person*> queue;
        queue.append(person);

        while(!queue.isEmpty())
        {
            Person* current = queue.takeFirst();

            if(current == nullptr || visited.contains(current))
                continue;

            visited.insert(current);

            if(current->father() == candidate || current->mother() == candidate)
                return true;

            if(current->father() != nullptr)
                queue.append(current->father());

            if(current->mother() != nullptr)
                queue.append(current->mother());
        }

        return false;
    }

    // True if `candidate` is anywhere below `person` in the family
    // tree (child, grandchild, ...). The mirror image of
    // isAncestorOf -- kept separate (rather than just calling
    // isAncestorOf with arguments swapped) because callers read
    // more clearly asking the direction they actually mean.
    inline bool isDescendantOf(Person* candidate, Person* person)
    {
        return isAncestorOf(person, candidate);
    }

    // --- Parents ---------------------------------------------------

    inline Result validateFatherRegistration(Person* child, Person* father)
    {
        if(child == nullptr || father == nullptr)
            return Result::PersonNull;

        if(isSamePerson(child, father))
            return Result::SamePerson;

        if(father->status() == LifeStatus::Deceased)
            return Result::PersonDeceased;

        if(hasFather(child))
            return Result::AlreadyExists;

        if(father->gender() != Gender::Male)
            return Result::InvalidGender;

        // A descendant can't also be an ancestor -- e.g. child's own
        // grandchild can't be registered as child's father.
        if(isDescendantOf(father, child))
            return Result::CycleDetected;

        return Result::Success;
    }

    inline Result validateMotherRegistration(Person* child, Person* mother)
    {
        if(child == nullptr || mother == nullptr)
            return Result::PersonNull;

        if(isSamePerson(child, mother))
            return Result::SamePerson;

        if(mother->status() == LifeStatus::Deceased)
            return Result::PersonDeceased;

        if(hasMother(child))
            return Result::AlreadyExists;

        if(mother->gender() != Gender::Female)
            return Result::InvalidGender;

        if(isDescendantOf(mother, child))
            return Result::CycleDetected;

        return Result::Success;
    }

    // Links child <-> parent in both directions, and appends the
    // child into the parent's child list. Assumes validation already
    // passed -- mirrors establishParentRelationship() /
    // addChildToParent() from the console version.
    inline void establishParentRelationship(Person* child, Person* parent)
    {
        if(child == nullptr || parent == nullptr)
            return;

        if(parent->gender() == Gender::Male)
            child->setFather(parent);
        else
            child->setMother(parent);

        if(!childAlreadyExists(parent, child))
            parent->addChild(child);
    }

    // --- Spouse ------------------------------------------------------

    inline Result validateSpouseRegistration(Person* person, Person* spouse)
    {
        if(person == nullptr || spouse == nullptr)
            return Result::PersonNull;

        if(isSamePerson(person, spouse))
            return Result::SamePerson;

        if(person->status() == LifeStatus::Deceased)
            return Result::PersonDeceased;

        if(spouse->status() == LifeStatus::Deceased)
            return Result::PersonDeceased;

        if(hasSpouse(person))
            return Result::AlreadyExists;

        if(hasSpouse(spouse))
            return Result::AlreadyExists;

        if(person->gender() == Gender::Male && spouse->gender() != Gender::Female)
            return Result::InvalidGender;

        if(person->gender() == Gender::Female && spouse->gender() != Gender::Male)
            return Result::InvalidGender;

        if(isAncestorOf(spouse, person) || isDescendantOf(spouse, person))
            return Result::AncestorMarriage;

        return Result::Success;
    }

    inline Result connectSpouses(Person* husband, Person* wife)
    {
        if(husband == nullptr || wife == nullptr)
            return Result::PersonNull;

        if(isSamePerson(husband, wife))
            return Result::SamePerson;

        if(husband->gender() != Gender::Male)
            return Result::InvalidGender;

        if(wife->gender() != Gender::Female)
            return Result::InvalidGender;

        if(husband->spouse() != nullptr || wife->spouse() != nullptr)
            return Result::AlreadyExists;

        husband->setSpouse(wife);
        wife->setSpouse(husband);

        return Result::Success;
    }

    inline Result disconnectSpouses(Person* person)
    {
        if(person == nullptr)
            return Result::PersonNull;

        Person* spouse = person->spouse();

        if(spouse == nullptr)
            return Result::PersonNotFound;

        spouse->setSpouse(nullptr);
        person->setSpouse(nullptr);

        return Result::Success;
    }

    // --- Child -------------------------------------------------------

    inline Result validateChildRegistration(Person* parent, Person* child)
    {
        if(parent == nullptr || child == nullptr)
            return Result::PersonNull;

        if(isSamePerson(parent, child))
            return Result::SamePerson;

        if(childAlreadyExists(parent, child))
            return Result::DuplicateChild;

        if(isAncestorOf(child, parent))
            return Result::CycleDetected;

        return Result::Success;
    }

    // Registers a child under `parent`, and under parent's spouse too
    // if one exists -- mirrors the console version's automatic
    // dual-parent registration (Chapter 6.6 of the documentation).
    inline void registerChildUnder(Person* parent, Person* child)
    {
        if(parent == nullptr || child == nullptr)
            return;

        establishParentRelationship(child, parent);

        if(hasSpouse(parent))
            establishParentRelationship(child, parent->spouse());
    }

    // Removes a father/mother relationship without touching anything
    // else -- the child keeps their other parent, spouse, and
    // children exactly as they were. Used by the "Remove Relationship"
    // confirmation flow.
    inline Result unlinkFather(Person* child)
    {
        if(child == nullptr)
            return Result::PersonNull;

        Person* father = child->father();

        if(father == nullptr)
            return Result::PersonNotFound;

        QList<Person*> siblings = father->children();
        siblings.removeAll(child);
        father->setChildren(siblings);

        child->setFather(nullptr);

        return Result::Success;
    }

    inline Result unlinkMother(Person* child)
    {
        if(child == nullptr)
            return Result::PersonNull;

        Person* mother = child->mother();

        if(mother == nullptr)
            return Result::PersonNotFound;

        QList<Person*> siblings = mother->children();
        siblings.removeAll(child);
        mother->setChildren(siblings);

        child->setMother(nullptr);

        return Result::Success;
    }

    // --- Lifecycle -----------------------------------------------------

    inline Result markPersonDeceased(Person* person)
    {
        if(person == nullptr)
            return Result::PersonNull;

        if(person->status() == LifeStatus::Deceased)
            return Result::PersonDeceased;

        person->setStatus(LifeStatus::Deceased);

        return Result::Success;
    }

    inline Result divorcePerson(Person* person)
    {
        if(person == nullptr)
            return Result::PersonNull;

        if(!hasSpouse(person))
            return Result::PersonNotFound;

        return disconnectSpouses(person);
    }
}
