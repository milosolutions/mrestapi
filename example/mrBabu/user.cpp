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

#include "user.h"
#include "address.h"

/*!
 * \addtogroup Example
 * @{
 */

/*!
 * \class User
 * \brief Represetation of application user
 */

User::User(QObject *parent) :
    QObject(parent)
{
    AddressPtr billingAddress = AddressPtr::create();
    mAddresses.append(billingAddress);
}

QString User::email() const
{
    return mEmail;
}

QString User::title() const
{
    return mTitle;
}

QString User::firstName() const
{
    return mFirstName;
}

QString User::lastName() const
{
    return mLastName;
}

QString User::phone() const
{
    return mPhone;
}

QString User::civilId() const
{
    return mCivilId;
}

QByteArray User::password() const
{
    return mPassword;
}

void User::setEmail(const QString& email)
{
    if (mEmail != email) {
        mEmail = email;
        emit emailChanged();
    }
}

void User::setTitle(const QString& title)
{
    if (mTitle != title) {
        mTitle = title;
        emit titleChanged();
    }
}

void User::setFirstName(const QString& name)
{
    if (mFirstName != name) {
        mFirstName = name;
        emit firstNameChanged();
    }
}

void User::setLastName(const QString& name)
{
    if (mLastName != name) {
        mLastName = name;
        emit lastNameChanged();
    }
}

void User::setPhone(const QString& phone)
{
    if (mPhone != phone) {
        mPhone = phone;
        emit phoneChanged();
    }
}

void User::setCivilId(const QString& id)
{
    if (mCivilId != id) {
        mCivilId = id;
        emit civilIdChanged();
    }
}

void User::setPassword(const QByteArray& password)
{
    if (mPassword != password) {
        mPassword = password;
        emit passwordChanged();
    }
}

Address *User::billingAddress()
{
    if (mAddresses.isEmpty()) {
        AddressPtr billingAddress = AddressPtr::create();
        mAddresses.append(billingAddress);
    }

    return mAddresses.first().data();
}

void User::clear()
{
    mId.clear();
    mEmail.clear();
    mPassword.clear();
    mTitle.clear();
    mFirstName.clear();
    mLastName.clear();
    mPhone.clear();
    mCivilId.clear();
    mAddresses.clear();
}

QByteArray User::id() const
{
    return mId;
}

void User::setId(const QByteArray &id)
{
    if (mId != id) {
        mId = id;
        emit idChanged();
    }
}

/*! @} */
