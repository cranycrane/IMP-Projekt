#include "WeatherScreen.h"
#include "WeatherData.h"
#include "Icons.h"

WeatherScreen::WeatherScreen(Adafruit_SSD1306& disp) : display(disp) {
    maxScrollOffset = 2;
}

void WeatherScreen::render() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    int y = 32 - (scrollOffset * lineHeight);  
    const int iconHeight = 32;

    if (currentData->icon != "" && y <= iconHeight) {
        drawIcon(currentData->icon, y - 32); 
    }

    if (!isnan(currentData->temperature)) {
        display.setCursor(0, y);
        display.print("Teplota: ");
        display.print(currentData->temperature);
        display.println(" C");
        y += lineHeight;
    }

    if (currentData->condition != "") {
        display.setCursor(0, y);
        display.print("Stav: ");
        display.println(currentData->condition);
        y += lineHeight;
    }

    if (!isnan(currentData->humidity)) {
        display.setCursor(0, y);
        display.print("Vlhkost: ");
        display.print(currentData->humidity);
        display.println("%");
        y += lineHeight;
    }

    if (!isnan(currentData->windSpeed)) {
        display.setCursor(0, y);
        display.print("Vitr: ");
        display.print(currentData->windSpeed);
        display.println(" m/s");
        y += lineHeight;
    }

    if (currentData->sunrise != "") {
        display.setCursor(0, y);
        display.print("Vychod slunce: ");
        display.println(currentData->sunrise);
        y += lineHeight;
    }

    if (currentData->sunset != "") {
        display.setCursor(0, y);
        display.print("Zapad slunce: ");
        display.println(currentData->sunset);
        y += lineHeight;
    }

    display.display();
}


void WeatherScreen::updateData(ScreenData* data) {
    if (data->getType() == ScreenData::WEATHER) {  
        WeatherData* weatherData = static_cast<WeatherData*>(data);
        currentData = weatherData;
    }
}

void WeatherScreen::drawIcon(const String& icon, int y) {
    Serial.println("Vykresluju ikonu: " + icon);
    if (icon == "sun") {
        display.drawBitmap(48, y, icon_sunny, 32, 32, SSD1306_WHITE);
    } else if (icon == "cloud") {
        display.drawBitmap(48, y, epd_bitmap_cloudy, 32, 32, SSD1306_WHITE);
    } else if (icon == "rain") {
        display.drawBitmap(48, y, epd_bitmap_heavy_rain, 32, 32, SSD1306_WHITE);
    } else if (icon == "fog") {
        display.drawBitmap(48, y, epd_bitmap_fog, 32, 32, SSD1306_WHITE);
    }
}
