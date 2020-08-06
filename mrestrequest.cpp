/*******************************************************************************
Copyright (C) 2020 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/


#include "mrestrequest.h"
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QJsonParseError>
#include <QDebug>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(crequest, "request")

/*!
 * \defgroup Network Network communication with Web API
 * @{
 */

/*!
 * \addtogroup Network
 * \class MRestRequest
 * \brief base equest for mrbabu.com API
 *
 * Base request does nothing but provides common functionality needed for
 * communication.
 *
 * When subclassing, implement your custom parse() method and add a signal to
 * return parsing result to logic classes.
 *
 * Also, you *have to* specify request type by setting mType member variable.
 * If you don't, your subclass will not work! It will print an error when
 * MRestRequest::Send() is used.
 */
MRestRequest::MRestRequest(const QUrl& url) :
    QObject(),
    m_priority(Priority::Normal),
    m_type(Type::None),
    m_url(url)
{
    m_requestTimer = new QTimer(this);
    m_requestTimer->setSingleShot(true);
    setRequestTimeout(5000);
    connect(m_requestTimer, &QTimer::timeout,
            this, &MRestRequest::retry);
}

MRestRequest::~MRestRequest()
{
}

/*!
 * \brief Set URL of this request. Overrides the QUrl set in the constructor
 * \param url of the destination server
 */
void MRestRequest::setAddress(const QUrl &url)
{
    m_url = url;
}

/*!
 * \brief Sets request timeout.
 * \param milliseconds
 */
void MRestRequest::setRequestTimeout(const quint32 msec)
{
    m_requestTimeout = msec;

    if (m_requestTimer) {
        m_requestTimer->setInterval(int(m_requestTimeout));
    }
}

/*!
 * Returns the address associated with this request.
 */
QUrl MRestRequest::address() const
{
    return m_url;
}

/*!
 * Sets request priority to \a priority.
 */
void MRestRequest::setPriority(const MRestRequest::Priority priority)
{
    m_priority = priority;
}

/*!
 * \brief Check if priority is higher then in given request
 * \param request for comparison
 * \return true if this priority is higher, false otherwise
 */
bool MRestRequest::isHigherPriority(const MRestRequest& request)
{
    return m_priority > request.m_priority;
}

/*!
 * \brief send request with given network manager
 * \param manager network access manager
 */
void MRestRequest::sendWith(QNetworkAccessManager* manager)
{
    m_networkManager = manager;
    m_requestRetryCounter = 0;
    send();
    m_replyData.clear();
}

/*!
 * \return JSON document with reply received from server.
 */
QJsonDocument MRestRequest::document() const
{
    return m_replyDocument;
}

/*!
 * \return Reply network error received from server.
 */
QString MRestRequest::lastError() const
{
    return m_lastError;
}

/*!
 * \return Raw data reply received from server.
 */
QByteArray MRestRequest::rawData() const
{
    return m_replyData;
}

/*!
 * Sets the maximal number of retries to \a retryLimit. MRestRequest is retried
 * when the previous request reaches a timeout.
 */
void MRestRequest::setRetryLimit(const uint retryLimit)
{
    m_maxRequestRetryCount = retryLimit;
}

/*!
 * Returns number of times this request has been retried.
 */
uint MRestRequest::retryCount() const
{
    return m_requestRetryCounter;
}

MRestRequest::Type MRestRequest::type() const
{
    return m_type;
}

void MRestRequest::setQuiet(const bool isQuiet)
{
    m_quiet = isQuiet;
}

bool MRestRequest::isQuiet() const
{
    return m_quiet;
}

QByteArray MRestRequest::token() const
{
    return m_token;
}

void MRestRequest::setToken(const QByteArray &token)
{
    m_token = token;
}

void MRestRequest::setDocument(const QJsonDocument &document)
{
    m_requestDocument = document;
}

/*!
 * \brief sends request using method specified in mType (Pup, Post, Get, Delete).
 *
 * If mType is not explicitly set, this function will bail out (with error).
 */
void MRestRequest::send()
{
    Q_ASSERT(m_networkManager);
    if (m_quiet == false) {
    qCInfo(crequest) << m_type << m_url.toDisplayString()
                     << m_requestRetryCounter
                     << m_requestDocument;
    }
    m_replyData.clear();
    QNetworkRequest request(m_url);
    request.setOriginatingObject(this);
    customizeRequest(request);

    switch (m_type) {
    case Type::None:
        qCCritical(crequest) << "Request type is set to None - can't send. Please"
                             << "set request type to Put, Post, Get or Delete";
        emit finished();
        return;
    case Type::Put:
        if (isMultiPart()) {
            auto device = requestMultiPart();
            m_activeReply = m_networkManager->put(request, device);
            device->setParent(m_activeReply);
        } else {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            m_activeReply = m_networkManager->put(request, requestData());
        }
        break;
    case Type::Get:
        m_activeReply = m_networkManager->get(request);
        break;
    case Type::Post:
        if (isMultiPart()) {
            auto device = requestMultiPart();
            m_activeReply = m_networkManager->post(request, device);
            device->setParent(m_activeReply);
        } else {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            m_activeReply = m_networkManager->post(request, requestData());
        }
        break;
    case Type::Delete:
        m_activeReply = m_networkManager->deleteResource(request);
        break;
    default: Q_UNREACHABLE(); break;
    }

    connect(m_activeReply, &QNetworkReply::finished,
            this, &MRestRequest::onReplyFinished);
    connect(m_activeReply, &QNetworkReply::readyRead,
            m_requestTimer, static_cast<void(QTimer::*)()>(&QTimer::start));
    connect(m_activeReply, &QNetworkReply::readyRead,
            this, &MRestRequest::onReadyRead);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
    connect(m_activeReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::errorOccurred),
            this, &MRestRequest::onReplyError);
#else
    connect(m_activeReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this, &MRestRequest::onReplyError);
#endif
    m_requestTimer->start();
}

void MRestRequest::customizeRequest(QNetworkRequest &request)
{
    Q_ASSERT_X(!isTokenRequired() || !m_token.isEmpty(),
               objectName().toLatin1(),
               "This request require token and it's not provided!");

    if (!m_token.isEmpty()) {
        request.setRawHeader(QByteArray("Authorization"),
                             QStringLiteral("%1 %2").arg("Bearer", m_token).toLatin1());
    }
}

bool MRestRequest::isMultiPart() const
{
    return false;
}

QByteArray MRestRequest::requestData() const
{
    return m_requestDocument.toJson(QJsonDocument::JsonFormat::Compact);
}

QHttpMultiPart *MRestRequest::requestMultiPart() const
{
    qDebug() << "Reimplement me!";
    return nullptr;
}

void MRestRequest::readReplyData(const QString &requestName,
                                 const QString &status)
{
    QJsonParseError parseError;
    // rawData can still be parsed in another formats
    m_replyDocument = QJsonDocument::fromJson(m_replyData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(crequest) << requestName << status
                            << "Error while parsing json document:"
                            << parseError.errorString();
    } else {
        if (m_quiet == false) {
            qCDebug(crequest) << requestName << status
                              << "Request reply is a valid JSON";
        }
    }
}

/*!
 * \brief resend request if time limit has passed
 */
void MRestRequest::retry()
{
    ++m_requestRetryCounter;
    qCDebug(crequest) << "Retry" << m_requestRetryCounter;
    m_activeReply->disconnect(this);
    m_activeReply->abort();
    m_activeReply->deleteLater();

    if (m_requestRetryCounter >= m_maxRequestRetryCount) {
        qCCritical(crequest, "Request retry limit reached - operation aborted!");

        emit replyError(m_lastError, QNetworkReply::NetworkError::TimeoutError);
        emit finished();
    } else {
        if (m_activeReply->bytesAvailable()) {
            qCInfo(crequest, "Retrying request, %lldB lost.",
                   m_activeReply->bytesAvailable());
        }

        send();
    }
}

/*!
 * \brief catch network error code and store to mLastError as QString
 * \param network error code
 */
void MRestRequest::onReplyError(QNetworkReply::NetworkError code)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr && code != QNetworkReply::NoError) {
        reply->disconnect(this);
        reply->deleteLater();
        m_requestTimer->stop();
        m_lastError = reply->errorString();

        const QString requestName(metaObject()->className());
        const QString status(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                             .toString());
        qCWarning(crequest) << requestName << status << "Error:" << m_lastError;
        qCWarning(crequest).noquote() << rawData();

        if (code == QNetworkReply::TimeoutError) {
            retry();
        } else {
            emit replyError(m_lastError, code);
            emit finished();
        }
    }
}

/*!
 * \brief collect data from server response
 */
void MRestRequest::onReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr) {
        m_replyData += reply->readAll();
    }
}

/*!
 * \brief handle collected data from server response
 */
void MRestRequest::onReplyFinished()
{
    m_requestTimer->stop();
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply == nullptr) {
        qCCritical(crequest) << "Reply is null";
        emit finished();
        return;
    }

    reply->deleteLater();

    const QString requestName(metaObject()->className());
    const QString status(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                         .toString());

    if (!m_replyData.isEmpty()) {
        readReplyData(requestName, status);
    } else {
        qCDebug(crequest) << requestName << status << "Request reply is empty";
    }

    //parse json document according to specific request reply format
    parse();
    emit finished();
}

bool MRestRequest::isTokenRequired() const
{
    return (m_type != Type::None &&
            m_type != Type::Get);
}

void MRestRequest::parse()
{
    if (m_elapsedTimer.isValid()) {
        qCDebug(crequest) << "Request (" << objectName()
                          << ") finished. Elapsed time:"
                          << m_elapsedTimer.elapsed();
    }

    emit requestFinished(m_replyDocument);
}


void MRestRequest::setQuery(const QUrlQuery &query)
{
    m_url.setQuery(query);
}

/*!
 * \fn MRestRequest::parse
 * \brief read QJsonDocument or Rawreturned by server
 *
 * This method should emit parsed data in form of request specific signal
 * because Request object will be deleted by event queue soon after
 * returning from onReplyFinished
 * NOTE!! you should check mReplyDocument and use rawData() if mReplyDocument isNull
 */

/*! @} */
