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

#include "openweathermaprequest.h"
#include "openweathermaprequestconfig.h"

#include <QDebug>

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class OpenWeatherMapRequest
 * \brief Convenience class - contains preset Web API URL.
 *
 * When subclassing, see the tips and warnings from Request class documentation.
 */

/*!
 * Adds \a method to the URL of Web API server.
 */

OpenWeatherMapRequest::OpenWeatherMapRequest(const QString &method)
    : RestRequest(method)
{
    setMethod(method);
    setPriority(Priority::Normal);
}

/*!
 * Sets the method path to \a apiMethodPath. This means that \a apiMethodPath
 * string will be appended to OpenWeatherMap base API URL.
 *
 * Example:
 * \code
 * request.setMethod("weather?q=Lublin&units=metric");
 * // request URL is now: http://api.openweathermap.org/data/2.5/weather?q=Lublin
 * &units=metric&APPID=dd67c51ac1e36ec8fa90ecab89f3e850
 * \endcode
 */
void OpenWeatherMapRequest::setMethod(const QString &apiMethodPath)
{
    mApiMethod = apiMethodPath;
    OpenWeatherMapRequestConfig base;
    setAddress(QUrl(base.baseUrl + mApiMethod + "&APPID=" + base.mAppID));
}

/*! @} */
