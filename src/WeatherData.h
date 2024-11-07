#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <Arduino.h>
#include "ScreenData.h"

class WeatherData : public ScreenData {
  public:
    WeatherData();
    void updateWeather(float temp, const String& condition, const String& icon);
    
    float getTemperature() const;
    String getCondition() const;
    String getIcon() const;

    DataType getType() const override { return WEATHER; }

  private:
    float temperature;
    String condition;
    String icon;
};

#endif
