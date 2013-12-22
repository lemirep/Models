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

#include "JSONListItemBinder.h"
#include <QDebug>


QHash<QJsonValue::Type,
void (Models::JSONListItemBinder::*)
(const QString &keyName,
 const QJsonValue &jsonValue)> Models::JSONListItemBinder::jsonToValue = Models::JSONListItemBinder::initJsonToValueHash();

QHash<QJsonValue::Type,
void (Models::JSONListItemBinder::*)
(const QString &keyName,
 const QJsonValue &jsonValue)> Models::JSONListItemBinder::initJsonToValueHash()
{
    QHash<QJsonValue::Type,
            void (Models::JSONListItemBinder::*)
            (const QString &keyName,
             const QJsonValue &jsonValue)> hash;

    hash[QJsonValue::Null] = &Models::JSONListItemBinder::valueFromNullOrUndefined;
    hash[QJsonValue::Undefined] = &Models::JSONListItemBinder::valueFromNullOrUndefined;
    hash[QJsonValue::Object] = &Models::JSONListItemBinder::valueFromQJsonObject;
    hash[QJsonValue::Array] = &Models::JSONListItemBinder::valueFromQJsonArray;
    hash[QJsonValue::Bool] = &Models::JSONListItemBinder::valueFromScalar;
    hash[QJsonValue::String] = &Models::JSONListItemBinder::valueFromScalar;
    hash[QJsonValue::Double] = &Models::JSONListItemBinder::valueFromScalar;

    return hash;
}

Models::JSONListItemBinder::JSONListItemBinder(Models::ListItem *item)
    : item(item)
{
}

Models::JSONListItemBinder::~JSONListItemBinder()
{
}

void Models::JSONListItemBinder::fromQJsonValue(const QJsonValue &jsonValue, Models::ListItem *item)
{
    if (item == NULL)
        return ;

    Models::JSONListItemBinder instance(item);

    instance.nameToRoles = item->roleTypesFromName();
    (instance.*jsonToValue[jsonValue.type()])("", jsonValue);
}

void Models::JSONListItemBinder::valueFromQJsonObject(const QString &keyName, const QJsonValue &jsonValue)
{
    QJsonObject obj = jsonValue.toObject();

    QStringList keys = obj.keys();
    foreach (const QString &keyName, keys)
    {
        QJsonValue val = obj.value(keyName);
        (this->*jsonToValue[val.type()])(keyName, val);
    }
}

void Models::JSONListItemBinder::valueFromQJsonArray(const QString &keyName, const QJsonValue &jsonValue)
{
    // IF KEYNAME VALUE IS OF QOBJECT* TYPE AND IS A LISTMODEL
    // FOR EACH VALUE IN ARRAY CREATE NEW OBJECT OF MODEL->PROTOTYPE->GETNEWITEMINSTANCE
    QJsonArray array = jsonValue.toArray();
    Models::ListModel *tmpModel = NULL;
    if (this->item->data(this->nameToRoles[keyName.toLocal8Bit()]).type() == QMetaType::QObjectStar &&
            qobject_cast<Models::SubListedListItem *>(this->item) != NULL &&
            (tmpModel = qobject_cast<Models::ListModel*>(
                 qvariant_cast<QObject *>(
                     this->item->data(this->nameToRoles[keyName.toLocal8Bit()])))) != NULL)
    {
        foreach (const QJsonValue &val, array)
        {
            Models::ListItem *subItem = tmpModel->getPrototype()->getNewItemInstance(this->item);
            JSONListItemBinder::fromQJsonValue(val, subItem);
            qobject_cast<Models::SubListedListItem *>(this->item)->submodel()->appendRow(subItem);
        }
    }
    else
        foreach (const QJsonValue &val, array)
            (this->*jsonToValue[val.type()])(keyName, val);
}

void Models::JSONListItemBinder::valueFromScalar(const QString &keyName, const QJsonValue &jsonValue)
{
    if (this->nameToRoles.contains(keyName.toLocal8Bit()))
        this->item->setData(this->nameToRoles[keyName.toLocal8Bit()], jsonValue.toVariant());
}

void Models::JSONListItemBinder::valueFromNullOrUndefined(const QString &keyName, const QJsonValue &jsonValue)
{
    qDebug() << "Value is null or undefined for " << keyName;
}


