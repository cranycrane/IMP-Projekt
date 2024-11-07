#include "WeatherScreen.h"
#include "WeatherData.h"
#include "Icons.h"

WeatherScreen::WeatherScreen(Adafruit_SSD1306& disp) : display(disp) {}

void WeatherScreen::render() {
    display.clearDisplay();
    display.setCursor(0, 46);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.print("Pocasi: ");
    display.println(currentData.getCondition());
    display.print("Teplota: ");
    display.print(currentData.getTemperature());
    display.println(" C");

    drawIcon(currentData.getIcon());
    display.display();
}

void WeatherScreen::updateData(ScreenData* data) {
    if (data->getType() == ScreenData::WEATHER) {  
        WeatherData* weatherData = static_cast<WeatherData*>(data);
        currentData = *weatherData;
    }
}

void WeatherScreen::drawIcon(const String& icon) {
    Serial.println("Vykresluju ikonu: " + icon);

    // Podmínky pro vykreslení ikony na základě kódu ikony
    if (icon == "01d" || icon == "01n") {
        display.drawBitmap(48, 0, icon_sunny, 32, 32, SSD1306_WHITE);
    } else if (icon == "02d" || icon == "02n" || icon == "03d" || icon == "03n") {
        display.drawBitmap(48, 0, epd_bitmap_cloudy, 32, 32, SSD1306_WHITE);
    } else if (icon == "10d" || icon == "10n") {
        display.drawBitmap(48, 0, epd_bitmap_heavy_rain, 32, 32, SSD1306_WHITE);
    } else if (icon == "50d" || icon == "50n") {
        display.drawBitmap(48, 0, epd_bitmap_fog, 32, 32, SSD1306_WHITE);
    }
    // Přidejte další podmínky pro další ikony
}
