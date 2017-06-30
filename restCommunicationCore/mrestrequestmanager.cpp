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

#include "mrestrequestmanager.h"
#include "mrestrequest.h"

#include <QNetworkAccessManager>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(rm, "requestManager")

/*!
 * \addtogroup Network
 * @{
 */

/*!
 * \class MRestRequestManager
 * \brief Allow sending request in queue
 *
 * Manager for general Request class. Provides way to
 * control number of concurrent downloads in network.
 */

/*!
 * Constructs a new network access manager.
 */
MRestRequestManager::MRestRequestManager(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::sslErrors,
            this, &MRestRequestManager::onSslErrors);
    mIgnoreSslErrors = false;

}

/*!
 * \brief send request with use of queue
 * \param request
 * \param type what type of HTTP message to send (PUT, POST, GET, DELETE)
 *
 * MRestRequestManager takes ownership of the pointer (it will keep it alive until
 * the request result is received).
 */
void MRestRequestManager::send(RestRequestPtr request)
{
    if (mActiveRequests.size() < MaxActiveRequestsCount) {
        mActiveRequests.append(request);

        request->sendWith(networkManager);
        QObject::connect(request.data(), &RestRequest::finished,
                this, &MRestRequestManager::onRequestFinished);
    } else {
        pendingRequests.enqueue(request);
    }
}

/*!
* \brief setting ignore to all certificate errors
*/
void MRestRequestManager::ignoreSslErrors()
{
    mIgnoreSslErrors = true;
}

/*!
 * \brief handle request queue
 */
void MRestRequestManager::onRequestFinished()
{
    removeActiveRequest(sender());
    if (!pendingRequests.isEmpty())
        send(pendingRequests.dequeue());
}

/*!
 * Removes request (taken from \a sender pointer) from the list of active requests.
 * Most usually, the request is being deleted here.
 */
void MRestRequestManager::removeActiveRequest(QObject *sender)
{
    if (!sender) {
        qCDebug(rm) << "Cannot remove null active request pointer";
        return;
    }

    foreach (const RestRequestPtr &request, mActiveRequests) {
        if (request.data() == sender) {
            mActiveRequests.removeOne(request);
            return;
        }
    }

    qCDebug(rm) << "Could not find the request to remove" << sender;
}

/*!
 *
 * \brief handle networkManager onSslErrors
 * \param reply
 * \param errors
 * handle onSslErrors. ignore SSL errors or abort and emit sslErrorsChanged
*/

void MRestRequestManager::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    if (mIgnoreSslErrors) {
        reply->ignoreSslErrors();
        return;
    }

    reply->deleteLater();
    mLastSslErrors.clear();
    foreach (QSslError error, errors) {
        mLastSslErrors << error.errorString();
    }

    emit sslErrorsChanged(mLastSslErrors);
}

/*! @} */
