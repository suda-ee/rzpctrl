#include "statemodel.h"

statemodel::statemodel(QObject * parent)
    : QAbstractTableModel(parent), updown(4), busyspare(4), rate(4),
      hHeader(3), vHeader(4)
{
    insertColumns(0, 3);
    insertRows(0, 4);
    setHeaderData(0, Qt::Horizontal, tr("通断"));
    setHeaderData(1, Qt::Horizontal, tr("忙闲"));
    setHeaderData(2, Qt::Horizontal, tr("速率(kbits/s)"));
    setHeaderData(0, Qt::Vertical, tr("光纤"));
    setHeaderData(1, Qt::Vertical, tr("无线Mesh"));
    setHeaderData(2, Qt::Vertical, tr("E1"));
    setHeaderData(3, Qt::Vertical, tr("V35"));
}

statemodel::~statemodel()
{
}

int statemodel::rowCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return 4;
    else
        return 0;
}

int statemodel::columnCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return 3;
    else
        return 0;
}

QVariant statemodel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
            case 0:
                return updown.at(index.row());
                break;
            case 1:
                return busyspare.at(index.row());
                break;
            default:
                return rate.at(index.row());
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant statemodel::headerData(int section, Qt::Orientation orientation,
        int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (orientation == Qt::Horizontal)
            return hHeader.at(section);
        else
            return vHeader.at(section);
    }
    else
        return QAbstractTableModel::headerData(section, orientation, role);
}

bool statemodel::setData(const QModelIndex & index, const QVariant & value,
            int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (index.column())
        {
            case 0:
                updown.setBit(index.row(), value.toBool());
                return true;
                break;
            case 1:
                busyspare.setBit(index.row(), value.toBool());
                return true;
                break;
            default:
                rate[index.row()] = value.toDouble();
                return true;
        }
        emit dataChanged(index, index);
    }
    else
        return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags statemodel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index);
}

bool statemodel::setHeaderData(int section, Qt::Orientation orientation,
        const QVariant & value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (orientation == Qt::Horizontal)
        {
            hHeader[section] = value.toString();
            return true;
        }
        else
        {
            vHeader[section] = value.toString();
            return true;
        }
        emit headerDataChanged(orientation, section, section);
    }
    else
        return QAbstractTableModel::setHeaderData(section, orientation, value,
                role);
}
bool statemodel::insertRows(int row, int count, const QModelIndex & parent)
{
    if (count + row == 4)
    {
        beginInsertRows(parent, row, row + count - 1);
        endInsertRows();
        return true;
    }
    else
        return false;
}

bool statemodel::insertColumns(int column, int count, const QModelIndex & parent)
{
    if (count + column == 3)
    {
        beginInsertColumns(parent, column, column + count - 1);
        endInsertColumns();
        return true;
    }
    else
        return false;
}

bool statemodel::removeRows(int row, int count, const QModelIndex & parent)
{
    if (count + row == 4)
    {
        beginRemoveRows(parent, row, row + count - 1);
        endRemoveRows();
        return true;
    }
    else
        return false;
}

bool statemodel::removeColumns(int column, int count, const QModelIndex & parent)
{
    if (count + column == 3)
    {
        beginRemoveColumns(parent, column, column + count - 1);
        endRemoveColumns();
        return true;
    }
    else
        return false;
}
