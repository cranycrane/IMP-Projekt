#ifndef DATESCREEN_H
#define DATESCREEN_H

#include <Adafruit_SSD1306.h>
#include "Screen.h"
#include "DateData.h"

class DateScreen : public Screen {
  public:
    DateScreen(Adafruit_SSD1306& display);
    void render() override;          
    void updateData(ScreenData* data) override;

  private:
    Adafruit_SSD1306& display;
    DateData currentData;     
};

#endif
