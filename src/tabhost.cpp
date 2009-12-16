#include "tabhost.h"

tabhost::tabhost(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    //
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/images/statestatus.png")), QIcon::Normal, QIcon::Off);
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/images/datasumm.png")), QIcon::Normal, QIcon::Off);
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/images/routedata.png")), QIcon::Normal, QIcon::Off);
    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/images/remotesetup.png")), QIcon::Normal, QIcon::Off);
    QIcon icon5;
    icon5.addPixmap(QPixmap(QString::fromUtf8(":/images/routes.png")), QIcon::Normal, QIcon::Off);
    ctlitems *stategroup = new ctlitems(treecrl);
    stategroup->setIcon(0, icon1);
    stategroup->setText(0, trUtf8("状态查看"));
    stategroup->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    ctlitems *datastate = new ctlitems(stategroup);
    datastate->setIcon(0, icon2);
    datastate->setText(0, trUtf8("通信状态"));
    ctlitems *routestate = new ctlitems(stategroup);
    routestate->setIcon(0, icon3);
    routestate->setText(0, trUtf8("路由状态"));
    ctlitems *setgroup = new ctlitems(treecrl);
    setgroup->setIcon(0, icon4);
    setgroup->setText(0, trUtf8("远程控制"));
    setgroup->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    ctlitems *routectl = new ctlitems(setgroup);
    routectl->setIcon(0, icon5);
    routectl->setText(0, trUtf8("路由设置"));

    treecrl->expandAll();

    //
    QWidget *tmppage = new ratestatepage(stacked);
    stacked->addWidget(tmppage);
    datastate->thepage = tmppage;
    tmppage = new rtstatepage(stacked);
    stacked->addWidget(tmppage);
    routestate->thepage = tmppage;
    tmppage = new rtsetpage(stacked);
    stacked->addWidget(tmppage);
    routectl->thepage = tmppage;

    //
    connect(treecrl, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(changepage(QTreeWidgetItem*, int)));
    connect(treecrl, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changepage(QTreeWidgetItem*, int)));
}

void tabhost::changepage(QTreeWidgetItem *item, int column)
{
    if (item->isSelected())
        stacked->setCurrentWidget(((ctlitems*) item)->thepage);
}

tabhost::~tabhost()
{
}
