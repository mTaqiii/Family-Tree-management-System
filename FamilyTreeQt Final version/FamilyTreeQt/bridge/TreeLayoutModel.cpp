#include "TreeLayoutModel.h"

TreeLayoutModel::TreeLayoutModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int TreeLayoutModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;

    return m_placements.size();
}

QVariant TreeLayoutModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= m_placements.size())
        return QVariant();

    const TreeLayoutEngine::Placement& p = m_placements.at(index.row());

    switch(role)
    {
        case PersonRole:       return QVariant::fromValue(p.person);
        case XRole:             return p.x;
        case YRole:             return p.y;
        case HasChildrenRole:  return p.hasChildren;
        case CollapsedRole:    return p.collapsed;
        default:                return QVariant();
    }
}

QHash<int, QByteArray> TreeLayoutModel::roleNames() const
{
    return {
        { PersonRole, "person" },
        { XRole, "nodeX" },
        { YRole, "nodeY" },
        { HasChildrenRole, "hasChildren" },
        { CollapsedRole, "collapsed" }
    };
}

void TreeLayoutModel::setPlacements(const QList<TreeLayoutEngine::Placement>& placements)
{
    beginResetModel();
    m_placements = placements;
    endResetModel();
}
