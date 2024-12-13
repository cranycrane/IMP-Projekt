#include "MenuScreen.h"

MenuScreen::MenuScreen(Adafruit_SSD1306& disp) 
    : display(disp), menuState(MAIN_MENU), selectedSettingValue(0) {}

void MenuScreen::render() {
display.clearDisplay();
switch (menuState) {
    case MAIN_MENU:
        showMainMenu();
        break;
    case WEATHER_INFO:
        weatherScreen->render();
        break;
    case DATE_INFO:
        dateScreen->render();
        break;
    case SETTINGS:
        settingsScreen->render();
        break;
}
display.display();
}

void MenuScreen::handleGesture(uint8_t gesture) {
    if(menuState == SETTINGS) {
        settingsScreen->handleGesture(gesture);
    }

    switch (gesture) {
        case APDS9960_UP:
            if (menuState == MAIN_MENU) {
                if (selectedMenuIndex == 0) {
                    selectedMenuIndex = 2; 
                } else {
                    selectedMenuIndex--; 
                }
            } else if (menuState == SETTINGS) {
                selectedSettingValue += 1;
            } else if (menuState == WEATHER_INFO) {
                // todo get back Up after new sensor
                weatherScreen->scrollDown();
            }
            break;

        case APDS9960_DOWN:
            if (menuState == MAIN_MENU) {
                if (selectedMenuIndex == 2) {
                    selectedMenuIndex = 0;
                } else {
                    selectedMenuIndex++;  
                }
            } else if (menuState == SETTINGS) {
                selectedSettingValue -= 1;  
            } else if (menuState == WEATHER_INFO) {
                weatherScreen->scrollDown();
            }
            break;

        case APDS9960_LEFT: 
            if (settingsScreen->settingsState == SettingsScreen::ADJUST_INTERVAL) {
                settingsScreen->settingsState = SettingsScreen::VIEW_SETTINGS;
            } else {
                menuState = MAIN_MENU;
            }
            break;

        case APDS9960_RIGHT:
            if (menuState == MAIN_MENU) {
                switch (selectedMenuIndex) {
                    case 0:
                        menuState = WEATHER_INFO;
                        break;
                    case 1:
                        menuState = DATE_INFO;
                        break;
                    case 2:
                        menuState = SETTINGS;
                        break;
                }
            }
            break;

        default:
            break;
    }

    render(); 
}

void MenuScreen::showMainMenu() {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Menu:");

    display.setCursor(0, 10);
    display.print(selectedMenuIndex == 0 ? "> " : "  ");
    display.println("1. Pocasi");

    display.setCursor(0, 20);
    display.print(selectedMenuIndex == 1 ? "> " : "  ");
    display.println("2. Datum");

    display.setCursor(0, 30);
    display.print(selectedMenuIndex == 2 ? "> " : "  ");
    display.println("3. Nastaveni");

    display.display();
}

void MenuScreen::showSettingsMenu() {
    display.setCursor(0, 0);
    display.println("Nastaveni:");
    display.print("Prahová hodnota: ");
    display.println(selectedSettingValue);
}