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

#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QByteArray>
#include <QList>

class Address : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString zip READ zip WRITE setZip NOTIFY zipChanged)

public:
    Address(QObject *parent  = nullptr);
    QString firstName() const;
    QString lastName() const;
    QString phone() const;
    QString address() const;
    QString city() const;
    QString country() const;
    QString zip() const;
    void setFirstName(const QString& name);
    void setLastName(const QString& name);
    void setPhone(const QString& phone);
    void setAddress(const QString &address);
    void setCity(const QString& city);
    void setCountry(const QString& country);
    void setZip(const QString& zip);

signals:
    void firstNameChanged() const;
    void lastNameChanged() const;
    void phoneChanged() const;
    void cityChanged() const;
    void countryChanged() const;
    void zipChanged() const;
    void addressChanged() const;

private:
    //TODO replace QByteArray with QString for all members
    QByteArray mFirstName;
    QByteArray mLastName;
    QByteArray mPhone;
    QByteArray mAddress;
    QByteArray mCity;
    QByteArray mCountry;
    QByteArray mZip;
};

#endif // ADDRESS_H
