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

#include "weather.h"

/*!
 * \addtogroup Example
 * @{
 */

/*!
 * \class Weather
 * \brief Representation of weather
 */

Weather::Weather(QObject *parent):
    QObject(parent)
{
}

QString Weather::cityName() const
{
    return mCityName;
}

int Weather::humidity() const
{
    return mHumidity;
}

int Weather::pressure() const
{
    return mPressure;
}

float Weather::temp() const
{
    return mTemp;
}

QString Weather::getDataAsString()
{
    return QString("\nCity: %1 \nHumidity: %2 \nPressure: %3 \nTemperature: %4")
            .arg(cityName()).arg(humidity()).arg(pressure()).arg(temp());
}

void Weather::setCityName(const QString &cityName)
{
    if (mCityName == cityName)
        return;

    mCityName = cityName;
    emit cityNameChanged(cityName);
}

void Weather::setHumidity(int humidity)
{
    if (mHumidity == humidity)
        return;

    mHumidity = humidity;
    emit humidityChanged(humidity);
}

void Weather::setPressure(int pressure)
{
    if (mPressure == pressure)
        return;

    mPressure = pressure;
    emit pressureChanged(pressure);
}

void Weather::setTemp(float temp)
{
    if (mTemp == temp)
        return;

    mTemp = temp;
    emit tempChanged(temp);
}

/*! @} */
