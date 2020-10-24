#include "Util.hpp"
#include "Auditor.hpp"
#include <string>

using namespace std;

Auditor::Auditor(){}
Auditor::~Auditor(){}
Auditor::Auditor(string text)
{
    string twoDots = ":";
    string comma = ",";
    string lessThan = "<";

    int index = text.find("dateBirth:");
    string in = text.substr(0, index);
    vector<string> t = tokenization(in, ":", ",");
    text.erase(0, index+10);
    
    index = text.find(twoDots);
    text.erase(0,index+2);// bilo + 5
    index = text.find("],");
    string t1 = text.substr(0, index);
    Date* dateBirth = new Date(t1);
    text.erase(0,index+2);

    index = text.find(twoDots);
    text.erase(0,index+1);
    index = text.find(comma);
    double salary = stod(text.substr(0, index));
    text.erase(0,index+1);
    
    index = text.find(lessThan);
    text.erase(0,index+1);
    vector<Date*> dates = vector<Date*>();
    dates = readArray<Date>(text);

    this->setName(t.at(0));
    this->setLastname(t.at(1));
    this->setSalary(salary);
    this->setDateBirth(dateBirth);
    this->setDatesVisiting(dates);

    /*while(text.find("Date["))
    {                          
        index = text.find(twoDots);
        text.erase(0,index+1);
        index = text.find(comma);
        deleted = text.substr(0, index);
        if(deleted == "true")
            return;
    }*/
}
Auditor::Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date*> datesVisiting)
    : AbstractWorker(name, lastname, dateBirth, salary), datesVisiting(datesVisiting){}

void Auditor::pushDateVisiting(Date *date)
{
    datesVisiting.push_back(date);
}
Date* Auditor::getDateVisiting(int indeks)
{
    return datesVisiting.at(indeks);
}
void Auditor::setDatesVisiting(vector<Date*> datesVisiting)
{
    this->datesVisiting = datesVisiting;
}