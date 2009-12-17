#include "addrmodel.h"

addrmodel::addrmodel(QObject * parent)
    : QAbstractTableModel(parent)
{
}

addrmodel::~addrmodel()
{
}

int addrmodel::rowCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return addr.count();
    else
        return 0;
}

int addrmodel::columnCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return 3;
    else
        return 0;
}

QVariant addrmodel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
            case 0:
                return alias.at(index.row());
                break;
            case 1:
                return addr.at(index.row());
                break;
            default:
                return port.at(index.row());
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant addrmodel::headerData(int section, Qt::Orientation orientation,
        int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return Vheader.at(section);
    else
        return QAbstractItemModel::headerData(section, orientation, role);
}

bool addrmodel::setData(const QModelIndex & index, const QVariant & value,
            int role)
{
    if (role == Qt::EditRole)
    {
        switch (index.column())
        {
            case 0:
                alias[index.row()] = value.toString();
                break;
            case 1:
                addr[index.row()] = value.toString();
                break;
            default:
                port[index.row()] = value.toInt();
        }
        emit dataChanged(index, index);
	return true;
    }
    else
        return QAbstractItemModel::setData(index, value, role);
}

Qt::ItemFlags addrmodel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool addrmodel::setHeaderData(int section, Qt::Orientation orientation,
        const QVariant & value, int role)
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        Vheader[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    else
        return QAbstractItemModel::setHeaderData(section, orientation, value,
                role);
}
bool addrmodel::insertRows(int row, int count, const QModelIndex & parent)
{
    int i;
    beginInsertRows(parent, row, row + count - 1);
    for (i = count; i > 0; i--)
    {
        alias.insert(row, QString(""));
        addr.insert(row, QString(""));
        port.insert(row, DEFAULTPORT);
    }
    endInsertRows();
    return true;
}

bool addrmodel::insertColumns(int column, int count, const QModelIndex & parent)
{
    if (count == 3 && column == 0)
    {
        beginInsertColumns(parent, column, column + count - 1);
        Vheader.append("");
        Vheader.append("");
        Vheader.append("");
        endInsertColumns();
        return true;
    }
    else
        return false;
}

bool addrmodel::removeRows(int row, int count, const QModelIndex & parent)
{
    int i;
    beginRemoveRows(parent, row, row + count - 1);
    for (i = 0; i < count; i++)
    {
        alias.removeAt(row);
        addr.removeAt(row);
        port.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool addrmodel::removeColumns(int column, int count, const QModelIndex & parent)
{
    return false;
}
