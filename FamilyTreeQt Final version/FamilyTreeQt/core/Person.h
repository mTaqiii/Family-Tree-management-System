#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <qqml.h>

#include "Types.h"

// Person is the single unit of the family graph -- same role as
// the `struct Person` in the original console app, but as a QObject
// so QML views can bind to id/name/gender/status/father/mother/spouse
// directly, and react automatically when they change.
//
// Ownership: Person objects are owned centrally by FamilyForest, never
// by each other. father/mother/spouse/children below are plain,
// non-owning observation pointers -- identical in spirit to the raw
// pointers used throughout the original struct-based design.
class Person : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Person objects are created by FamilyForest, not from QML")

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Gender gender READ gender CONSTANT)
    Q_PROPERTY(LifeStatus status READ status WRITE setStatus NOTIFY statusChanged)

    Q_PROPERTY(Person* father READ father NOTIFY fatherChanged)
    Q_PROPERTY(Person* mother READ mother NOTIFY motherChanged)
    Q_PROPERTY(Person* spouse READ spouse NOTIFY spouseChanged)
    Q_PROPERTY(QList<Person*> children READ children NOTIFY childrenChanged)

    // Optional -- 0 means "not recorded". Added specifically to
    // support Timeline Mode (a year slider that hides people not yet
    // born and grays out those who have died); every other feature
    // in the app works fine with these left at 0.
    Q_PROPERTY(int birthYear READ birthYear WRITE setBirthYear NOTIFY birthYearChanged)
    Q_PROPERTY(int deathYear READ deathYear WRITE setDeathYear NOTIFY deathYearChanged)

public:

    explicit Person(int id,
                     const QString& name,
                     Gender gender,
                     QObject* parent = nullptr);

    int id() const { return m_id; }

    QString name() const { return m_name; }
    void setName(const QString& name);

    Gender gender() const { return m_gender; }

    LifeStatus status() const { return m_status; }
    void setStatus(LifeStatus status);

    Person* father() const { return m_father; }
    Person* mother() const { return m_mother; }
    Person* spouse() const { return m_spouse; }
    QList<Person*> children() const { return m_children; }

    int birthYear() const { return m_birthYear; }
    void setBirthYear(int year);

    int deathYear() const { return m_deathYear; }
    void setDeathYear(int year);

    // --- Internal relationship wiring -------------------------------
    // These are called only by the Relationships:: free functions
    // (core/Relationships.h), never directly by the bridge or QML,
    // exactly like the original code kept pointer surgery inside a
    // small set of trusted functions (connectSpouses, addChildToParent, ...).

    void setFather(Person* father);
    void setMother(Person* mother);
    void setSpouse(Person* spouse);
    void addChild(Person* child);
    void setChildren(const QList<Person*>& children);

    // Transient traversal-guard flag used by graph search (mirrors
    // Person::visited in the console version). Never exposed to QML.
    bool visited = false;

signals:

    void nameChanged();
    void statusChanged();
    void fatherChanged();
    void motherChanged();
    void spouseChanged();
    void childrenChanged();
    void birthYearChanged();
    void deathYearChanged();

private:

    int m_id;
    QString m_name;
    Gender m_gender;
    LifeStatus m_status = LifeStatus::Alive;

    Person* m_father = nullptr;
    Person* m_mother = nullptr;
    Person* m_spouse = nullptr;
    QList<Person*> m_children;

    int m_birthYear = 0;
    int m_deathYear = 0;
};
