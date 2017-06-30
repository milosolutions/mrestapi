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

#include "mrbaburequest.h"
#include "mrbaburequestconfig.h"

#include <QDebug>

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class MrBabuRequest
 * \brief Convenience class - contains preset Web API URL.
 *
 * When subclassing, see the tips and warnings from Request class documentation.
 */

/*!
 * Adds \a method to the URL of Web API server.
 */
MrBabuRequest::MrBabuRequest(const QString &method)
    : RestRequest()
{
    setMethod(method);
    setPriority(Priority::Normal);
}

/*!
 * Sets the method path to \a apiMethodPath. This means that \a apiMethodPath
 * string will be appended to MrBabu base API URL.
 *
 * Example:
 * \code
 * request.setMethod("basket");
 * // request URL is now: http://ec2-52-33-133-227.us-west-2.compute.amazonaws.com/api/basket
 * \endcode
 */
void MrBabuRequest::setMethod(const QString &apiMethodPath)
{
    mApiMethod = apiMethodPath;
    MrBabuRequestConfig base;
    setAddress(QUrl(base.baseUrl + mApiMethod + "/?format=json"));
}

/*! @} */
