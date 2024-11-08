#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(Adafruit_SSD1306& disp) : display(disp) {}

void SettingsScreen::render() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.println("Nastaveni pocasi:");
    
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

    int intervalCursorX = (settingsState == ADJUST_INTERVAL && selectedOption == 5) ? 10 : 0;
    display.setCursor(intervalCursorX, 5 * lineHeight + 10); 

    display.print("6. Interval: ");
    display.print(updateInterval);
    display.println(" min");

    display.setCursor(0, selectedOption * lineHeight + 10);  
    display.print("->");

    display.display();
}


void SettingsScreen::handleGesture(uint8_t gesture) {
    if (settingsState == VIEW_SETTINGS) {
        switch (gesture) {
            case APDS9960_UP:
                selectedOption = (selectedOption - 1 + optionCount) % optionCount;
                break;
            case APDS9960_DOWN:
                selectedOption = (selectedOption + 1) % optionCount;
                break;
            case APDS9960_RIGHT:
                if (selectedOption == 5) { 
                    settingsState = ADJUST_INTERVAL;
                } else {
                    switch (selectedOption) {
                        case 0: weatherSettings.showTemperature = !weatherSettings.showTemperature; break;
                        case 1: weatherSettings.showHumidity = !weatherSettings.showHumidity; break;
                        case 2: weatherSettings.showWindSpeed = !weatherSettings.showWindSpeed; break;
                        case 3: weatherSettings.showSunrise = !weatherSettings.showSunrise; break;
                        case 4: weatherSettings.showSunset = !weatherSettings.showSunset; break;
                    }
                }
                break;
            case APDS9960_LEFT:
        Serial.println("Jdu taky main");
                sendSettings();
                break;
        }
    } else if (settingsState == ADJUST_INTERVAL) {
        if (gesture == APDS9960_UP && updateInterval < 60) {
            updateInterval += 5;
        } else if (gesture == APDS9960_DOWN && updateInterval > 5) {
            updateInterval -= 5;
        } else if (gesture == APDS9960_LEFT) { 
            sendSettings(); 
        }
    }
    render();
}

void SettingsScreen::sendSettings() {
    if (client.connected()) {
        StaticJsonDocument<200> doc;
        doc["showTemperature"] = weatherSettings.showTemperature;
        doc["showHumidity"] = weatherSettings.showHumidity;
        doc["showWindSpeed"] = weatherSettings.showWindSpeed;
        doc["showSunrise"] = weatherSettings.showSunrise;
        doc["showSunset"] = weatherSettings.showSunset;
        doc["updateInterval"] = updateInterval;

        char jsonBuffer[256];
        serializeJson(doc, jsonBuffer);

        client.publish("home/request/weather", jsonBuffer);
        Serial.println("Send MQTT message: ");
        Serial.println(jsonBuffer);
    } else {
        Serial.println("MQTT not connected.");
    }
}

WeatherSettings SettingsScreen::getSettings() const {
    return weatherSettings;
}
