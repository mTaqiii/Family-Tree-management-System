#include "Person.h"

Person::Person(int id, const QString& name, Gender gender, QObject* parent)
    : QObject(parent),
      m_id(id),
      m_name(name),
      m_gender(gender)
{
}

void Person::setName(const QString& name)
{
    if(m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

void Person::setStatus(LifeStatus status)
{
    if(m_status == status)
        return;

    m_status = status;
    emit statusChanged();
}

void Person::setFather(Person* father)
{
    m_father = father;
    emit fatherChanged();
}

void Person::setMother(Person* mother)
{
    m_mother = mother;
    emit motherChanged();
}

void Person::setSpouse(Person* spouse)
{
    m_spouse = spouse;
    emit spouseChanged();
}

void Person::addChild(Person* child)
{
    m_children.append(child);
    emit childrenChanged();
}

void Person::setChildren(const QList<Person*>& children)
{
    m_children = children;
    emit childrenChanged();
}

void Person::setBirthYear(int year)
{
    if(m_birthYear == year)
        return;

    m_birthYear = year;
    emit birthYearChanged();
}

void Person::setDeathYear(int year)
{
    if(m_deathYear == year)
        return;

    m_deathYear = year;
    emit deathYearChanged();
}
