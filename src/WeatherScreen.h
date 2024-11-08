#ifndef WEATHERSCREEN_H
#define WEATHERSCREEN_H

#include <Adafruit_SSD1306.h>
#include "Screen.h"
#include "WeatherData.h"

class WeatherScreen : public Screen {
  public:
    WeatherScreen(Adafruit_SSD1306& display);
    void render() override;          
    void updateData(ScreenData* data);

  private:
    Adafruit_SSD1306& display;
    WeatherData* currentData;     

    void drawIcon(const String& icon, int y);
};

#endif
