#include "Date.hpp"
#include "Util.hpp"
#include <string>
using namespace std;

Date::Date(){};
Date::~Date(){};
Date::Date(string in)
{
    vector<string> delovi = tokenization(in, ":", ",");
    if(delovi.size() == 5){
        this->hour = stod(delovi.at(0));
        this->minute = stod(delovi.at(1));
        this->day = stod(delovi.at(2));
        this->month = stoi(delovi.at(3)); 
        this->year = stoi(delovi.at(4));
    }
    else if(delovi.size() == 3){
        this->day = stod(delovi.at(0));
        this->month = stoi(delovi.at(1)); 
        this->year = stoi(delovi.at(2));
        this->hour = 0;
        this->minute = 0;
    }
}
Date::Date(int day, int month, int year, int hour, int minute)
    : hour(hour), minute(minute), day(day), month(month), year(year){}

int Date::getHour() {
    return hour;
}
void Date::setHour(int hour) {
    this->hour = hour;
}
int Date::getMinute() {
    return minute;
}
void Date::setMinute(int minute) {
    this->minute = minute;
}
int Date::getDay() {
    return day;
}
void Date::setDay(int day) {
    this->day = day;
}
int Date::getMonth() {
    return month;
}
void Date::setMonth(int month) {
    this->month = month;
}
int Date::getYear() {
    return year;
}
void Date::setYear(int year) {
    this->year = year;
}
string Date::getDate()
{
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
}
string Date::getDateWithTime()
{
    return to_string(hour) + "-" + to_string(minute) + "-" + Date::getDate();
}

/*vector<Date*> Date::readData(string in)
{
    vector<Date*> dates;
    vector<string> text;
    while(in.find("Date["))
    {
        int index = in.find("],");
        text.push_back(in.substr(0, index));
        in.erase(0, index + 2);
    }
    for(string s : text)
    {
        dates.push_back(new Date(s));
    }
    return dates;
}*/