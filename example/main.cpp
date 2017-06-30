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

#include <QCoreApplication>
#include <QLoggingCategory>

#include "mrBabu/session.h"
#include "restapiclient.h"

#include "openweathermaprequests/weatherbycitynamerequest.h"
#include "openWeatherMap/weather.h"

Q_LOGGING_CATEGORY(coreMain, "core.main")

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion(APP_VERSION);
    app.setOrganizationName("Milo Solutions");
    app.setOrganizationDomain("milosolutions.com");
    app.setApplicationName("REST API communication - demo.");

    qCInfo(coreMain) << "Application data set."
                 << "\n\tName:" << app.applicationName()
                 << "\n\tOrganisation:" << app.organizationName()
                 << "\n\tDomain:" << app.organizationDomain()
                 << "\n\tVersion:" << app.applicationVersion();

    // Crate rest api client.
    RestAPIClient client;


    // [1] ########  Simple example of usage, based on MrBabuQt project. ########.

    Session session;
    session.setClient(&client);

    // This is only example - we do not send any request here but we can see how use this classes.
    // session.registerUser(...);
    // session.login(...);
    // session.getUserInfo();

    // [1] ######################################################################



    // [2] ########  Simple example of usage, based on OpenWeatherMap API. ########.

    Weather weatherInLublin;

    auto errorLambda = [](const QString &error) {
        // do something with data
        qCInfo(coreMain) << "Print error msg: " << error;
    };

    auto onWeatherInfoLambda = [&weatherInLublin](const QString &cityName,
            int humidity, int pressure, int temp) {

        // do something with data
        weatherInLublin.setCityName(cityName);
        weatherInLublin.setHumidity(humidity);
        weatherInLublin.setPressure(pressure);
        weatherInLublin.setTemp(temp);

        qCInfo(coreMain) << "Weather: " + weatherInLublin.getDataAsString();
    };

    // prepare some request
    auto badCityNameWeatheRequest = QSharedPointer<WeatherByCityNameRequest>::create("");
    QObject::connect(badCityNameWeatheRequest.data(), &WeatherByCityNameRequest::replyError, errorLambda);
    QObject::connect(badCityNameWeatheRequest.data(), &WeatherByCityNameRequest::weatherInfo, onWeatherInfoLambda);

    auto lublinWeatherRequest = QSharedPointer<WeatherByCityNameRequest>::create("Lublin");
    QObject::connect(lublinWeatherRequest.data(), &WeatherByCityNameRequest::replyError, errorLambda);
    QObject::connect(lublinWeatherRequest.data(), &WeatherByCityNameRequest::weatherInfo, onWeatherInfoLambda);

    // send request
    client.send(badCityNameWeatheRequest);
    client.send(lublinWeatherRequest);

    // [2] ######################################################################

    return app.exec();
}
