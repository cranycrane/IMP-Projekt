#include "DateData.h"

DateData::DateData() : holidayNameStr("Neznámé"), dateStr("Neznámé") {}

void DateData::updateDate(const String& holidayName, const String& date) {
    holidayNameStr = holidayName;
    dateStr = date;
}

String DateData::getHolidayName() const {
    return holidayNameStr;
}
String DateData::getDate() const {
    return dateStr;
}    