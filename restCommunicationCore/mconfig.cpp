/*******************************************************************************
  Copyright (C) 2016 Milo Solutions
  Contact: https://www.milosolutions.com

  This file is part of Milo Code Database, which is a collection of useful code
  snippets often reused within Milo Solutions. As such, this code is present in
  many projects done by Milo Solutions and does not constitute a copyright
  infridgement.

  You are entitled to do anything you please with this code, just as with the
  rest of code you bought. Files not containing this notice were written
  specifically for this project and have not been shared with any other party
  within or without Milo.
*******************************************************************************/

#include "MConfig.h"
#include <QSettings>

/*!
 * \defgroup MConfig Configuration and settings
 * @{
 */

/*!
 * \class MConfig
 * \brief Configuration object base
 *
 * Class provides simplified use for storing
 * configurable values. Usage:
 * 1. Subclass MConfig
 * 2. Define group name (mGroupName)
 * 3. For each member of subclassed object provide info to mValues hash using ValuePtr object.
 * 4. Make sure yor application does have QCoreApplication::organizationName and
 * QCoreApplication::applicationName set.
 */

MConfig::MConfig(const QByteArray& groupName) :
    mGroupName(groupName)
{
    //Nothing
}

/*!
 * \brief load all values using QSettings
 */
void MConfig::load()
{
    QSettings settings;
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        copyValue(mValues.value(key).ptr,
                  mValues.value(key).type,
                  settings.value(key));
    }
}

/*!
 * \brief save all values using QSettings
 */
void MConfig::save()
{
    QSettings settings;
    settings.beginGroup(mGroupName);
    foreach (const QByteArray& key, mValues.keys()) {
        QVariant value(mValues.value(key).type,
                       mValues.value(key).ptr);
        settings.setValue(key, value);
    }
}

/*!
 * \brief copy variant value to given pointer using defined type
 * \param dst
 * \param type
 * \param value
 */

#define COPY_TYPE(type) \
{\
    type *ptr = static_cast<type*>(dst);\
    *ptr = value.value<type>();\
} break;

void MConfig::copyValue(void *dst, int type, const QVariant& value)
{
    if (value.isNull()) {
        return;
    }

    Q_ASSERT(value.canConvert(type));

    switch (type) {
    case QMetaType::Int:        COPY_TYPE(int)
    case QMetaType::QByteArray: COPY_TYPE(QByteArray)
    default:
        qFatal("MConfig: type unsupported!");
    }
}

/*! @} */
