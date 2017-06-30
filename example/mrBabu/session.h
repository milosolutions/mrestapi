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

#ifndef SESSION_H
#define SESSION_H

#include <QByteArray>
#include <QObject>
#include <QPointer>
#include "userptr.h"
#include "config.h"

class RestAPIClient;

class Session : public QObject, public Config
{
    Q_OBJECT
    Q_PROPERTY(User* user READ user NOTIFY userChanged)

public:
    explicit Session(QObject *parent = nullptr);
    ~Session();
    void setClient(RestAPIClient *client);
    Q_INVOKABLE bool hasToken() const;
    Q_INVOKABLE void login(const QString& email, const QByteArray& password);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void registerUser(const QString& email, const QString& password,
                                  const QString& firstName, const QString& lastName,
                                  const QString& phone, const QString& civilId,
                                  const QString& address, const QString& city,
                                  const QString& zip, const QString& country);
    Q_INVOKABLE void getUserInfo();

    User* user() const;

signals:
    void loginSuccessful(const QString& token) const;
    void loginError(const QString& msgs) const;
    void invalidPassword() const;
    void invalidUsername() const;
    void registrationSuccessful(const QString& apiToken) const;
    void registrationError(const QString& errors) const;
    void userChanged(User* user) const;
    void userInfoError(const QString& error) const;

private:
    void onLoginSuccessful(const QString& token);
    void onUserInfo(const QString& firstName,
                    const QString& lastName,
                    const QString& phoneNumber,
                    const QString& civilId,
                    const QString& email);

    QByteArray mToken;
    UserPtr mCurrentUser;
    QPointer<RestAPIClient> mClient;
};

#endif // SESSION_H
