#include "SQLiteListItemBinder.h"

Models::SQLiteListItemBinder::SQLiteListItemBinder()
{
}

void Models::SQLiteListItemBinder::fromQSqlRecord(const QSqlRecord &record, Models::ListItem *item)
{
    if (item == NULL)
        return ;
    QHash<QByteArray, int> nameToRoles = item->roleTypesFromName();
    for (int i = 0; i < record.count(); i++)
        item->setData(nameToRoles[record.fieldName(i).toLocal8Bit()], record.value(i));
}

QString Models::SQLiteListItemBinder::toQSqlQuery(Models::ListItem *item, const QString &tableName)
{
        if (item == NULL || tableName.isEmpty())
            return "";

        QString queryBase("INSERT OR REPLACE INTO " + tableName + " (");
        QString queryValues(" VALUES(");
        QHash<int, QByteArray> roles = item->roleNames();
        QList<int> roleKeys = roles.keys();

        for (int i = 0; i < roles.count(); i++)
        {
            int roleKey = roleKeys.at(i);
            QVariant val = item->data(roleKey);

            queryBase += roles[roleKey];
            queryValues += (val.type() == QMetaType::QString || val.type() == QMetaType::QUrl) ?
                        ("\'" + val.toString() + "\'") : val.toString();
            queryBase += (i + 1 < roles.count()) ? ", " : ")";
            queryValues += (i + 1 < roles.count()) ? ", " : ");";
        }

        return queryBase + queryValues;
}
