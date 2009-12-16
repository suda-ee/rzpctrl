#include "rtsetpage.h"

rtsetpage::rtsetpage(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    model = new rtsetmodel(this);
    delegate = new rtsetdelegate(this);
    tblroute->setModel(model);
    tblroute->setItemDelegate(delegate);
    connect(rtManu, SIGNAL(clicked(bool)), this, SIGNAL(rtSetManu(bool)));
    connect(rtAuto, SIGNAL(clicked(bool)), this, SIGNAL(rtSetAuto(bool)));
    connect(btsendRoute, SIGNAL(clicked()), this, SIGNAL(sgSendRoute()));
}
rtsetpage::~rtsetpage()
{
}
