#include "ratestatepage.h"

ratestatepage::ratestatepage(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    state = new statemodel(this);
    tblrate->setModel(state);
    delegate = new statedelegate(this);
    tblrate->setItemDelegateForColumn(0, delegate);
    tblrate->setItemDelegateForColumn(1, delegate);
    tmLabel->hide();
    timeInterval->hide();
    timer = new QTimer(this);
}
ratestatepage::~ratestatepage()
{
}

void ratestatepage::showHideTime(bool checked)
{
    if (checked)
    {
        tmLabel->show();
        timeInterval->show();
        timer->setInterval(timeInterval->value() * 1000);
    }
    else
    {
        tmLabel->hide();
        timeInterval->hide();
        timer->stop();
    }
}

void ratestatepage::startTimer()
{
    if (timeEn->isChecked())
        timer->start();
}
