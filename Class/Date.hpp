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
    bool deleted = false;

public:
    Date();
    Date(string in, int changed);
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
    virtual bool isDeleted();
    virtual void setDeleted();
    bool isEqual(Date* date);

    string getDate();
    string getDateWithTime();
    static vector<Date *> readArray(string in, int changed);
    void write(ostream &output, Date *osobe);
};


#endif