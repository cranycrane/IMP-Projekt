#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(Adafruit_SSD1306& disp) : display(disp) {}

void SettingsScreen::render() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.println("Nastaveni pocasi:");
    
    // Zobrazení možností s indikátorem vybrané možnosti
    display.print("1. Teplota: ");
    display.println(weatherSettings.showTemperature ? "ANO" : "NE");
    display.print("2. Vlhkost: ");
    display.println(weatherSettings.showHumidity ? "ANO" : "NE");
    display.print("3. Vitr: ");
    display.println(weatherSettings.showWindSpeed ? "ANO" : "NE");
    display.print("4. Vychod slunce: ");
    display.println(weatherSettings.showSunrise ? "ANO" : "NE");
    display.print("5. Zapad slunce: ");
    display.println(weatherSettings.showSunset ? "ANO" : "NE");

    // Zvýraznění aktuálně vybrané možnosti
    display.setCursor(0, selectedOption * lineHeight + 10);  // Offset na základě výběru
    display.print("->");
    
    display.display();
}

void SettingsScreen::handleGesture(uint8_t gesture) {
    switch (gesture) {
        case APDS9960_UP:
            // Přechod na předchozí možnost
            selectedOption = (selectedOption - 1 + optionCount) % optionCount;
            break;
        case APDS9960_DOWN:
            // Přechod na další možnost
            selectedOption = (selectedOption + 1) % optionCount;
            break;
        case APDS9960_RIGHT:
            Serial.println("Davam right");
            // Přepnutí hodnoty vybrané možnosti
            switch (selectedOption) {
                case 0: weatherSettings.showTemperature = !weatherSettings.showTemperature; break;
                case 1: weatherSettings.showHumidity = !weatherSettings.showHumidity; break;
                case 2: weatherSettings.showWindSpeed = !weatherSettings.showWindSpeed; break;
                case 3: weatherSettings.showSunrise = !weatherSettings.showSunrise; break;
                case 4: weatherSettings.showSunset = !weatherSettings.showSunset; break;
            }
            break;
        case APDS9960_LEFT:
        Serial.println("Odesilam sett");
            sendSettings();
            break;
    }
    render();  // Aktualizace obrazovky po změně
}

void SettingsScreen::sendSettings() {
    if (client.connected()) {
        StaticJsonDocument<200> doc;
        doc["showTemperature"] = weatherSettings.showTemperature;
        doc["showHumidity"] = weatherSettings.showHumidity;
        doc["showWindSpeed"] = weatherSettings.showWindSpeed;
        doc["showSunrise"] = weatherSettings.showSunrise;
        doc["showSunset"] = weatherSettings.showSunset;

        char jsonBuffer[256];
        serializeJson(doc, jsonBuffer);

        client.publish("home/request/weather", jsonBuffer);
        Serial.println("MQTT zpráva odeslána: ");
        Serial.println(jsonBuffer);
    } else {
        Serial.println("MQTT není připojen, zpráva nebyla odeslána.");
    }
}

WeatherSettings SettingsScreen::getSettings() const {
    return weatherSettings;
}
