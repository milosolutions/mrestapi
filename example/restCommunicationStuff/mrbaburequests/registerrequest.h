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

#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include "mrbaburequest.h"

#include <QObject>

class RegisterRequest : public MrBabuRequest
{
    Q_OBJECT

public:
    RegisterRequest(const QString& email, const QString& password,
                    const QString& firstName, const QString& lastName,
                    const QString& phone, const QString& civilId,
                    const QString& address, const QString& city,
                    const QString& zip, const QString& country);

signals:
    void registrationSuccessful(const QString &apiToken) const;

protected:
    virtual void parse() override final;
};

#endif // REGISTERREQUEST_H
