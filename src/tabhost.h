#ifndef TABHOST_H
#define TABHOST_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include <QtNetwork/QTcpSocket>
#include "ui_tabhost.h"
#include "ctlitems.h"
#include "ratestatepage.h"
#include "rtstatepage.h"
#include "rtsetpage.h"

QT_BEGIN_NAMESPACE

class tabhost : public QWidget, public Ui::tabclass
{
    Q_OBJECT
public:
    tabhost(QWidget *parent = 0);
    ~tabhost();
    void setAndConn(const QString & hostName, quint16 port);
    QTcpSocket *dataSocket;
    QString peerhostname;
    quint16 peerport;

public slots:
    void changepage(QTreeWidgetItem *item, int column);
    void reconnectskt();
    void disconnectskt();
    void setthisEnabled();
    void setthisDisabled();
    void getDataRate();
    void readDataIn();
    void setManuRt();
    void setAutoRt();
    void slSendRoute();
    void sktErrorMsg(QAbstractSocket::SocketError socketError);
    void sktConnMsg(QAbstractSocket::SocketState socketState);
    void changeRouteSet(const QModelIndex & index);

signals:
    void statusMsg(const QString & msg);
};

QT_END_NAMESPACE

#endif // TABHOST_H
