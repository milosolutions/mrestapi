#pragma once

#include "mrestrequest.h"

#include <QObject>
#include <QFileInfo>
#include <QMultiHash>

class MMultiPartRequest : public MRestRequest
{
    Q_OBJECT

public:
    explicit MMultiPartRequest(const QUrl &url);

    void addPart(const QString &key, const QString &value);
    void addPart(const QString &key, const QFileInfo &file);

protected:
    bool isMultiPart() const override;
    QHttpMultiPart* requestMultiPart() const override;

private:
    QMultiHash<QString, QString> m_stringParts;
    QMultiHash<QString, QFileInfo> m_fileParts;
};

