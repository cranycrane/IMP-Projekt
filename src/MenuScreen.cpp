#include "MenuScreen.h"

MenuScreen::MenuScreen(Adafruit_SSD1306& disp) : display(disp), menuIndex(0) {}

void MenuScreen::render() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    if (menuState == MAIN_MENU) {
        display.println("Hlavní Menu:");
        display.println(mainMenu[menuIndex]);
    } else if (menuState == INFO_MENU) {
        display.println("Info Menu:");
        display.println(infoMenu[menuIndex]);
    } else if (menuState == ACTION_MENU) {
        display.println("Spousteni akce...");
        display.println("Obnovit data...");
        // Tady může být kód pro akci, například obnovení dat
    } else if (menuState == SETTINGS_MENU) {
        display.println("Nastavení teploty:");
        display.println("Nastavená hodnota...");
        // Tady může být logika pro nastavování hodnot
    }
    
    display.display();
}

void MenuScreen::nextMenuItem() {
    if (menuState == MAIN_MENU) {
        menuIndex = (menuIndex + 1) % menuItemsCount;
    } else if (menuState == INFO_MENU) {
        menuIndex = (menuIndex + 1) % 2; // Dvě položky v INFO_MENU
    }
}

void MenuScreen::previousMenuItem() {
    if (menuState == MAIN_MENU) {
        menuIndex = (menuIndex - 1 + menuItemsCount) % menuItemsCount;
    } else if (menuState == INFO_MENU) {
        menuIndex = (menuIndex - 1 + 2) % 2;
    }
}

void MenuScreen::selectItem() {
    if (menuState == MAIN_MENU) {
        switch (menuIndex) {
            case 0: // Informace
                menuState = INFO_MENU;
                menuIndex = 0;
                break;
            case 1: // Akce
                menuState = ACTION_MENU;
                // Tady můžete spustit akci, například volání funkce na obnovu dat
                break;
            case 2: // Nastavení
                menuState = SETTINGS_MENU;
                // Tady můžete nastavit teplotu nebo jinou hodnotu
                break;
        }
    } else if (menuState == INFO_MENU) {
        // Zde lze zobrazit informace, například počasí nebo datum
    }
}

void MenuScreen::backToMainMenu() {
    menuState = MAIN_MENU;
    menuIndex = 0;
}

void MenuScreen::updateData(ScreenData* data) {
    return;
}