#ifndef SCREEN_H
#define SCREEN_H

#include "ScreenData.h"

class Screen {
  public:
    virtual void render() = 0;
    void updateData(ScreenData* data);
    
    // Přidání základních funkcí posunu
    void scrollUp();
    void scrollDown();
    
    // Virtuální destruktor
    virtual ~Screen() {}

  protected:
    int scrollOffset = 0;  // Uchovává aktuální posun na obrazovce
    const int lineHeight = 8;  // Výška jednoho řádku, použijte podle potřeby
    int maxScrollOffset = 0; 
};

#endif
