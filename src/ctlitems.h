#include <QtGui/QWidget>
#include <QtGui/QTreeWidgetItem>

class ctlitems : public QTreeWidgetItem
{
public:
    ctlitems(QTreeWidget *parent, int type = Type);
    ctlitems(ctlitems *parent, int type = Type);
    ~ctlitems();
    
    QWidget *thepage;
};
