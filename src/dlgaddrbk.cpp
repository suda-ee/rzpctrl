#include "dlgaddrbk.h"
#include <QProcessEnvironment>
#include <QDir>
#include <QDebug>

dlgaddrbk::dlgaddrbk(QWidget *parent)
    : QDialog(parent), addrdocument()
{
    setupUi(this);
    //
    changed = false;
    QDomElement theelem = QDomElement();
    int i;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString profile = env.value("APPDATA");
    if (profile == QString())
	profile = env.value("HOME") + "/.config";
    QDir appDataDir = QDir(profile + "/rzpctrl");
    if (!appDataDir.exists())
	appDataDir.mkpath(profile + "/rzpctrl");
    theaddrfile = new QFile(profile + "/rzpctrl/" + ADDR_FILE, this);
    hostsmodel = new addrmodel(addrlist);
    hostsmodel->insertColumns(0, 3);
    hostsmodel->setHeaderData(0, Qt::Horizontal, tr("Õ¾Ãû"),
            Qt::DisplayRole);
    if (addrdocument.setContent(theaddrfile))
    {
        QDomNodeList hostlistelm = QDomNodeList();
        hostlistelm = addrdocument.elementsByTagName("host");
        hostsmodel->insertRows(0, hostlistelm.count());
        for (i = 0; i < hostlistelm.count(); i++)
        {
	    theelem = hostlistelm.item(i).toElement();
            hostsmodel->setData(hostsmodel->index(i, 0),
                    theelem.attribute("alias"));
            hostsmodel->setData(hostsmodel->index(i, 1),
                    theelem.attribute("addr"));
            hostsmodel->setData(hostsmodel->index(i, 2),
                    theelem.attribute("port").toInt());
        }
    }
    addrlist->setModel(hostsmodel);
    addrlist->setColumnHidden(1, true);
    addrlist->setColumnHidden(2, true);
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(hostsmodel);
    mapper->addMapping(lnname, 0);
    mapper->addMapping(lnaddr, 1);
    mapper->addMapping(sport, 2);
    mapper->toFirst();
    connect(btaddtolist, SIGNAL(clicked()), mapper, SLOT(submit()));
}

void dlgaddrbk::textsynclist(QModelIndex mdlindex)
{
    addrlist->selectRow(mdlindex.row());
    mapper->setCurrentIndex(mdlindex.row());
}

void dlgaddrbk::newhostentry()
{
    hostsmodel->insertRows(hostsmodel->rowCount(), 1);
    int therow = hostsmodel->rowCount() - 1;
    addrlist->selectRow(therow);
    hostsmodel->setData(hostsmodel->index(therow, 0),
            tr("New Host %1").arg(therow));
    hostsmodel->setData(hostsmodel->index(therow, 2),
            DEFAULTPORT);
    mapper->setCurrentIndex(therow);
    changed = true;
}

void dlgaddrbk::rmhostentry()
{
    
    hostsmodel->removeRows(addrlist->currentIndex().row(), 1);
    changed = true;
}

void dlgaddrbk::addrchange()
{
    changed = true;
}

dlgaddrbk::~dlgaddrbk()
{
    if (changed)
    {
        addrdocument = QDomDocument();
        addrdocument.appendChild(addrdocument.createProcessingInstruction("xml",
                    "version=\"1.0\" encoding=\"UTF-8\""));
        QDomElement root = addrdocument.createElement("hosts");
        addrdocument.appendChild(root);
        int i;
        QDomElement hostelem;
        for (i = 0; i < hostsmodel->rowCount(); i++)
        {
            hostelem = addrdocument.createElement("host");
            hostelem.setAttribute("alias", hostsmodel->data(
                        hostsmodel->index(i, 0)).toString());
            hostelem.setAttribute("addr", hostsmodel->data(
                        hostsmodel->index(i, 1)).toString());
            hostelem.setAttribute("port", hostsmodel->data(
                        hostsmodel->index(i, 2)).toInt());
            root.appendChild(hostelem);
        }
        theaddrfile->remove();
        theaddrfile->open(QIODevice::ReadWrite);
        QTextStream str(theaddrfile);
        addrdocument.save(str, 4);
    }
}
