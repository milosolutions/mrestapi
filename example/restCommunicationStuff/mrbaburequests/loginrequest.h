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

#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "mrbaburequest.h"

#include <QString>
#include <QStringList>
#include <QObject>

class LoginRequest : public MrBabuRequest
{
    Q_OBJECT

public:
    LoginRequest(const QString &email = QString::null,
                 const QString &password = QString::null);

signals:
    void loginSuccessful(const QString &token) const;
    void invalidPassword() const;
    void invalidUsername() const;
    void userInfo(const QString& firstName,
                  const QString& lastName,
                  const QString& phoneNumber,
                  const QString& civilId,
                  const QString& email) const;
protected:
    virtual void parse() override final;
};

#include <QSharedPointer>
using LoginRequestPtr = QSharedPointer<LoginRequest>;

#endif // LOGINREQUEST_H
