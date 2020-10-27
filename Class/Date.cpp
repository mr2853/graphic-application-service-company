#include "Date.hpp"
#include "../Util.hpp"
#include <string>
using namespace std;

Date::Date(){};
Date::~Date(){};
Date::Date(string in)
{
    vector<string> delovi = tokenization(in, ":", ",", "");
    /*cout << "\n\nDelovi elem: " << delovi.at(0) << "\n" << endl;
    cout << "Delovi elem: " << delovi.at(1) << "\n" << endl;
    cout << "Delovi elem: " << delovi.at(2) << "\n" << endl;
    cout << "Delovi elem: " << delovi.at(3) << "\n" << endl;*/
    if(delovi.size() == 5){
        //cout << "\nHour: " << stod(delovi.at(0)) << "\n" << endl;
        this->hour = stod(delovi.at(0));
        this->minute = stod(delovi.at(1));
        this->day = stod(delovi.at(2));
        this->month = stoi(delovi.at(3)); 
        this->year = stoi(delovi.at(4));
    }
    else if(delovi.size() == 3){
        //cout << "\nDay: " << stod(delovi.at(0)) << "\n" << endl;
        this->day = stod(delovi.at(0));
        this->month = stoi(delovi.at(1)); 
        this->year = stoi(delovi.at(2));
        this->hour = 0;
        //cout << "\nHour: " << hour << "\n" << endl;
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
vector<Date*> Date::readArray(string in)
{
    vector<Date*> array = vector<Date*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("]$Date") != std::string::npos){
            index = in.find("]$Date");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else if(in.find("Date[") != std::string::npos){
            index = in.find_last_of(">");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        //cout << "\n\n" << s << "\n\n" << endl;
        index = s.find("[");
        type1 = s.substr(0, index);
        Date *d = new Date(s);
        array.push_back(d);
    }
    return array;
};