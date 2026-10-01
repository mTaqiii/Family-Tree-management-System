#include "FamilyForest.h"
#include <functional>

FamilyForest::FamilyForest(QObject* parent)
    : QObject(parent)
{
}

Person* FamilyForest::createPerson(const QString& name, Gender gender)
{
    auto person = std::make_unique<Person>(m_nextPersonId, name, gender, this);
    m_nextPersonId++;

    Person* raw = person.get();
    m_people.push_back(std::move(person));

    return raw;
}

int FamilyForest::registerTree(Person* root)
{
    if(root == nullptr)
        return 0;

    FamilyTreeEntry entry;
    entry.treeId = m_nextTreeId;
    entry.root = root;

    m_nextTreeId++;
    m_trees.append(entry);

    return entry.treeId;
}

Person* FamilyForest::findById(int id) const
{
    if(id <= 0)
        return nullptr;

    Person* found = nullptr;

    // ID search walks the same father/mother/spouse/children graph as
    // name search, short-circuiting as soon as it finds a match.
    QList<Person*> visited;

    std::function<Person*(Person*)> walk = [&](Person* current) -> Person*
    {
        if(current == nullptr || current->visited)
            return nullptr;

        current->visited = true;
        visited.append(current);

        if(current->id() == id)
            return current;

        if(Person* r = walk(current->father())) return r;
        if(Person* r = walk(current->mother())) return r;
        if(Person* r = walk(current->spouse())) return r;

        for(Person* child : current->children())
        {
            if(Person* r = walk(child))
                return r;
        }

        return nullptr;
    };

    for(const FamilyTreeEntry& entry : m_trees)
    {
        found = walk(entry.root);

        if(found != nullptr)
            break;
    }

    for(Person* p : visited)
        p->visited = false;

    return found;
}

QList<Person*> FamilyForest::findByName(const QString& query) const
{
    QString lowerQuery = query.toLower();

    QList<Person*> results;
    QList<Person*> visited;

    for(const FamilyTreeEntry& entry : m_trees)
        searchRecursive(entry.root, lowerQuery, results, visited);

    for(Person* p : visited)
        p->visited = false;

    return results;
}

void FamilyForest::searchRecursive(Person* current,
                                    const QString& lowerQuery,
                                    QList<Person*>& results,
                                    QList<Person*>& visitedList) const
{
    if(current == nullptr || current->visited)
        return;

    current->visited = true;
    visitedList.append(current);

    if(current->name().toLower() == lowerQuery && !results.contains(current))
        results.append(current);

    searchRecursive(current->father(), lowerQuery, results, visitedList);
    searchRecursive(current->mother(), lowerQuery, results, visitedList);
    searchRecursive(current->spouse(), lowerQuery, results, visitedList);

    for(Person* child : current->children())
        searchRecursive(child, lowerQuery, results, visitedList);
}

QList<Person*> FamilyForest::allPeople() const
{
    QList<Person*> list;

    for(const auto& p : m_people)
        list.append(p.get());

    return list;
}
