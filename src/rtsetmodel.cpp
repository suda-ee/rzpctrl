#include "rtsetmodel.h"

rtsetmodel::rtsetmodel(QObject * parent)
    : QAbstractTableModel(parent), carrier(4), hHeader(4), vHeader(4),
    carrierState(4)
{
    insertColumns(0, 4);
    insertRows(0, 4);
    setHeaderData(0, Qt::Horizontal, tr("光纤"));
    setHeaderData(1, Qt::Horizontal, tr("无线Mesh"));
    setHeaderData(2, Qt::Horizontal, tr("E1"));
    setHeaderData(3, Qt::Horizontal, tr("V35"));
    setHeaderData(0, Qt::Vertical, tr("TDCS"));
    setHeaderData(1, Qt::Vertical, tr("语音"));
    setHeaderData(2, Qt::Vertical, tr("视频"));
    setHeaderData(3, Qt::Vertical, tr("E1"));
    for (int i = 0; i < 4; i++)
	carrier[i] = 999;
}

rtsetmodel::~rtsetmodel()
{
}

int rtsetmodel::rowCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return 4;
    else
        return 0;
}

int rtsetmodel::columnCount(const QModelIndex & parent) const
{
    if (parent == QModelIndex())
        return 4;
    else
        return 0;
}

QVariant rtsetmodel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (carrier.at(index.row()) == index.column())
            return true;
        else
            return false;
    }
    else if (role == Qt::CheckStateRole)
    {
	return carrierState.at(index.column());
    }
    else
    {
        return QVariant();
    }
}

QVariant rtsetmodel::headerData(int section, Qt::Orientation orientation,
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

bool rtsetmodel::setData(const QModelIndex & idx, const QVariant & value,
            int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (value.toBool())
            carrier[idx.row()] = idx.column();
	else
            carrier[idx.row()] = 999;
        emit dataChanged(index(idx.row(), 0), index(idx.row(), 3));
        return true;
    }
    else if (role == Qt::CheckStateRole)
    {
	carrierState[idx.column()] = value.toBool();
        emit dataChanged(index(idx.row(), 0), index(idx.row(), 3));
        return true;
    }
    else
        return QAbstractTableModel::setData(idx, value, role);
}

Qt::ItemFlags rtsetmodel::flags(const QModelIndex & index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool rtsetmodel::setHeaderData(int section, Qt::Orientation orientation,
        const QVariant & value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (orientation == Qt::Horizontal)
        {
            hHeader[section] = value.toString();
        }
        else
        {
            vHeader[section] = value.toString();
        }
        emit headerDataChanged(orientation, section, section);
	return true;
    }
    else
        return QAbstractTableModel::setHeaderData(section, orientation, value,
                role);
}
bool rtsetmodel::insertRows(int row, int count, const QModelIndex & parent)
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

bool rtsetmodel::insertColumns(int column, int count, const QModelIndex & parent)
{
    if (count + column == 4)
    {
        beginInsertColumns(parent, column, column + count - 1);
        endInsertColumns();
        return true;
    }
    else
        return false;
}

bool rtsetmodel::removeRows(int row, int count, const QModelIndex & parent)
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

bool rtsetmodel::removeColumns(int column, int count, const QModelIndex & parent)
{
    if (count + column == 4)
    {
        beginRemoveColumns(parent, column, column + count - 1);
        endRemoveColumns();
        return true;
    }
    else
        return false;
}
