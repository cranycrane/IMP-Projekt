#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <Adafruit_APDS9960.h>
#include <Adafruit_SSD1306.h>
#include "Screen.h"
#include "DateScreen.h"
#include "WeatherScreen.h"
#include "SettingsScreen.h"

class MenuScreen : public Screen {
  public:
    MenuScreen(Adafruit_SSD1306& display);

    DateScreen* dateScreen;
    WeatherScreen* weatherScreen;
    SettingsScreen* settingsScreen;

    void render() override;
    void handleGesture(uint8_t gesture);

  private:
    enum MenuState {
        MAIN_MENU,
        WEATHER_INFO,
        DATE_INFO,
        SETTINGS
    };

    Adafruit_SSD1306& display;

    MenuState menuState;
    int selectedSettingValue;
    int selectedMenuIndex = 0;

    void showSettingsMenu();
    void showMainMenu();
};

#endif
