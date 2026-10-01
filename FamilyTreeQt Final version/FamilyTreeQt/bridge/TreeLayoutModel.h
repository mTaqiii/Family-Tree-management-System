#pragma once

#include <QAbstractListModel>
#include <qqml.h>

#include "../core/Person.h"
#include "../core/TreeLayoutEngine.h"

class TreeLayoutModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Provided by FamilyTreeController")

public:

    enum Role
    {
        PersonRole = Qt::UserRole + 1,
        XRole,
        YRole,
        HasChildrenRole,
        CollapsedRole
    };

    explicit TreeLayoutModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setPlacements(const QList<TreeLayoutEngine::Placement>& placements);

private:

    QList<TreeLayoutEngine::Placement> m_placements;
};
