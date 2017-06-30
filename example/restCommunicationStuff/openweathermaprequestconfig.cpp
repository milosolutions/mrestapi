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

#include "openweathermaprequestconfig.h"

/*!
 * \ingroup Network
 * \ingroup Config
 * \ingroup Example
 * @{
 */

/*!
 * \class OpenWeatherMapRequestConfig
 * \brief Common request configuration. Contains URL and key to Web API.
 */

OpenWeatherMapRequestConfig::OpenWeatherMapRequestConfig()
{
#ifdef USE_PRODUCTION_SERVER
    baseUrl = "TODO";
    mAppID = "TODO"
#else
    baseUrl = "http://api.openweathermap.org/data/2.5/";
    mAppID = "dd67c51ac1e36ec8fa90ecab89f3e850"; // genereted on https://home.openweathermap.org
#endif

    CONFIG_VALUE(baseUrl, QMetaType::QByteArray);
}

/*! @} */
