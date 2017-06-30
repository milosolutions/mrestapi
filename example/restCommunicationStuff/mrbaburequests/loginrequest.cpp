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

#include "loginrequest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(requestLogin, "request.login")

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class LoginRequest
 * \brief Request performs login operation using email/ password combination
 *
 * API reply contains a Token, which can be used to perform operations reserved
 * to authenticated users.
 */

/*!
 * Setup the request using user's \a email and \a password.
 *
 * Use LoginRequest::send() to send it to the server.
 */
LoginRequest::LoginRequest(const QString &email, const QString &password)
    : MrBabuRequest("login")
{
    if (!email.isEmpty() && !password.isEmpty()) {
        QJsonObject object;
        object.insert("username", QJsonValue(email));
        object.insert("password", QJsonValue(password));
        mRequestDocument.setObject(object);
        mPriority = Priority::High;
        mType = Type::Post;
    } else {
        qCDebug(requestLogin) << "Error: missing login info"
                                 << email << password.length();
    }
}

/*!
 * Parses the reply, extracting API Token if everything went well (emited in
 * loginSuccessful().
 *
 * When an invalid password was specified, emits invalidPassword(),
 * when an invalid login was specified, emits invalidUsername().
 *
 * On all other errors, emits the standard replyError().
 */
void LoginRequest::parse()
{
    const QJsonObject object(mReplyDocument.object());

    /*
    "non_field_errors": [
        "invalid login"
    ]
    // OR
    "non_field_errors": [
        "Staff users can not log in via the rest api"
    ]
    */

    const QString errors("non_field_errors");
    if (object.contains(errors)) {
        const QJsonArray errorMessages(object.value(errors).toArray());

        QStringList errorMsgStrings;
        foreach (const QJsonValue &value, errorMessages) {
            const QString message(value.toString());
            errorMsgStrings << message;

            if (message.contains("invalid password")) {
                emit invalidPassword();
                return;
            }

            if (message.contains("invalid login")) {
                emit invalidUsername();
                return;
            }
        }

        qCDebug(requestLogin()) << "Server returned errors:"
                                << errorMsgStrings;
        emit replyError(errorMsgStrings.join(". "));
        return;
    }

    const QString token(object.value("token").toString());

    if (token.isEmpty()) {
        qCDebug(requestLogin) << "Error in parsing server reply"
                              << mReplyDocument.toJson()
                              << token;
        emit replyError("Error in parsing server reply");
        return;
    }

    const QString firstName(object.value("first_name").toString());
    const QString lastName(object.value("last_name").toString());
    const QString phoneNumber(object.value("phone").toString());
    const QString civilId(object.value("civilid").toString());
    const QString email(object.value("email").toString());

    emit userInfo(firstName, lastName, phoneNumber, civilId, email);

    qCDebug(requestLogin) << "Login successful" << token.length();
    emit loginSuccessful(token);
}

/*! @} */
