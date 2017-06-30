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

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QVector>
#include "addressptr.h"

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString civilId READ civilId WRITE setCivilId NOTIFY civilIdChanged)
    Q_PROPERTY(QByteArray password READ password WRITE setPassword NOTIFY passwordChanged)

    Q_PROPERTY(Address* billingAddress READ billingAddress NOTIFY billingAddressChanged)

public:
    User(QObject *parent = nullptr);
    QByteArray id() const;
    QString email() const;
    QString title() const;
    QString firstName() const;
    QString lastName() const;
    QString phone() const;
    QString civilId() const;
    QByteArray password() const;
    void setId(const QByteArray &id);
    void setEmail(const QString& email);
    void setTitle(const QString& title);
    void setFirstName(const QString& name);
    void setLastName(const QString& name);
    void setPhone(const QString& phone);
    void setCivilId(const QString& id);
    void setPassword(const QByteArray& password);
    Address* billingAddress();
    void clear();

signals:
    void emailChanged() const;
    void titleChanged() const;
    void firstNameChanged() const;
    void lastNameChanged() const;
    void phoneChanged() const;
    void civilIdChanged() const;
    void idChanged() const;
    void passwordChanged() const;
    void billingAddressChanged() const;

private:
    QByteArray mId;
    QString mEmail;
    QByteArray mPassword;
    QString mTitle;
    QString mFirstName;
    QString mLastName;
    QString mPhone;
    QString mCivilId;
    //TODO user can have multiple profiles
    enum AddressType { BillingAddress, ShippingAddress};
    QVector<AddressPtr> mAddresses;
};

#endif // USER_H
