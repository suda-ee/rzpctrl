#include "tabhost.h"
#include <QtGui/QMessageBox>

tabhost::tabhost(QWidget *parent)
    : QWidget(parent), peerhostname()
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
    tmppage->setObjectName("ratepage");
    stacked->addWidget(tmppage);
    datastate->thepage = tmppage;
    tmppage = new rtstatepage(stacked);
    stacked->addWidget(tmppage);
    routestate->thepage = tmppage;
    tmppage = new rtsetpage(stacked);
    tmppage->setObjectName("rtSetPage");
    stacked->addWidget(tmppage);
    routectl->thepage = tmppage;

    dataSocket = new QTcpSocket(parent);

    //
    connect(treecrl, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(changepage(QTreeWidgetItem*, int)));
    connect(treecrl, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changepage(QTreeWidgetItem*, int)));
    connect(((ratestatepage*)(datastate->thepage))->btGetRate, SIGNAL(clicked()), this, SLOT(getDataRate()));
    connect(((ratestatepage*)(datastate->thepage))->timer, SIGNAL(timeout()), this, SLOT(getDataRate()));

    connect(((rtsetpage*)(routectl->thepage)), SIGNAL(rtSetManu()), this,
            SLOT(setManuRt()));
    connect(((rtsetpage*)(routectl->thepage)), SIGNAL(rtSetAuto()), this,
            SLOT(setAutoRt()));
    connect(((rtsetpage*)(routectl->thepage)), SIGNAL(sgSendRoute()), this,
            SLOT(slSendRoute()));

    connect(dataSocket, SIGNAL(connected()), this, SLOT(setthisEnabled()));
    connect(dataSocket, SIGNAL(disconnected()), this, SLOT(setthisDisabled()));
    connect(dataSocket, SIGNAL(readyRead()), this, SLOT(readDataIn()));
    connect(dataSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(sktErrorMsg(QAbstractSocket::SocketError)));
    connect(dataSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(sktConnMsg(QAbstractSocket::SocketState)));
}

void tabhost::changepage(QTreeWidgetItem *item, int column)
{
    if (item->isSelected())
    {
        stacked->setCurrentWidget(((ctlitems*) item)->thepage);
        if (stacked->findChild<ratestatepage*>("ratepage")
                != qobject_cast<ratestatepage*>(((ctlitems*) item)->thepage))
            stacked->findChild<ratestatepage*>("ratepage")->timeEn
                ->setChecked(false);
    }
}

void tabhost::setAndConn(const QString & hostName, quint16 port)
{
    peerhostname = hostName;
    peerport = port;
    dataSocket->connectToHost(hostName, port);
}

void tabhost::reconnectskt()
{
    if (dataSocket->state() != QAbstractSocket::ConnectedState)
    {
        dataSocket->disconnectFromHost();
        dataSocket->connectToHost(peerhostname, peerport);
    }
}

void tabhost::disconnectskt()
{
    dataSocket->disconnectFromHost();
}

void tabhost::setthisEnabled()
{
    setEnabled(true);
}

void tabhost::setthisDisabled()
{
    setDisabled(true);
}

tabhost::~tabhost()
{
    dataSocket->disconnectFromHost();
}

void tabhost::getDataRate()
{
    QByteArray sendingMsg;
    sendingMsg.resize(2);
    sendingMsg[0] = 0x95;
    sendingMsg[1] = 0x21;
    if (dataSocket->write(sendingMsg) > 0)
        emit statusMsg(trUtf8("%1: 发送数据成功").arg(peerhostname));
    //dataSocket->flush();
}

void tabhost::slSendRoute()
{
    QByteArray sendingMsg;
    sendingMsg.resize(2);
    sendingMsg[0] = 0xeb;
    sendingMsg[1] = 0x81;
    char rttable[4] = {0x21, 0x22, 0x23, 0x24};
    rtsetmodel *model = qobject_cast<rtsetmodel*>(
            stacked->findChild<rtsetpage*>("rtSetPage")->tblroute->model());
    sendingMsg.append(rttable[model->carrier.at(0)]);
    sendingMsg.append(rttable[model->carrier.at(1)]);
    sendingMsg.append(rttable[model->carrier.at(2)]);
    sendingMsg.append(rttable[model->carrier.at(3)]);
    if (dataSocket->write(sendingMsg) > 0)
        emit statusMsg(trUtf8("%1: 发送数据成功").arg(peerhostname));
}

void tabhost::setManuRt()
{
    QByteArray sendingMsg;
    sendingMsg.resize(2);
    sendingMsg[0] = 0xeb;
    sendingMsg[1] = 0x83;
    if (dataSocket->write(sendingMsg) > 0)
        emit statusMsg(trUtf8("%1: 发送数据成功").arg(peerhostname));
}

void tabhost::setAutoRt()
{
    QByteArray sendingMsg;
    sendingMsg.resize(2);
    sendingMsg[0] = 0xeb;
    sendingMsg[1] = 0x82;
    if (dataSocket->write(sendingMsg) > 0)
        emit statusMsg(trUtf8("%1: 发送数据成功").arg(peerhostname));
}

void tabhost::readDataIn()
{
    QByteArray receivedMsg = dataSocket->readAll();
    QByteArray stateHead = QByteArray::fromHex("9521");
    QByteArray rtManutableHead = QByteArray::fromHex("eb81");
    QByteArray rtAutoHead = QByteArray::fromHex("eb82");
    QByteArray rtManuHead = QByteArray::fromHex("eb83");
    if (receivedMsg.startsWith(stateHead))
    {
        statemodel *model = qobject_cast<statemodel*>(stacked
		->findChild<ratestatepage*>("ratepage")->tblrate->model());
        float rate = *(uint*)&receivedMsg.data()[4] / 1000.;
        model->setData(model->index(0, 2), rate);
        rate = *(uint*)&receivedMsg.data()[8] / 1000.;
        model->setData(model->index(1, 2), rate);
        rate = *(uint*)&receivedMsg.data()[12] / 1000.;
        model->setData(model->index(2, 2), rate);
        rate = *(uint*)&receivedMsg.data()[16] / 1000.;
        model->setData(model->index(3, 2), rate);
        QBitArray signs(8);
        int i;
        char statechar = receivedMsg.at(2);
	//QMessageBox::about(this, "about", QString("%1").arg(rate));
        for (i = 0; i < 8; i++)
        {
            signs.setBit(i, statechar & 0x01);
            statechar = statechar >> 1;
        }
        for (i = 0; i < 4; i++)
        {
            model->setData(model->index(i, 0), signs.at(i));
            model->setData(model->index(i, 1), signs.at(i + 4));
        }
        stacked->findChild<ratestatepage*>("ratepage")->tblrate->setFocus();
        emit statusMsg(trUtf8("%1: 接收状态信息成功").arg(peerhostname));
    }
    else if (receivedMsg.startsWith(rtManutableHead))
    {
        emit statusMsg(trUtf8("%1: 手动路由表发送成功！").arg(peerhostname));
    }
    else if (receivedMsg.startsWith(rtAutoHead))
    {
        emit statusMsg(trUtf8("%1: 自动路由模式启动成功！").arg(peerhostname));
    }
    else if (receivedMsg.startsWith(rtManuHead))
    {
        emit statusMsg(trUtf8("%1: 手动路由模式启动成功！").arg(peerhostname));
    }
}

void tabhost::sktErrorMsg(QAbstractSocket::SocketError socketError)
{
    if (socketError == QAbstractSocket::ConnectionRefusedError)
        emit statusMsg(trUtf8("%1: 拒绝连接！").arg(peerhostname));
    else if (socketError == QAbstractSocket::RemoteHostClosedError)
        emit statusMsg(trUtf8("%1: 远端断开！").arg(peerhostname));
    else if (socketError == QAbstractSocket::HostNotFoundError)
        emit statusMsg(trUtf8("%1: 主机未发现！").arg(peerhostname));
    else if (socketError == QAbstractSocket::SocketTimeoutError)
        emit statusMsg(trUtf8("%1: 操作超时！").arg(peerhostname));
    else if (socketError == QAbstractSocket::NetworkError)
        emit statusMsg(trUtf8("%1: 网络错误！").arg(peerhostname));
}

void tabhost::sktConnMsg(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
        emit statusMsg(trUtf8("%1: 未连接！").arg(peerhostname));
    else if (socketState == QAbstractSocket::ConnectedState)
        emit statusMsg(trUtf8("%1: 连接！").arg(peerhostname));
}
