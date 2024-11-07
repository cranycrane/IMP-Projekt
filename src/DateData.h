#ifndef DATEDATA_H
#define DATEDATA_H

#include <Arduino.h>
#include "ScreenData.h"

class DateData : public ScreenData {
  public:
    DateData();
    void updateDate(const String& holidayName, const String& date);

    String getHolidayName() const;
    String getDate() const;    

    DataType getType() const override { return DATE; }

  private:
    String holidayNameStr;
    String dateStr;
};

#endif
