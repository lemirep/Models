#include "ListModel.h"
#include <QDebug>


Models::ListItem::ListItem(QObject *parent) : QObject(parent)
{
    if (qobject_cast<ListItem *>(parent) != NULL)
        qDebug() << "Parent is a listItem";
}

bool Models::ListItem::setData(int role, const QVariant &value)
{
    Q_UNUSED(role);
    Q_UNUSED(value);
    return false;
}

QHash<QByteArray, int> Models::ListItem::roleTypesFromName()
{
    QHash<int, QByteArray> roles = this->roleNames();
    QHash<QByteArray, int> typesForNameHash;

    foreach (const QByteArray &val, roles.values())
        typesForNameHash[val] = roles.key(val);

    return typesForNameHash;
}

//void Models::ListItem::fromQSQLRecord(const QSqlRecord &result)
//{
//    if (this->nameToRoles.empty())
//    {
//        QHash<int, QByteArray> roles = this->roleNames();

//        foreach (const QByteArray &val, roles.values())
//            this->nameToRoles[val] = roles.key(val);
//    }
//    for (int i = 0; i < result.count(); i++)
//        this->setData(this->nameToRoles[result.fieldName(i).toLatin1()], result.value(i));
//}

//QString Models::ListItem::toSQLQuery(const QString &table) const
//{
//    QString queryBase("INSERT OR REPLACE INTO " + table + " (");
//    QHash<int, QByteArray> roles = this->roleNames();
//    QList<int> roleKeys = roles.keys();
//    QString queryValues(" VALUES(");
//    for (int i = 0; i < roles.count(); i++)
//    {
//        int roleKey = roleKeys.at(i);
//        QVariant val = this->data(roleKey);

//        queryBase += roles[roleKey];
//        queryValues += (val.type() == QVariant::String || val.type() == QVariant::Url) ?
//                    ("\'" + val.toString() + "\'") : val.toString();
//        queryBase += (i + 1 < roles.count()) ? ", " : ")";
//        queryValues += (i + 1 < roles.count()) ? ", " : ");";
//    }
//    return queryBase + queryValues;
//}

void Models::ListItem::triggerItemUpdate()
{
    emit dataChanged();
}

bool Models::ListItem::operator<(const Models::ListItem &nextElem)
{
    Q_UNUSED(nextElem);
    return false;
}
