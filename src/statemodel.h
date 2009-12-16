#ifndef STATEMODEL_H
#define STATEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include "config.h"

QT_BEGIN_NAMESPACE

class statemodel : public QAbstractTableModel
{
    Q_OBJECT
public:
    statemodel(QObject * parent = 0);
    ~statemodel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value,
            int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool setHeaderData(int section, Qt::Orientation orientation,
            const QVariant & value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex & parent
            = QModelIndex());
    bool insertColumns(int column, int count, const QModelIndex & parent
            = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent
            = QModelIndex());
    bool removeColumns(int column, int count, const QModelIndex & parent
            = QModelIndex());

    QBitArray updown; //column 0
    QBitArray busyspare;
    QVector<float> rate; //in kbit/s 

    //Headers
    QVector<QString> hHeader;
    QVector<QString> vHeader;
    
};

QT_END_NAMESPACE

#endif // STATEMODEL_H
