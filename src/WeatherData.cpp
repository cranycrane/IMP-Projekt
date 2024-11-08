#include "WeatherData.h"

WeatherData::WeatherData()
    : temperature(NAN), humidity(NAN), windSpeed(NAN), condition(""), icon(""),
      sunrise(""), sunset("") {}

void WeatherData::update(float temp, const String& cond, const String& iconCode, float hum, float wind, const String& sunRiseTime, const String& sunSetTime) {
    temperature = temp;
    condition = cond;
    icon = iconCode;
    humidity = hum;
    windSpeed = wind;
    sunrise = sunRiseTime;
    sunset = sunSetTime;
}
