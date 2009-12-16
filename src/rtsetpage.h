#ifndef RTSETPAGE_H
#define RTSETPAGE_H

#include <QtGui/QWidget>
#include "ui_rtsetpage.h"
#include "rtsetmodel.h"
#include "rtsetdelegate.h"

QT_BEGIN_NAMESPACE

class rtsetpage : public QWidget, public Ui::rtsetpage
{
    Q_OBJECT
public:
    rtsetpage(QWidget *parent = 0);
    ~rtsetpage();
    rtsetmodel *model;
    rtsetdelegate *delegate;

signals:
    void rtSetManu(bool checked = true);
    void rtSetAuto(bool checked = true);
    void sgSendRoute();
};

QT_END_NAMESPACE

#endif // RTSETPAGE_H
