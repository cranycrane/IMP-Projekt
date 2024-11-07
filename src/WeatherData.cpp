#include "WeatherData.h"

WeatherData::WeatherData() : temperature(0), condition("Unknown"), icon("01d") {}

void WeatherData::updateWeather(float temp, const String& cond, const String& iconCode) {
    temperature = temp;
    condition = cond;
    icon = iconCode;
}

float WeatherData::getTemperature() const {
    return temperature;
}

String WeatherData::getCondition() const {
    return condition;
}

String WeatherData::getIcon() const {
    return icon;
}
