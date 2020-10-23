#ifndef DATE_HPP
#define DATE_HPP
#include <iostream>
#include <string>

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
    Date(int day, int month, int year, int hour = 0, int minute = 0);
    ~Date();

	int getHour() {
		return hour;
	}

	void setHour(int hour) {
		this->hour = hour;
	}
    int getMinute() {
		return minute;
	}

	void setMinute(int minute) {
		this->minute = minute;
	}

	int getDay() {
		return day;
	}

	void setDay(int day) {
		this->day = day;
	}

	int getMonth() {
		return month;
	}

	void setMonth(int month) {
		this->month = month;
	}

	int getYear() {
		return year;
	}

	void setYear(int year) {
		this->year = year;
	}

    string getDate();
    string getDateWithTime();
};


#endif