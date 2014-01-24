#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>

namespace Models
{

class ListModel;

class ListItem : public QObject
{
    Q_OBJECT
public:

public :
    ListItem(QObject *parent = 0);
    virtual ~ListItem() {}
    virtual int id() const = 0;
    virtual QVariant data(int role) const = 0;
    virtual bool     setData(int role, const QVariant &value);
    virtual QHash<int, QByteArray> roleNames() const = 0;
    QHash<QByteArray, int> roleTypesFromName();
    virtual void triggerItemUpdate();
    virtual bool operator<(const ListItem &nextElem);
    virtual ListItem& operator=(const ListItem &);
    virtual ListItem* getNewItemInstance(QObject *parent = 0) const = 0;
    ListItem *getParentItem() const;

protected :
    ListItem *parentItem;

signals:
    void dataChanged();
};

}

#endif // LISTITEM_H
