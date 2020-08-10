#pragma once

#include "mrestrequest.h"

class ImageRequest : public MRestRequest
{
public:
    ImageRequest(const QUrl &url, const QString &cachePath);

protected:
    bool isTokenRequired() const override;
    void parse() override;
    void readReplyData(const QString &requestName, const QString &status) override;

private:
    QString m_cachePath;
};

