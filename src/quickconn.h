#ifndef QUICKCONN_H
#define QUICKCONN_H

#include <QtGui/QDialog>
#include "ui_quickconn.h"

QT_BEGIN_NAMESPACE

class quickconn : public QDialog, public Ui::quickconn
{
    Q_OBJECT
public:
    quickconn(QWidget *parent = 0);
    ~quickconn();
};

QT_END_NAMESPACE

#endif // QUICKCONN_H
