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

#include "restapiclient.h"

#include <QSharedPointer>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(mrbrequest, "request")

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class RestAPIClient
 * \brief Network Manager for communication with any REST API
 */

RestAPIClient::RestAPIClient(QObject *parent)
    : RestRequestManager(parent)
{
}

/*! @} */
