#include "mimagerequest.h"

#include <QFile>
#include <QFileInfo>

ImageRequest::ImageRequest(const QUrl& url, const QString &cachePath)
    : MRestRequest(url),
      m_cachePath(cachePath)
{
}

bool ImageRequest::isTokenRequired() const
{
    return false;
}

void ImageRequest::parse()
{
    if (m_elapsedTimer.isValid()) {
        qDebug() << "Request (" << objectName()
                 << ") finished. Elapsed time:"
                 << m_elapsedTimer.elapsed();
    }

    emit requestFinished(m_replyDocument);
}

void ImageRequest::readReplyData(const QString &requestName, const QString &status)
{
    QFile file(m_cachePath + "/" + QFileInfo(m_url.path()).fileName());
    if (file.open(QFile::WriteOnly) == false) {
        qDebug() << "Could not open file for writing" << file.fileName()
                 << requestName << status;
        return;
    }

    qDebug() << "Writing file" << file.fileName();
    file.write(m_replyData);
}
