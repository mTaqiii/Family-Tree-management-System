#pragma once

#include <QObject>
#include <QList>
#include <memory>
#include <vector>

#include "Person.h"
#include "Types.h"

// A single registered family line: an ID plus its root Person.
// Equivalent to `struct FamilyTree` (treeID + root + next) in the
// console version, minus the manual linked-list plumbing -- that's
// just QList<FamilyTreeEntry> below.
struct FamilyTreeEntry
{
    int treeId = 0;
    Person* root = nullptr;
};

// Owns every Person ever created and every tree root registered.
// This replaces the two console-app globals `familyForestHead` and
// `nextPersonID`/`nextTreeID` with one object that has a clear
// lifetime (owned by the app, destroyed on exit) instead of raw
// global pointers.
class FamilyForest : public QObject
{
    Q_OBJECT

public:

    explicit FamilyForest(QObject* parent = nullptr);

    // Creates and takes ownership of a new Person. Does not attach
    // it to any tree by itself -- see registerTree().
    Person* createPerson(const QString& name, Gender gender);

    // Registers `root` as the entry point of a brand-new tree.
    // Mirrors createTreeForPerson() from the console version.
    int registerTree(Person* root);

    QList<FamilyTreeEntry> trees() const { return m_trees; }

    // --- Search --------------------------------------------------------
    // Both searches walk the *full connected graph* (father, mother,
    // spouse, children) from every tree root, not just downward --
    // this is the fix from the console version that makes a person
    // findable even when they were only ever linked in (e.g. a spouse
    // or parent who was never given their own tree).

    Person* findById(int id) const;
    QList<Person*> findByName(const QString& query) const;

    QList<Person*> allPeople() const;

private:

    void searchRecursive(Person* current,
                          const QString& lowerQuery,
                          QList<Person*>& results,
                          QList<Person*>& visitedList) const;

    std::vector<std::unique_ptr<Person>> m_people;
    QList<FamilyTreeEntry> m_trees;

    int m_nextPersonId = 1;
    int m_nextTreeId = 1;
};
