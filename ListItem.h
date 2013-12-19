#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlRecord>
#include <QSqlQuery>

namespace Models
{

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

//    void fromQSQLRecord(const QSqlRecord &result);
//    QString toSQLQuery(const QString &table) const;
//    QSqlQuery toSQLQuery(const QString &table) const;

signals:
    void dataChanged();
};

}

#endif // LISTITEM_H
