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
#include <QVector>
#include <QStringList>

#include "mrestrequestqueue.h"
#include "mrestrequest.h"

class QNetworkAccessManager;

class MRestRequestManager : public QObject
{
    Q_OBJECT
public:
    MRestRequestManager(QObject *parent = nullptr);
    void send(RestRequestPtr request);
    void ignoreSslErrors();
signals:
    void sslErrorsChanged(const QStringList &errors);
protected:
    void onRequestFinished();
    void removeActiveRequest(QObject *sender);
    MRestRequestQueue pendingRequests;
    QVector<MRestRequestPtr> mActiveRequests;
    QStringList mLastSslErrors;
    bool mIgnoreSslErrors;
    QNetworkAccessManager *networkManager = nullptr;
    int MaxActiveRequestsCount = 3;
private slots:
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
};
