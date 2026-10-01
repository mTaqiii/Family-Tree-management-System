#pragma once

#include <QAbstractListModel>
#include <qqml.h>

#include "../core/Person.h"

// Generic "list of people" model, reused for every list-shaped view
// in the app: all registered trees, a set of search results, or a
// person's list of children. QML gets each Person* through the
// `person` role and binds straight to its properties/signals.
class PersonListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided by FamilyTreeController")

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:

    enum Role
    {
        PersonRole = Qt::UserRole + 1
    };

    explicit PersonListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return rowCount(); }

    void setPeople(const QList<Person*>& people);

signals:

    void countChanged();

private:

    QList<Person*> m_people;
};
