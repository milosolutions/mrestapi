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

#include "session.h"
#include "user.h"
#include "restapiclient.h"
#include "mrbaburequests/loginrequest.h"
#include "mrbaburequests/logoutrequest.h"
#include "mrbaburequests/registerrequest.h"
#include "mrbaburequests/userinforequest.h"

#include <QSharedPointer>
#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(session, "core.session")

/*!
 * \addtogroup Example
 * @{
 */

/*! \class Session
 *  \brief Application sessio management
 */

Session::Session(QObject *parent) : QObject(parent), Config("Session")
{
    mCurrentUser = UserPtr::create();
    CONFIG_VALUE(mToken, QMetaType::QByteArray);
    load();
}

Session::~Session()
{
    save();
}

void Session::setClient(RestAPIClient *client)
{
    mClient = client;
}

bool Session::hasToken() const
{
    return !mToken.isEmpty();
}

User* Session::user() const
{
    return mCurrentUser.data();
}

void Session::onLoginSuccessful(const QString &token)
{
    mToken = token.toUtf8();
    emit loginSuccessful(token);
}

void Session::onUserInfo(const QString &firstName, const QString &lastName,
                         const QString &phoneNumber, const QString &civilId,
                         const QString &email)
{
    if (!firstName.isEmpty()) user()->setFirstName(firstName);
    if (!lastName.isEmpty()) user()->setLastName(lastName);
    if (!phoneNumber.isEmpty()) user()->setPhone(phoneNumber);
    if (!civilId.isEmpty()) user()->setCivilId(civilId);
    if (!email.isEmpty()) user()->setEmail(email);
}

void Session::login(const QString &email, const QByteArray &password)
{
    if (mClient.isNull()) {
        qCDebug(session) << "Client class not set - cannot send login request!";
        return;
    }

    auto request = QSharedPointer<LoginRequest>::create(email, password);

    connect(request.data(), &LoginRequest::loginSuccessful,
            this, &Session::onLoginSuccessful);
    connect(request.data(), &LoginRequest::replyError,
            this, &Session::loginError);
    connect(request.data(), &LoginRequest::invalidPassword,
            this, &Session::invalidPassword);
    connect(request.data(), &LoginRequest::invalidUsername,
            this, &Session::invalidUsername);
    connect(request.data(), &LoginRequest::userInfo,
            this, &Session::onUserInfo);

    mClient->send(request);
}

void Session::logout()
{
    if (mClient.isNull()) {
        qCDebug(session) << "Client class not set - cannot send logout request!";
        return;
    }

    auto request = QSharedPointer<LogoutRequest>::create();

    connect(request.data(), &LogoutRequest::replyError,
            this, &Session::loginError);

    mClient->send(request);
    mToken.clear();
    mCurrentUser->clear();
}

void Session::registerUser(const QString& email, const QString& password,
                           const QString& firstName, const QString& lastName,
                           const QString& phone, const QString& civilId,
                           const QString& address, const QString& city,
                           const QString& zip, const QString& country)
{
    if (mClient.isNull()) {
        qCDebug(session) << "Client class not set - cannot send login request!";
        return;
    }

    auto request = QSharedPointer<RegisterRequest>::create(email, password,
                                                           firstName, lastName,
                                                           phone, civilId,
                                                           address, city,
                                                           zip, country);
    connect(request.data(), &RegisterRequest::registrationSuccessful,
            this, &Session::registrationSuccessful);
    connect(request.data(), &RegisterRequest::registrationSuccessful,
            this, &Session::onLoginSuccessful);
    connect(request.data(), &RegisterRequest::replyError,
            this, &Session::registrationError);

    mClient->send(request);
}

void Session::getUserInfo()
{
    if (mClient.isNull()) {
        qCDebug(session) << "Client class not set - cannot send user info request!";
        return;
    }

    if (mToken.isEmpty()) {
        qCDebug(session) << "Token missing - cannot send user info request!";
        return;
    }

    //qCDebug(session) << "Getting user data with token:" << mToken;
    auto request = QSharedPointer<UserInfoRequest>::create(mToken);
    connect(request.data(), &UserInfoRequest::userInfo,
            this, &Session::onUserInfo);
    connect(request.data(), &UserInfoRequest::replyError,
            this, &Session::userInfoError);
    mClient->send(request);
}

/*! @} */
