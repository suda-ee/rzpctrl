#include "rtsetdelegate.h"
#include <QtGui/QCheckBox>
#include <QtGui/QPainter>
#include <QtGui/QApplication>

rtsetdelegate::rtsetdelegate(QObject * parent)
    : QStyledItemDelegate(parent)
{
}

rtsetdelegate::~rtsetdelegate()
{
}

void rtsetdelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex & index) const
{
    painter->save();
    QStyleOptionButton optBt;
    optBt.rect = option.rect;
    optBt.rect.moveLeft(optBt.rect.width() / 3 + optBt.rect.left());
    optBt.state = QStyle::State_Active | QStyle::State_Enabled
        | QStyle::State_MouseOver;
    if (index.model()->data(index).toBool())
        optBt.state = optBt.state | QStyle::State_On;
    else
        optBt.state = optBt.state | QStyle::State_Off;
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &optBt, painter);
    painter->restore();
}

QWidget * rtsetdelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QStyleOptionButton optBt;
    optBt.rect = option.rect;
    optBt.rect.moveLeft(optBt.rect.width() / 3 + optBt.rect.left());
    QCheckBox *editor = new QCheckBox(parent);
    editor->setGeometry(optBt.rect);
    return editor;
}

void rtsetdelegate::setEditorData(QWidget *editor,
        const QModelIndex &index) const
{
    if (index.model()->data(index).toBool())
        qobject_cast<QCheckBox*>(editor)->setCheckState(Qt::Checked);
    else
        qobject_cast<QCheckBox*>(editor)->setCheckState(Qt::Unchecked);
}

void rtsetdelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex & index) const
{
    bool value;
    if (qobject_cast<QCheckBox*>(editor)->checkState() == Qt::Checked)
        value = true;
    else
        value = false;
    model->setData(index, value);
}

void rtsetdelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QStyleOptionButton optBt;
    optBt.rect = option.rect;
    optBt.rect.moveLeft(optBt.rect.width() / 3 + optBt.rect.left());
    editor->setGeometry(optBt.rect);
}
