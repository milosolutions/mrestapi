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

#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

class Weather : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString cityName READ cityName WRITE setCityName NOTIFY cityNameChanged)
    Q_PROPERTY(int humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
    Q_PROPERTY(int pressure READ pressure WRITE setPressure NOTIFY pressureChanged)
    Q_PROPERTY(float temp READ temp WRITE setTemp NOTIFY tempChanged)

public:
    Weather(QObject *parent = nullptr);

    QString cityName() const;
    int humidity() const;
    int pressure() const;
    float temp() const;

    QString getDataAsString();

public slots:
    void setCityName(const QString &cityName);
    void setHumidity(int humidity);
    void setPressure(int pressure);
    void setTemp(float temp);

signals:
    void cityNameChanged(const QString &cityName) const;
    void humidityChanged(int humidity) const;
    void pressureChanged(int pressure) const;
    void tempChanged(float temp) const;

private:
    QString mCityName;
    int mHumidity {0};
    int mPressure {0};
    float mTemp {0};
};

#endif // WEATHER_H
