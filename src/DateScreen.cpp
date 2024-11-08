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

    String formattedDate = convertDateFormat(currentData.getDate());  // Převod formátu
    display.print("Datum: ");
    display.println(formattedDate);

    display.display();
}


void DateScreen::updateData(ScreenData* data) {
    if (data->getType() == ScreenData::DATE) {  
        DateData* dateData = static_cast<DateData*>(data);
        currentData = *dateData;
    }
}

String DateScreen::convertDateFormat(const String& date) {
    if (date.length() != 10) {
        return "Wrong format";
    }

    String year = date.substring(0, 4);
    String month = date.substring(5, 7);
    String day = date.substring(8, 10);

    return day + "." + month + "." + year;
}
