#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <Adafruit_SSD1306.h>
#include "Screen.h"
#include "vutLogo.cpp"

class WelcomeScreen : public Screen {
  public:
    WelcomeScreen(Adafruit_SSD1306& display);
    void updateData(ScreenData* data) override;
    void render() override;          

  private:
    Adafruit_SSD1306& display;

};

#endif
