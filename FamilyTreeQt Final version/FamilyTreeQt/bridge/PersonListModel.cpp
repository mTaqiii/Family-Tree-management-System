#include "PersonListModel.h"

PersonListModel::PersonListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int PersonListModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;

    return m_people.size();
}

QVariant PersonListModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= m_people.size())
        return QVariant();

    if(role == PersonRole)
        return QVariant::fromValue(m_people.at(index.row()));

    return QVariant();
}

QHash<int, QByteArray> PersonListModel::roleNames() const
{
    return { { PersonRole, "person" } };
}

void PersonListModel::setPeople(const QList<Person*>& people)
{
    beginResetModel();
    m_people = people;
    endResetModel();
    emit countChanged();
}
