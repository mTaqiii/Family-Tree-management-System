#include "FamilyTreeController.h"
#include "../core/Relationships.h"
#include "../core/XmlExporter.h"
#include "../core/XmlImporter.h"
#include <QPointF>
#include <QSet>
#include <QPair>
#include <algorithm>
#include <QDebug>
#include <QFile>
#include <QUrl>

namespace
{
    Gender parseGender(const QString& gender)
    {
        return gender.toLower() == "female" ? Gender::Female : Gender::Male;
    }
}

FamilyTreeController::FamilyTreeController(QObject* parent)
    : QObject(parent),
      m_forest(new FamilyForest(this)),
      m_treesModel(new PersonListModel(this)),
      m_searchResultsModel(new PersonListModel(this)),
      m_treeLayoutModel(new TreeLayoutModel(this))
{
}

void FamilyTreeController::loadTree(Person* root)
{
    if(root != m_activeRoot)
        m_collapsedIds.clear();

    m_activeRoot = root;

    QSet<int> excludedIds;

    if(m_timelineEnabled)
    {
        for(Person* p : m_forest->allPeople())
        {
            if(p->birthYear() > 0 && p->birthYear() > m_timelineYear)
                excludedIds.insert(p->id());
        }
    }

    QList<TreeLayoutEngine::Placement> placements = TreeLayoutEngine::layout(root, m_collapsedIds, excludedIds);
    m_treeLayoutModel->setPlacements(placements);

    m_visiblePeople.clear();
    for(const TreeLayoutEngine::Placement& p : placements)
        m_visiblePeople.insert(p.person);

    QHash<Person*, QPointF> positionByPerson;
    for(const TreeLayoutEngine::Placement& p : placements)
        positionByPerson[p.person] = QPointF(p.x, p.y);

    QVariantList edges;
    QSet<Person*> visited;
    QSet<QPair<Person*, Person*>> marriagesDrawn;

    for(const TreeLayoutEngine::Placement& p : placements)
    {
        Person* person = p.person;

        if(!positionByPerson.contains(person))
            continue;

        QPointF from = positionByPerson.value(person);

        // Parent -> child lines (skipped entirely while collapsed,
        // since the children aren't part of this layout at all).
        for(Person* child : person->children())
        {
            if(!positionByPerson.contains(child))
                continue;

            QPointF to = positionByPerson.value(child);

            QVariantMap edge;
            edge["type"] = "parent-child";
            edge["x1"] = from.x();
            edge["y1"] = from.y();
            edge["x2"] = to.x();
            edge["y2"] = to.y();
            edges.append(edge);
        }

        // Marriage line, drawn once per couple.
        Person* spouse = person->spouse();

        if(spouse != nullptr && positionByPerson.contains(spouse))
        {
            Person* a = person < spouse ? person : spouse;
            Person* b = person < spouse ? spouse : person;
            QPair<Person*, Person*> key(a, b);

            if(!marriagesDrawn.contains(key))
            {
                marriagesDrawn.insert(key);

                QPointF to = positionByPerson.value(spouse);

                QVariantMap edge;
                edge["type"] = "marriage";
                edge["x1"] = from.x();
                edge["y1"] = from.y();
                edge["x2"] = to.x();
                edge["y2"] = to.y();
                edges.append(edge);
            }
        }
    }

    m_treeEdges = edges;

    if(placements.isEmpty())
    {
        m_treeBounds = QRectF();
    }
    else
    {
        double minX = placements.first().x, maxX = placements.first().x;
        double minY = placements.first().y, maxY = placements.first().y;

        for(const TreeLayoutEngine::Placement& p : placements)
        {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }

        // Pad by roughly one card's worth of space on every side so
        // nodes at the edge of the tree aren't flush against the view.
        const double pad = 140.0;
        m_treeBounds = QRectF(minX - pad, minY - pad,
                               (maxX - minX) + pad * 2,
                               (maxY - minY) + pad * 2);
    }

    emit treeChanged();
}

void FamilyTreeController::toggleCollapsed(Person* person)
{
    if(person == nullptr)
        return;

    if(m_collapsedIds.contains(person->id()))
        m_collapsedIds.remove(person->id());
    else
        m_collapsedIds.insert(person->id());

    loadTree(m_activeRoot);
}

void FamilyTreeController::setTimelineEnabled(bool enabled)
{
    if(m_timelineEnabled == enabled)
        return;

    m_timelineEnabled = enabled;
    emit timelineChanged();

    if(m_activeRoot != nullptr)
        loadTree(m_activeRoot);
}

void FamilyTreeController::setTimelineYear(int year)
{
    if(m_timelineYear == year)
        return;

    m_timelineYear = year;
    emit timelineChanged();

    if(m_activeRoot != nullptr && m_timelineEnabled)
        loadTree(m_activeRoot);
}

QVariantMap FamilyTreeController::setYears(Person* person, int birthYear, int deathYear)
{
    if(person == nullptr)
        return makeResult(Result::PersonNull);

    person->setBirthYear(birthYear);
    person->setDeathYear(deathYear);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, person);
}

QVariantList FamilyTreeController::ancestryPath(Person* person) const
{
    QVariantList path;

    QList<Person*> chain;
    Person* current = person;
    int guard = 0;

    while(current != nullptr && guard < 200)
    {
        chain.prepend(current);

        if(current == m_activeRoot)
            break;

        Person* next = nullptr;

        if(current->father() != nullptr && m_visiblePeople.contains(current->father()))
            next = current->father();
        else if(current->mother() != nullptr && m_visiblePeople.contains(current->mother()))
            next = current->mother();

        if(next == nullptr)
            break;

        current = next;
        guard++;
    }

    for(Person* p : chain)
    {
        QVariantMap entry;
        entry["id"] = p->id();
        entry["name"] = p->name();
        entry["person"] = QVariant::fromValue(p);
        path.append(entry);
    }

    return path;
}

QVariantMap FamilyTreeController::makeResult(Result result, Person* person) const
{
    QVariantMap map;
    map["success"] = (result == Result::Success);
    map["message"] = QString::fromUtf8(resultMessage(result));
    map["person"] = QVariant::fromValue(person);
    return map;
}

void FamilyTreeController::refreshTreesModel()
{
    QList<Person*> roots;

    for(const FamilyTreeEntry& entry : m_forest->trees())
        roots.append(entry.root);

    m_treesModel->setPeople(roots);
}

void FamilyTreeController::refreshActiveTreeIfNeeded()
{
    if(m_activeRoot != nullptr)
        loadTree(m_activeRoot);
}

QVariantMap FamilyTreeController::registerRootPerson(const QString& name, const QString& gender)
{
    if(name.trimmed().isEmpty())
        return makeResult(Result::PersonNull);

    Person* root = m_forest->createPerson(name.trimmed(), parseGender(gender));
    m_forest->registerTree(root);

    refreshTreesModel();

    return makeResult(Result::Success, root);
}

QVariantMap FamilyTreeController::registerNewFather(Person* child, const QString& name)
{
    Person* father = m_forest->createPerson(name.trimmed(), Gender::Male);

    Result result = Relationships::validateFatherRegistration(child, father);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::establishParentRelationship(child, father);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, father);
}

QVariantMap FamilyTreeController::linkExistingFather(Person* child, Person* father)
{
    Result result = Relationships::validateFatherRegistration(child, father);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::establishParentRelationship(child, father);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, father);
}

QVariantMap FamilyTreeController::registerNewMother(Person* child, const QString& name)
{
    Person* mother = m_forest->createPerson(name.trimmed(), Gender::Female);

    Result result = Relationships::validateMotherRegistration(child, mother);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::establishParentRelationship(child, mother);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, mother);
}

QVariantMap FamilyTreeController::linkExistingMother(Person* child, Person* mother)
{
    Result result = Relationships::validateMotherRegistration(child, mother);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::establishParentRelationship(child, mother);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, mother);
}

QVariantMap FamilyTreeController::registerNewSpouse(Person* person, const QString& name)
{
    if(person == nullptr)
        return makeResult(Result::PersonNull);

    Gender spouseGender = (person->gender() == Gender::Male) ? Gender::Female : Gender::Male;
    Person* spouse = m_forest->createPerson(name.trimmed(), spouseGender);

    Result result = Relationships::validateSpouseRegistration(person, spouse);

    if(result != Result::Success)
        return makeResult(result);

    if(person->gender() == Gender::Male)
        Relationships::connectSpouses(person, spouse);
    else
        Relationships::connectSpouses(spouse, person);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, spouse);
}

QVariantMap FamilyTreeController::linkExistingSpouse(Person* person, Person* spouse)
{
    Result result = Relationships::validateSpouseRegistration(person, spouse);

    if(result != Result::Success)
        return makeResult(result);

    if(person->gender() == Gender::Male)
        Relationships::connectSpouses(person, spouse);
    else
        Relationships::connectSpouses(spouse, person);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, spouse);
}

QVariantMap FamilyTreeController::registerNewChild(Person* parent, const QString& name, const QString& gender)
{
    Person* child = m_forest->createPerson(name.trimmed(), parseGender(gender));

    Result result = Relationships::validateChildRegistration(parent, child);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::registerChildUnder(parent, child);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, child);
}

QVariantMap FamilyTreeController::linkExistingChild(Person* parent, Person* child)
{
    Result result = Relationships::validateChildRegistration(parent, child);

    if(result != Result::Success)
        return makeResult(result);

    Relationships::registerChildUnder(parent, child);

    refreshActiveTreeIfNeeded();

    return makeResult(Result::Success, child);
}

QVariantMap FamilyTreeController::unlinkFather(Person* child)
{
    Result result = Relationships::unlinkFather(child);
    refreshActiveTreeIfNeeded();
    return makeResult(result, child);
}

QVariantMap FamilyTreeController::unlinkMother(Person* child)
{
    Result result = Relationships::unlinkMother(child);
    refreshActiveTreeIfNeeded();
    return makeResult(result, child);
}

QVariantMap FamilyTreeController::exportTree(Person* root, const QString& filePath)
{
    QVariantMap result;

    if(root == nullptr)
    {
        result["success"] = false;
        result["message"] = "No family tree selected to export.";
        return result;
    }

    QString path = filePath;

    // A file:// URL comes straight from QML's FileDialog.selectedFile;
    // QFile needs a plain local path.
    if(path.startsWith("file://"))
    {
        QUrl url(path);
        path = url.toLocalFile();
    }

    QFile file(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        result["success"] = false;
        result["message"] = "Couldn't open \"" + path + "\" for writing.";
        return result;
    }

    bool ok = XmlExporter::exportTree(root, &file);
    file.close();

    result["success"] = ok;
    result["message"] = ok
        ? ("Exported " + root->name() + "'s family tree to " + path)
        : "Export failed -- the XML writer reported an error.";

    return result;
}

QVariantMap FamilyTreeController::importTree(const QString& filePath)
{
    QVariantMap result;

    QString path = filePath;

    if(path.startsWith("file://"))
    {
        QUrl url(path);
        path = url.toLocalFile();
    }

    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result["success"] = false;
        result["message"] = "Couldn't open \"" + path + "\" for reading.";
        return result;
    }

    QString errorMessage;
    Person* newRoot = XmlImporter::importTree(m_forest, &file, &errorMessage);
    file.close();

    if(newRoot == nullptr)
    {
        result["success"] = false;
        result["message"] = errorMessage.isEmpty() ? "Import failed." : errorMessage;
        return result;
    }

    refreshTreesModel();

    result["success"] = true;
    result["message"] = "Imported \"" + newRoot->name() + "\"'s family tree from " + path;
    result["person"] = QVariant::fromValue(newRoot);

    return result;
}

QVariantMap FamilyTreeController::renamePerson(Person* person, const QString& newName)
{
    if(person == nullptr)
        return makeResult(Result::PersonNull);

    if(newName.trimmed().isEmpty())
        return makeResult(Result::UnknownError);

    person->setName(newName.trimmed());

    return makeResult(Result::Success, person);
}

QVariantMap FamilyTreeController::markDeceased(Person* person)
{
    Result result = Relationships::markPersonDeceased(person);
    refreshActiveTreeIfNeeded();
    return makeResult(result, person);
}

QVariantMap FamilyTreeController::divorcePerson(Person* person)
{
    Result result = Relationships::divorcePerson(person);
    refreshActiveTreeIfNeeded();
    return makeResult(result, person);
}

int FamilyTreeController::searchByName(const QString& query)
{
    QList<Person*> results = m_forest->findByName(query);
    m_searchResultsModel->setPeople(results);
    return results.size();
}

Person* FamilyTreeController::searchById(int id)
{
    return m_forest->findById(id);
}
