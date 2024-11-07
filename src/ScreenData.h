#ifndef SCREENDATA_H
#define SCREENDATA_H

class ScreenData {
  public:
    enum DataType { WEATHER, DATE, OTHER };

    virtual ~ScreenData() {}
    virtual DataType getType() const = 0;
};

#endif
