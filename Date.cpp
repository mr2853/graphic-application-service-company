#include "Date.hpp"

Date::Date(){};
Date::~Date(){};
Date::Date(int day, int month, int year, int hour, int minute)
    : hour(hour), minute(minute), day(day), month(month), year(year){}

string Date::getDate()
{
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
}

string Date::getDateWithTime()
{
    return to_string(hour) + "-" + to_string(minute) + "-" + Date::getDate();
}