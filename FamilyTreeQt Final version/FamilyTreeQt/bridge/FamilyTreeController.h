#pragma once

#include <QObject>
#include <QVariantMap>
#include <QRectF>
#include <QSet>
#include <qqml.h>

#include "../core/FamilyForest.h"
#include "PersonListModel.h"
#include "TreeLayoutModel.h"

// The single entry point QML talks to. Every method here does the
// same three things the console menu functions used to do -- collect
// arguments, call into Relationships:: for validation/mutation, and
// report a Result -- just without any cout/cin in between.
//
// QML never touches FamilyForest or Relationships directly; it only
// ever sees this controller, exactly the way the console app's menu
// functions were the only thing allowed to call the validate/connect
// functions directly.
class FamilyTreeController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(PersonListModel* trees READ treesModel CONSTANT)
    Q_PROPERTY(PersonListModel* searchResults READ searchResultsModel CONSTANT)
    Q_PROPERTY(TreeLayoutModel* treeLayout READ treeLayoutModel CONSTANT)
    Q_PROPERTY(int totalPeople READ totalPeople NOTIFY treeChanged)
    Q_PROPERTY(QVariantList treeEdges READ treeEdges NOTIFY treeChanged)
    Q_PROPERTY(Person* activeRoot READ activeRoot NOTIFY treeChanged)
    Q_PROPERTY(QRectF treeBounds READ treeBounds NOTIFY treeChanged)
    Q_PROPERTY(bool timelineEnabled READ timelineEnabled WRITE setTimelineEnabled NOTIFY timelineChanged)
    Q_PROPERTY(int timelineYear READ timelineYear WRITE setTimelineYear NOTIFY timelineChanged)

public:

    explicit FamilyTreeController(QObject* parent = nullptr);

    PersonListModel* treesModel() const { return m_treesModel; }
    PersonListModel* searchResultsModel() const { return m_searchResultsModel; }
    TreeLayoutModel* treeLayoutModel() const { return m_treeLayoutModel; }
    int totalPeople() const { return m_forest->allPeople().size(); }
    QVariantList treeEdges() const { return m_treeEdges; }
    Person* activeRoot() const { return m_activeRoot; }
    QRectF treeBounds() const { return m_treeBounds; }

    bool timelineEnabled() const { return m_timelineEnabled; }
    void setTimelineEnabled(bool enabled);

    int timelineYear() const { return m_timelineYear; }
    void setTimelineYear(int year);

    // Records (optional) birth/death years for Timeline Mode. Either
    // can be passed as 0 to mean "not recorded" / "leave unset".
    Q_INVOKABLE QVariantMap setYears(Person* person, int birthYear, int deathYear);

    // Recomputes the layout for the tree rooted at `root` and
    // publishes it through treeLayout / treeEdges. Called whenever
    // the user opens "View Family Tree" or the tree changes shape
    // (a new child/spouse registered while it's open).
    Q_INVOKABLE void loadTree(Person* root);

    // Collapses/expands a person's subtree in the currently loaded
    // tree (large families shouldn't have to render fully expanded
    // at once). Re-runs the layout immediately.
    Q_INVOKABLE void toggleCollapsed(Person* person);

    // Path of ancestors from the active tree's root down to `person`,
    // following whichever parent is actually part of this tree --
    // used to drive breadcrumb navigation. Each entry is
    // {id, name, person}.
    Q_INVOKABLE QVariantList ancestryPath(Person* person) const;

    // --- Registration --------------------------------------------------
    // Every *Register* call returns {success: bool, message: string,
    // person: Person*} so QML can show an error toast on failure or
    // navigate straight to the new person on success, without needing
    // to know about the Result enum at all.

    Q_INVOKABLE QVariantMap registerRootPerson(const QString& name, const QString& gender);

    Q_INVOKABLE QVariantMap registerNewFather(Person* child, const QString& name);
    Q_INVOKABLE QVariantMap linkExistingFather(Person* child, Person* father);

    Q_INVOKABLE QVariantMap registerNewMother(Person* child, const QString& name);
    Q_INVOKABLE QVariantMap linkExistingMother(Person* child, Person* mother);

    Q_INVOKABLE QVariantMap registerNewSpouse(Person* person, const QString& name);
    Q_INVOKABLE QVariantMap linkExistingSpouse(Person* person, Person* spouse);

    Q_INVOKABLE QVariantMap registerNewChild(Person* parent, const QString& name, const QString& gender);
    Q_INVOKABLE QVariantMap linkExistingChild(Person* parent, Person* child);

    // --- Removing relationships (each is a confirmed, deliberate
    // action from the UI -- these don't delete anyone, just sever
    // one link) -------------------------------------------------------

    Q_INVOKABLE QVariantMap unlinkFather(Person* child);
    Q_INVOKABLE QVariantMap unlinkMother(Person* child);

    // --- Export --------------------------------------------------------

    // Writes the tree rooted at `root` to `filePath` as XML. Returns
    // {success, message} -- filePath comes from a native save dialog
    // on the QML side, so this never has to prompt for anything itself.
    Q_INVOKABLE QVariantMap exportTree(Person* root, const QString& filePath);

    // Imports a previously exported XML file as a brand-new family
    // tree (never overwrites or merges into an existing one). On
    // success, {success, message, person} carries the new root so
    // QML can jump straight into viewing it.
    Q_INVOKABLE QVariantMap importTree(const QString& filePath);

    // --- Lifecycle -------------------------------------------------------

    Q_INVOKABLE QVariantMap renamePerson(Person* person, const QString& newName);
    Q_INVOKABLE QVariantMap markDeceased(Person* person);
    Q_INVOKABLE QVariantMap divorcePerson(Person* person);

    // --- Search ------------------------------------------------------------
    // Refreshes searchResults and also returns the count, so QML can
    // show "3 people found" without a second round trip.

    Q_INVOKABLE int searchByName(const QString& query);
    Q_INVOKABLE Person* searchById(int id);

signals:

    void treeChanged();
    void timelineChanged();

private:

    QVariantMap makeResult(Result result, Person* person = nullptr) const;
    void refreshTreesModel();
    void refreshActiveTreeIfNeeded();

    FamilyForest* m_forest;
    PersonListModel* m_treesModel;
    PersonListModel* m_searchResultsModel;
    TreeLayoutModel* m_treeLayoutModel;
    QVariantList m_treeEdges;
    QRectF m_treeBounds;
    Person* m_activeRoot = nullptr;
    QSet<int> m_collapsedIds;
    QSet<Person*> m_visiblePeople;

    bool m_timelineEnabled = false;
    int m_timelineYear = 2026;
};
