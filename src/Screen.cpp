#include "Screen.h"

void Screen::scrollUp() {
    if (scrollOffset > 0) {
        scrollOffset--;
    }
}

void Screen::scrollDown() {
    if (scrollOffset < maxScrollOffset) {
        scrollOffset++;
    }
}

void Screen::updateData(ScreenData* data) {
    return;
}