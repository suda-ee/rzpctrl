#ifndef RATESTATEPAGE_H
#define RATESTATEPAGE_H

#include <QtCore/QTimer>
#include <QtGui/QWidget>
#include "ui_ratestatepage.h"
#include "statemodel.h"
#include "statedelegate.h"

QT_BEGIN_NAMESPACE

class ratestatepage : public QWidget, public Ui::ratestatepage
{
    Q_OBJECT
public:
    ratestatepage(QWidget *parent = 0);
    ~ratestatepage();
    statemodel *state;
    statedelegate *delegate;
    QTimer *timer;

public slots:
    void showHideTime(bool checked);
    void setTimerInterval(int timeSecond);
    void startTimer();
};

QT_END_NAMESPACE

#endif // RATESTATEPAGE_H
