#include "DateScreen.h"
#include "DateData.h"
#include "Icons.h"

DateScreen::DateScreen(Adafruit_SSD1306& disp) : display(disp) {}

void DateScreen::render() {
    display.clearDisplay();
    display.setCursor(0, 32);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.print("Dnes ma svatek ");
    display.println(currentData.getHolidayName());
    display.print("Datum: ");
    display.print(currentData.getDate());

    display.display();
}

void DateScreen::updateData(ScreenData* data) {
    if (data->getType() == ScreenData::DATE) {  
        DateData* dateData = static_cast<DateData*>(data);
        currentData = *dateData;
    }
}