#include "Screen.h"

void Screen::scrollUp() {
    if (scrollOffset > 0) {
        scrollOffset--;  // Posun nahoru, pokud je možné
    }
}

void Screen::scrollDown() {
    if (scrollOffset < maxScrollOffset) {
        scrollOffset++;  // Posun dolů, pokud je možné
    }
}

void Screen::updateData(ScreenData* data) {
    return;
}