#include "WelcomeScreen.h"

WelcomeScreen::WelcomeScreen(Adafruit_SSD1306& disp) : display(disp) {}

void WelcomeScreen::render() {
    display.clearDisplay();
    display.display();
    display.drawBitmap(
    (32),
    (0),
    epd_bitmap_vut, 64, 64, SSD1306_WHITE
    );
    display.display();
}


void WelcomeScreen::updateData(ScreenData* data) {
    return;
}