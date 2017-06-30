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

#ifndef OPENWEATHERMAPREQUESTCONFIG_H
#define OPENWEATHERMAPREQUESTCONFIG_H

#include "restrequestconfig.h"

class OpenWeatherMapRequestConfig : public RestRequestConfig
{
public:
    OpenWeatherMapRequestConfig();
    QString mAppID;
};

#endif // OPENWEATHERMAPREQUESTCONFIG_H
