#ifndef SCREEN_H
#define SCREEN_H

#include "ScreenData.h"

class Screen {
  public:
    virtual void render() = 0;
    void updateData(ScreenData* data);
    
    void scrollUp();
    void scrollDown();
  

  protected:
    int scrollOffset = 0;  
    const int lineHeight = 8;
    int maxScrollOffset = 0; 
};

#endif
