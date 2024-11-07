#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <Adafruit_SSD1306.h>
#include "Screen.h"

class MenuScreen : public Screen {
  public:
    MenuScreen(Adafruit_SSD1306& display);
    void render() override;
    void updateData(ScreenData* data) override;
    void nextMenuItem(); // Přejde na další položku
    void previousMenuItem(); // Přejde na předchozí položku
    void selectItem(); // Potvrdí výběr položky a přepne do podmenu nebo spustí akci
    void backToMainMenu(); // Vrátí se zpět do hlavního menu

  private:
    enum MenuState { MAIN_MENU, INFO_MENU, ACTION_MENU, SETTINGS_MENU };
    MenuState menuState = MAIN_MENU; // Aktuální stav menu

    Adafruit_SSD1306& display;
    int menuIndex;
    const char* mainMenu[3] = {"Informace", "Akce", "Nastavení"};
    const char* infoMenu[2] = {"Počasí", "Datum"};
    int menuItemsCount = 3;
};

#endif
