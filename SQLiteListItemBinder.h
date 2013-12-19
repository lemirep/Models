#ifndef SQLITELISTITEMBINDER_H
#define SQLITELISTITEMBINDER_H

#include "SubListedListItem.h"
#include <QSqlRecord>

namespace Models
{

class SQLiteListItemBinder
{
private:
    SQLiteListItemBinder();

public :
    static void fromQSqlRecord(const QSqlRecord &record, Models::ListItem *item);
    static QString toQSqlQuery(Models::ListItem *item, const QString &tableName);
};

}

#endif // SQLITELISTITEMBINDER_H
