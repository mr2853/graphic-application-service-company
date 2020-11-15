#ifndef DATE_HPP
#define DATE_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date
{
private:
    int hour;
    int minute;
    int day;
    int month;
    int year;

public:
    Date();
    Date(string in);
    Date(int day, int month, int year);
    Date(int hour, int minute, int day, int month, int year);
    ~Date();

	int getHour();
	void setHour(int hour);
	int getMinute();
	void setMinute(int minute);
	int getDay();
	void setDay(int day);
	int getMonth();
	void setMonth(int month);
	int getYear();
	void setYear(int year);

    string getDate();
    string getDateWithTime();
    static vector<Date *> readArray(string in);
    //static vector<Date*> readData(string in);
};


#endif