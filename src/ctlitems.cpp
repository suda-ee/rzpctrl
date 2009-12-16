#include "ctlitems.h"

ctlitems::ctlitems(QTreeWidget *parent, int type)
    : QTreeWidgetItem(parent, type)
{
}

ctlitems::ctlitems(ctlitems *parent, int type)
    : QTreeWidgetItem(parent, type)
{
}

ctlitems::~ctlitems()
{
}
