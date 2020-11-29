#include "Date.hpp"
#include "../Util.hpp"
#include <string>
using namespace std;

Date::Date(){};
Date::~Date()
{
	this->setDeleted();
};
Date::Date(string in, int changed)
{
    vector<string> delovi = tokenization(in, ":", ",", "", changed);
    if(delovi.size() == 5){
        this->hour = stod(delovi.at(0));
        this->minute = stod(delovi.at(1));
        this->day = stod(delovi.at(2));
        this->month = stoi(delovi.at(3));
        int i = 0;
        int last = 0;
        while (i < delovi.at(4).size())
        {
            if(isdigit(delovi.at(4)[i]))
            {
                last = i;      
            }
            i++;
        }
        delovi.at(4) = delovi.at(4).substr(0, last+1);
        this->year = stoi(delovi.at(4));
    }
    else if(delovi.size() == 3){
        this->day = stod(delovi.at(0));
        this->month = stoi(delovi.at(1));
        int i = 0;
        int last = 0;
        while (i < delovi.at(2).size())
        {
            if(isdigit(delovi.at(2)[i]))
            {
                last = i;      
            }
            i++;
        }
        delovi.at(2) = delovi.at(2).substr(0, last+1);
        this->year = stoi(delovi.at(2));
        this->hour = 0;
        this->minute = 0;
    }
    else if(delovi.size() == 6){
        this->hour = stod(delovi.at(1));
        this->minute = stod(delovi.at(2));
        this->day = stod(delovi.at(3));
        this->month = stoi(delovi.at(4));
        int i = 0;
        int last = 0;
        while (i < delovi.at(5).size())
        {
            if(isdigit(delovi.at(5)[i]))
            {
                last = i;      
            }
            i++;
        }
        delovi.at(5) = delovi.at(5).substr(0, last+1);
        this->year = stoi(delovi.at(5));
        this->setDeleted();
    }
}
void Date::setDeleted() {
	deleted = true;
}

bool Date::isEqual(Date* date)
{
    if(this->hour == date->hour && this->minute == date->minute 
    && this->day == date->day && this->month == date->month 
    && this->year == date->year && this->deleted == date->deleted)
    {
        return true;
    }
    return false;
}
bool Date::isDeleted() {
	return deleted;
}
Date::Date(int hour, int minute, int day, int month, int year)
    : hour(hour), minute(minute), day(day), month(month), year(year){}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year), minute(0), hour(0){}

int Date::getHour() const {
    return hour;
}
void Date::setHour(int hour) {
    this->hour = hour;
}
int Date::getMinute() const {
    return minute;
}
void Date::setMinute(int minute) {
    this->minute = minute;
}
int Date::getDay() const {
    return day;
}
void Date::setDay(int day) {
    this->day = day;
}
int Date::getMonth() const {
    return month;
}
void Date::setMonth(int month) {
    this->month = month;
}
int Date::getYear() const {
    return year;
}
void Date::setYear(int year) {
    this->year = year;
}
string Date::getDate() const
{
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
}
string Date::getDateWithTime() const
{
    return to_string(hour) + "-" + to_string(minute) + "-" + Date::getDate();
}
vector<Date*> Date::readArray(string in, int changed)
{
    vector<Date*> array = vector<Date*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("$Date[") != std::string::npos){
            index = in.find("$Date[");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 1);
        }
        else if(in.find("Date[") != std::string::npos){
            index = in.find_last_of("]");
            text.push_back(in.substr(0, index+1));
            in.erase(0, index + 1);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        if(changed == 1)
        {
            string someText = s;
            index = someText.find(":");
            someText.erase(0,index+1);
            index = someText.find(",");
            string type = someText.substr(0, index);
            if(type == "true")
            {
                continue;
            }
        }
        Date *d = new Date(s, changed);
        array.push_back(d);
    }
    return array;
};

void Date::write(ostream &output, Date *d)
{
    output << "Date[deleted:";
    if(d->deleted)
    {
        output << "true";
    }
    else
    {
        output << "false";
    }
    output << ",hour:" << d->hour;
    output << ",minute:" << d->minute << ",day:" << d->day << ",month:" << d->month << ",year:" << d->year << "]";
}