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

#include "registerrequest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(requestRegister, "request.register")

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class RegisterRequest
 * \brief Registers a new user
 */

/*!
 * Creates a new registration request using all registration details.
 *
 * Send it using Register::send()
 */
RegisterRequest::RegisterRequest(const QString& email, const QString& password,
                                 const QString& firstName, const QString& lastName,
                                 const QString& phone, const QString& civilId,
                                 const QString& address, const QString& city,
                                 const QString& zip, const QString& country)
    : MrBabuRequest("register")
{
    if (!email.isEmpty() && !password.isEmpty() && !firstName.isEmpty()
            && !lastName.isEmpty() && !address.isEmpty() && !city.isEmpty()
            && !zip.isEmpty() && !country.isEmpty()) {
        QJsonObject object {
            {"email", QJsonValue(email)},
            {"password", QJsonValue(password)},
            {"first_name", QJsonValue(firstName)},
            {"last_name", QJsonValue(lastName)},
            {"phone", QJsonValue(phone)},
            {"civilid", QJsonValue(civilId)},
            {"address", QJsonValue(address)},
            {"city", QJsonValue(city)},
            {"zipcode", QJsonValue(zip)},
            {"country", QJsonValue(country)},
            {"username", QJsonValue(email)},
            {"token", QJsonValue("")}
        };
        mRequestDocument.setObject(object);
        mPriority = Priority::High;
        mType = Type::Post;
    } else {
        qCDebug(requestRegister) << "Error: missing registration info"
                                 << email << password.length()
                                 << firstName << lastName << phone << civilId
                                 << address << city << zip << country;
    }
}

/*!
 * Emits registrationSuccessful() with a Web API Token when all went OK.
 *
 * Otherwise, emits replyError().
 */
void RegisterRequest::parse()
{
    const QJsonObject object(mReplyDocument.object());
    const QString token(object.value("Token").toString());

    if (token.isEmpty()) {
        qCDebug(requestRegister) << "Error in parsing server reply"
                                 << mReplyDocument.toJson()
                                 << token;
        emit replyError("Error in parsing server reply");
        return;
    }

    qCDebug(requestRegister) << "Registration successful" << token;
    emit registrationSuccessful(token);
}

/*! @} */
