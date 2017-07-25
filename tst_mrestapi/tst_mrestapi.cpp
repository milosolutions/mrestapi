/*******************************************************************************
Copyright (C) 2016 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#include <QtTest>
#include <QCoreApplication>

#include "restapiclient.h"
#include "weatherbycitynamerequest.h"

class TestMRestAPI : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testRequest();
    void testBadRequest();

private:
    RestAPIClient client;
};

void TestMRestAPI::initTestCase()
{
    QCoreApplication::setApplicationName("MRestAPI Test");
    QCoreApplication::setOrganizationName("Milo");
}

void TestMRestAPI::cleanupTestCase()
{

}

void TestMRestAPI::testRequest()
{
    bool successEncountered = false;

    auto errorLambda = [](const QString &) {
        QFAIL("Test should not get error reply! Check internet connectivity.");
    };

    auto onWeatherInfoLambda = [&successEncountered](const QString &, int, int, int) {
        successEncountered = true;
    };

    auto lublinWeatherRequest = QSharedPointer<WeatherByCityNameRequest>::create("Lublin");
    QObject::connect(lublinWeatherRequest.data(), &WeatherByCityNameRequest::replyError, errorLambda);
    QObject::connect(lublinWeatherRequest.data(), &WeatherByCityNameRequest::weatherInfo, onWeatherInfoLambda);
    // send request
    client.send(lublinWeatherRequest);

    while(successEncountered == false)
        QTest::qWait(250);

    QVERIFY(successEncountered == true);
}

void TestMRestAPI::testBadRequest()
{
    bool errorEncountered = false;

    auto errorLambda = [&errorEncountered](const QString &str) {
        if (str.contains("Bad Request"))
            errorEncountered = true;
        else
            QFAIL("Test encountered error other than Bad Request! Check internet connectivity.");
    };

    auto badCityNameWeatheRequest = QSharedPointer<WeatherByCityNameRequest>::create("");
    QObject::connect(badCityNameWeatheRequest.data(), &WeatherByCityNameRequest::replyError, errorLambda);
    // send request
    client.send(badCityNameWeatheRequest);

    while(errorEncountered == false)
        QTest::qWait(250);

    QVERIFY(errorEncountered == true);
}

QTEST_MAIN(TestMRestAPI)

#include "tst_mrestapi.moc"
