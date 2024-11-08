// WeatherData.h
#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <Arduino.h>
#include "ScreenData.h"

class WeatherData : public ScreenData {
  public:
    WeatherData();
    DataType getType() const override { return WEATHER; }
    bool hasData = false;

    float temperature;
    String condition;
    String icon;
    float humidity;
    float windSpeed;
    String sunrise;  
    String sunset; 

    void update(float temp, const String& cond, const String& iconCode, float hum, float wind, const String& sunRiseTime, const String& sunSetTime);
};

#endif
