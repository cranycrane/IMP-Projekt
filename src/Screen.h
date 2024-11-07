#ifndef SCREEN_H
#define SCREEN_H

#include "ScreenData.h"

class Screen {
  public:
    virtual void render() = 0;    
    virtual void updateData(ScreenData* data) = 0;
    virtual ~Screen() {} 
};

#endif
