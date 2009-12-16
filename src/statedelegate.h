#ifndef STATEDELEGATE_H
#define STATEDELEGATE_H

#include <QtGui/QStyledItemDelegate>
#include "config.h"

QT_BEGIN_NAMESPACE

class statedelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    statedelegate(QObject * parent = 0);
    ~statedelegate();
    void paint(QPainter * painter, const QStyleOptionViewItem & option,
            const QModelIndex & index) const;
    /*
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index);// const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex & index) const;
    void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
    */
};

QT_END_NAMESPACE

#endif // STATEDELEGATE_H
