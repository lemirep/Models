/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#ifndef JSONLISTITEM_H
#define JSONLISTITEM_H

#include "ListItem.h"
#include <QJsonValue>

namespace Models
{

class JSONListItemBuilder
{
private:
    JSONListItemBuilder(Models::ListItem *item);

    Models::ListItem *item;

public:
    virtual ~JSONListItemBuilder();
    static void fromQJsonValue(const QJsonValue &jsonValue, Models::ListItem *item);

protected :
    static QHash<QJsonValue::Type,
    void (JSONListItemBuilder::*)(const QString &keyName,
                                  const QJsonValue &jsonValue)> jsonToValue;
    static QHash<QJsonValue::Type,
    void (JSONListItemBuilder::*)(const QString &keyName,
                                  const QJsonValue &jsonValue)> initJsonToValueHash();
    QHash<QByteArray, int> nameToRoles;

    virtual void valueFromQJsonObject(const QString &keyName = "", const QJsonValue &jsonValue = QJsonValue());
    virtual void valueFromQJsonArray(const QString &keyName = "", const QJsonValue &jsonValue = QJsonValue());
    virtual void valueFromScalar(const QString &keyName = "", const QJsonValue &jsonValue = QJsonValue());
    virtual void valueFromNullOrUndefined(const QString &keyName = "", const QJsonValue &jsonValue = QJsonValue());
};
}

#endif // JSONLISTITEM_H
