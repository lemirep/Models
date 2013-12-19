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

#include "JSONListItemBuilder.h"
#include <QDebug>


QHash<QJsonValue::Type,
void (Models::JSONListItemBuilder::*)
(const QString &keyName,
 const QJsonValue &jsonValue)> Models::JSONListItemBuilder::jsonToValue = Models::JSONListItemBuilder::initJsonToValueHash();

QHash<QJsonValue::Type,
void (Models::JSONListItemBuilder::*)
(const QString &keyName,
 const QJsonValue &jsonValue)> Models::JSONListItemBuilder::initJsonToValueHash()
{
    QHash<QJsonValue::Type,
            void (Models::JSONListItemBuilder::*)
            (const QString &keyName,
             const QJsonValue &jsonValue)> hash;

    hash[QJsonValue::Null] = &Models::JSONListItemBuilder::valueFromNullOrUndefined;
    hash[QJsonValue::Undefined] = &Models::JSONListItemBuilder::valueFromNullOrUndefined;
    hash[QJsonValue::Object] = &Models::JSONListItemBuilder::valueFromQJsonObject;
    hash[QJsonValue::Array] = &Models::JSONListItemBuilder::valueFromQJsonArray;
    hash[QJsonValue::Bool] = &Models::JSONListItemBuilder::valueFromScalar;
    hash[QJsonValue::String] = &Models::JSONListItemBuilder::valueFromScalar;
    hash[QJsonValue::Double] = &Models::JSONListItemBuilder::valueFromScalar;

    return hash;
}

Models::JSONListItemBuilder::JSONListItemBuilder(Models::ListItem *item)
    : item(item)
{
}

Models::JSONListItemBuilder::~JSONListItemBuilder()
{
}

void Models::JSONListItemBuilder::fromQJsonValue(const QJsonValue &jsonValue, Models::ListItem *item)
{
    if (item == NULL)
        return ;

    Models::JSONListItemBuilder instance(item);

    instance.nameToRoles = item->roleTypesFromName();
    (instance.*jsonToValue[jsonValue.type()])("", jsonValue);
}

void Models::JSONListItemBuilder::valueFromQJsonObject(const QString &keyName, const QJsonValue &jsonValue)
{
    QJsonObject obj = jsonValue.toObject();

    foreach (const QString &keyName, obj.keys())
    {
        QJsonValue val = obj.value(keyName);
        (this->*jsonToValue[val.type()])(keyName, val);
    }
}

void Models::JSONListItemBuilder::valueFromQJsonArray(const QString &keyName, const QJsonValue &jsonValue)
{
    QJsonArray array = jsonValue.toArray();

    foreach (const QJsonValue &val, array)
        (this->*jsonToValue[val.type()])(keyName, val);
}

void Models::JSONListItemBuilder::valueFromScalar(const QString &keyName, const QJsonValue &jsonValue)
{
    if (this->nameToRoles.contains(keyName.toLocal8Bit()))
        this->item->setData(this->nameToRoles[keyName.toLocal8Bit()], jsonValue.toVariant());
}

void Models::JSONListItemBuilder::valueFromNullOrUndefined(const QString &keyName, const QJsonValue &jsonValue)
{
    qDebug() << "Value is null or undefined for " << keyName;
}


