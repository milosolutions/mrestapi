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

#include "userinforequest.h"

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(requestUserInfo, "request.userInfo")

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class UserInfoRequest
 * \brief Gets current user data
 *
 * Name, email, phone, etc.
 */

/*!
 * Contructs a new request. \a token is required and needs to be valid (you can
 * get it by logging in or registering).
 */
UserInfoRequest::UserInfoRequest(const QByteArray& token)
    : MrBabuRequest("change-user-data")
{
    if (!token.isEmpty()) {
        QJsonObject object {
            {"token", QJsonValue(QString(token))},
            {"first_name", QJsonValue("")},
            {"last_name", QJsonValue("")},
            {"username", QJsonValue("")},
            {"phone", QJsonValue("")},
            {"civilid", QJsonValue("")},
            {"email", QJsonValue("")}
        };

        mRequestDocument.setObject(object);
        mPriority = Priority::Normal;
        mType = Type::Post;
    } else {
        qCDebug(requestUserInfo) << "Error: missing user token" << token;
    }
}

/*!
 * All data is returned on success, by emitting userInfo() signal.
 */
void UserInfoRequest::parse()
{
    const QJsonObject object(mReplyDocument.object());

    const QString firstName(object.value("first_name").toString());
    const QString lastName(object.value("last_name").toString());
    const QString phoneNumber(object.value("phone").toString());
    const QString civilId(object.value("civilid").toString());
    const QString email(object.value("email").toString());

    if (firstName.isEmpty() && lastName.isEmpty()) {
        qCDebug(requestUserInfo) << mReplyDocument.toJson();
    }

    qCDebug(requestUserInfo).noquote() << "Received user info:"
                                       << firstName.left(1) << lastName.left(1)
                                       << phoneNumber.length()
                                       << civilId.length() << email.length();
    emit userInfo(firstName, lastName, phoneNumber, civilId, email);
}

/*! @} */
