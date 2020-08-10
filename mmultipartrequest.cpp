#include "mmultipartrequest.h"

#include <QDebug>

#include <QHttpMultiPart>
#include <QHttpPart>

MMultiPartRequest::MMultiPartRequest(const QUrl& url)
    : MRestRequest(url)
{
}

void MMultiPartRequest::addPart(const QString &key, const QString &value)
{
    qDebug() << "Adding part" << key << value;
    m_stringParts.insert(key, value);
}

void MMultiPartRequest::addPart(const QString &key, const QFileInfo &file)
{
    qDebug() << "Adding part" << key << file.fileName();
    m_fileParts.insert(key, file);
}

bool MMultiPartRequest::isMultiPart() const
{
    return true;
}

QHttpMultiPart* MMultiPartRequest::requestMultiPart() const
{
    // Adapted from:
    // https://stackoverflow.com/questions/38179706/uploading-a-file-in-multipart-form-data-in-qt5

    // TODO: we can probably parent those things to the request itself.

    auto multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for (const QString &key : m_stringParts.uniqueKeys()) {
        for (const QString &value : m_stringParts.values(key)) {
            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
            part.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QString("form-data; name=\"%1\"").arg(key));
            // TODO: this might cause us to lose UTF-8!
            part.setBody(value.toLocal8Bit());
            multiPart->append(part);
        }
    }

    for (const QString &key : m_fileParts.uniqueKeys()) {
        for (const QFileInfo &value : m_fileParts.values(key)) {
            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
            part.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QString("form-data; name=\"%1\"; filename=\"%2\"")
                           .arg(key, value.fileName()));
            auto file = new QFile(value.absoluteFilePath());
            file->setParent(multiPart);
            if (file->open(QIODevice::ReadOnly) == false) {
                qWarning() << "Could not open cached file!"
                           << key << value;
            }

            part.setBodyDevice(file);
            multiPart->append(part);
        }
    }

    return multiPart;
}
