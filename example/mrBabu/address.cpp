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

#include "address.h"

/*!
 * \defgroup Example Example code
 * @{
 */

/*!
 * \class Address
 * \brief User address data
 */

Address::Address(QObject *parent) :
    QObject(parent)
{
    //TODO
}

QString Address::firstName() const
{
    return mFirstName;
}

QString Address::lastName() const
{
    return mLastName;
}

QString Address::phone() const
{
    return mPhone;
}

QString Address::address() const
{
    return mAddress;
}

QString Address::city() const
{
    return mCity;
}

QString Address::country() const
{
    return mCountry;
}

QString Address::zip() const
{
    return mZip;
}

void Address::setFirstName(const QString& name)
{
    if (mFirstName != name) {
        mFirstName = name.toUtf8();
        emit firstNameChanged();
    }
}

void Address::setLastName(const QString& name)
{
    if (mLastName != name) {
        mLastName = name.toUtf8();
        emit lastNameChanged();
    }
}

void Address::setPhone(const QString& phone)
{
    if (mPhone != phone) {
        mPhone = phone.toUtf8();
        emit phoneChanged();
    }
}

void Address::setAddress(const QString& address)
{
    if (mAddress == address)
        return;

    mAddress = address.toUtf8();
    emit addressChanged();
}

void Address::setCity(const QString& city)
{
    if (mCity != city) {
        mCity = city.toUtf8();
        emit cityChanged();
    }
}

void Address::setCountry(const QString& country)
{
    if (mCountry != country) {
        mCountry = country.toUtf8();
        emit countryChanged();
    }

}

void Address::setZip(const QString& zip)
{
    if (mZip != zip) {
        mZip = zip.toUtf8();
        emit zipChanged();
    }
}

/*! @} */
