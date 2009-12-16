#include "statedelegate.h"
#include "statemodel.h"
#include <QtGui/QPainter>
#include <QtGui/QRadioButton>
#include <QtGui/QApplication>

statedelegate::statedelegate(QObject * parent)
    : QStyledItemDelegate(parent)
{
}

statedelegate::~statedelegate()
{
}

void statedelegate::paint(QPainter *painter,
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
    QApplication::style()->drawControl(QStyle::CE_RadioButton, &optBt, painter);
    painter->restore();
}
/*
QWidget * statedelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QStyleOptionButton optBt;
    optBt.rect = option.rect;
    optBt.rect.moveLeft(optBt.rect.width() / 3 + optBt.rect.left());
    QRadioButton *editor = new QRadioButton(parent);
    editor->setGeometry(optBt.rect);
    editor->setAutoExclusive(false);
    return editor;
}

void statedelegate::setEditorData(QWidget *editor,
        const QModelIndex &index) //const
{
    qobject_cast<QRadioButton*>(editor)->setChecked(
            index.model()->data(index).toBool());
    emit closeEditor(editor);
}

void statedelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex & index) const
{
    bool value;
    value = qobject_cast<QRadioButton*>(editor)->isChecked();
    model->setData(index, value);
}

void statedelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QStyleOptionButton optBt;
    optBt.rect = option.rect;
    optBt.rect.moveLeft(optBt.rect.width() / 3 + optBt.rect.left());
    editor->setGeometry(optBt.rect);
}
*/
