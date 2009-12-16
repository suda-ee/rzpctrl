#ifndef RTSETPAGE_H
#define RTSETPAGE_H

#include <QtGui/QWidget>
#include "ui_rtsetpage.h"

QT_BEGIN_NAMESPACE

class rtsetpage : public QWidget, public Ui::rtsetpage
{
    Q_OBJECT
public:
    rtsetpage(QWidget *parent = 0);
    ~rtsetpage();
};

QT_END_NAMESPACE

#endif // RTSETPAGE_H
