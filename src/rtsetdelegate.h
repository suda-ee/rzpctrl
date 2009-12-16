#ifndef RTSETDELEGATE_H
#define RTSETDELEGATE_H

#include <QtGui/QStyledItemDelegate>
#include <QtGui/QPainter>
#include "config.h"

QT_BEGIN_NAMESPACE

class rtsetdelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    rtsetdelegate(QObject * parent = 0);
    ~rtsetdelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex & index) const;
    void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;
};

QT_END_NAMESPACE

#endif // RTSETDELEGATE_H
