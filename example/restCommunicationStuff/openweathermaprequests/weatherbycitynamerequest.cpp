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

#include "weatherbycitynamerequest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(requestWeahterCityByName, "request.weahterCityByName")

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class WeatherByCityNameRequest
 * \brief Request retrieves information about the weather in indicated city.
 */

/*!
 * Setup the request using  \a cityName.
 *
 * Use WeatherByCityNameRequest::send() to send it to the server.
 */

WeatherByCityNameRequest::WeatherByCityNameRequest(const QString &cityName)
    : OpenWeatherMapRequest("weather?q=" + cityName + "&units=metric")
{
    mPriority = Priority::High;
    mType = Type::Get;
}

/*!
 * All data is returned on success, by emitting weatherInfo() signal.
 */
void WeatherByCityNameRequest::parse()
{
    const QJsonObject object(mReplyDocument.object());

    /*
     * {"cod":"404","message":"Error: Not found city"}
     */

    const QString cod{"cod"};
    const QString  errorCode{"404"};

    if (object.contains(cod) && object.value(cod).toString() == errorCode) {
        const QString errorMsgKey("message");
        const QString errorMessage(object.value(errorMsgKey).toString());

        qCDebug(requestWeahterCityByName) << "Server returned errors:"
                                << errorMessage;
        emit replyError(errorMessage);
        return;
    }

    /*
     * {"base":"cmc stations","clouds":{"all":76},"cod":200,"coord":{"lat":51.25,"lon":22.57},
     * "dt":1467117635,"id":765876,"main":{"humidity":51,"pressure":1010,"temp":297.04000000000002,
     * "temp_max":297.04000000000002,"temp_min":297.04000000000002},"name":"Lublin","rain":{},
     * "sys":{"country":"PL","id":51499,"message":0.0025000000000000001,"sunrise":1467080211,
     * "sunset":1467139754,"type":3},"weather":[{"description":"broken clouds","icon":"04d",
     * "id":803,"main":"Clouds"}],"wind":{"deg":5.0039699999999998,"speed":4.8600000000000003}}
     */

    // let's take the data that we are interested
    const QJsonObject main = object.value("main").toObject();

    const QString cityName = object.value("name").toString();
    int humidity = main.value("humidity").toInt();
    int pressure = main.value("pressure").toInt();
    float temp = main.value("temp").toDouble();

    emit weatherInfo(cityName, humidity, pressure, temp);
}

/*! @} */
