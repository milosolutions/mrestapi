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

#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonDocument>
#include <QNetworkReply>

class QTimer;
class QNetworkReply;
class QNetworkAccessManager;

class MRestRequest : public QObject
{
    Q_OBJECT
public:
    enum class Type {None, Put, Post, Get, Delete};
    Q_ENUM(Type)

    explicit MRestRequest(const QUrl& url = QUrl());
    virtual ~MRestRequest();
    void setAddress(const QUrl& url);
    void setRequestTimeout(quint32 msec = 5000);
    bool isHigherPriority(const MRestRequest& request);
    void sendWith(QNetworkAccessManager* manager);
    QUrl address() const;
    QString lastError() const;
    QJsonDocument document() const;
    QByteArray rawData() const;

signals:
    void finished() const;
    void replyError(const QString &msgs) const;

public slots:

protected:
    enum class Priority {Bottom, Low, Normal, High, Top};
    void setPriority(Priority priority);

    void send();
    virtual void retry();
    virtual void parse() = 0;

    Priority mPriority = Priority::Normal;
    Type mType = Type::Get;
    QUrl mUrl;
    QNetworkReply *mActiveReply;
    int mRequestRetryCounter;
    int mRequestTimeout;
    int mMaxRequestRetryCount = 3;
    QByteArray mReplyData;
    QJsonDocument mReplyDocument;
    QJsonDocument mRequestDocument;

private slots:
    void onReplyError(QNetworkReply::NetworkError code);
    void onReadyRead();
    void onReplyFinished();
private:
    QString mLastError;
    QTimer *mRequestTimer;
    QNetworkAccessManager *mNetworkManager = nullptr;
};
