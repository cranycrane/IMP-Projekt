#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_APDS9960.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Screen.h"
#include "WeatherSettings.h"

class SettingsScreen : public Screen {
  public:
    SettingsScreen(Adafruit_SSD1306& display);
    PubSubClient client;

    void render() override;                
    void handleGesture(uint8_t gesture);   
    WeatherSettings getSettings() const;   
    void sendSettings();

    enum SettingsState { VIEW_SETTINGS, ADJUST_INTERVAL };
    SettingsState settingsState = VIEW_SETTINGS;
  private:

    Adafruit_SSD1306& display;
    WeatherSettings weatherSettings;
    int selectedOption = 0;                
    const int optionCount = 6;  
    int updateInterval = 5;           
};

#endif
