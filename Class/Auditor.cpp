#include "../Util.hpp"
#include "Auditor.hpp"
#include <string>

using namespace std;

Auditor::Auditor(){}
Auditor::~Auditor()
{
    
};
void Auditor::setDeleted() {
    for(int i = 0; i < datesVisiting->size(); i++)
    {
        datesVisiting->at(i)->setDeleted();
    }
	AbstractWorker::setDeleted();
}
Auditor::Auditor(string text, int changed)
{
    string twoDots = ":";
    string comma = ",";
    string lessThan = "<";

    int index = text.find("dateBirth:");
    string in = text.substr(0, index);
    vector<string> t = tokenization(in, ":", ",", "", changed);
    text.erase(0, index+10);
    
    index = text.find("],");
    string t1 = text.substr(0, index);
    Date* dateBirth = new Date(t1, changed);
    text.erase(0,index+2);

    index = text.find(twoDots);
    text.erase(0,index+1);
    index = text.find(comma);
    double salary = stod(text.substr(0, index));
    text.erase(0,index+1);
    
    index = text.find(lessThan);
    text.erase(0,index+1);
    vector<Date*> *dates = new vector<Date*>();
    *dates = Date::readArray(text, changed);
    if(t.size() == 2){
        this->setName(t.at(0));
        this->setLastname(t.at(1));
    }
    else if(t.size() == 3)
    {
        this->setDeleted();
        this->setName(t.at(1));
        this->setLastname(t.at(2));
    }
    this->setSalary(salary);
    this->setDateBirth(dateBirth);
    this->setDatesVisiting(dates);
}
Auditor::Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date*> *datesVisiting)
    : AbstractWorker(name, lastname, dateBirth, salary), datesVisiting(datesVisiting){}

Auditor::Auditor(string name, string lastname, Date *dateBirth, double salary)
    : AbstractWorker(name, lastname, dateBirth, salary), datesVisiting(new vector<Date*>()){}


void Auditor::addDateVisiting(Date* date)
{
    datesVisiting->push_back(date);
}
void Auditor::removeDateVisiting(Date* date)
{
    for(int i = 0; i < datesVisiting->size(); i++)
    {
        if(datesVisiting->at(i)->isEqual(date))
        {
            datesVisiting->erase(datesVisiting->begin()+i);
            break;
        }
    }
}
bool Auditor::isAvailabe(Date* date)
{
    for(int i = 0; i < datesVisiting->size(); i++)
    {
        if(datesVisiting->at(i)->isEqual(date))
        {
            return false;
        }
    }
    return true;
}

void Auditor::pushDateVisiting(Date *date)
{
    datesVisiting->push_back(date);
}
Date* Auditor::getDateVisiting(int indeks)
{
    return datesVisiting->at(indeks);
}
void Auditor::setDatesVisiting(vector<Date*> *datesVisiting)
{
    this->datesVisiting = datesVisiting;
}
vector<Date*>* Auditor::getDatesVisiting(){
    return datesVisiting;
}
string Auditor::getType()
{
	return type;
}

void Auditor::write(ostream &output, void *data)
{
    Auditor *d = (Auditor*)data;
    output << "Auditor";
    AbstractWorker::write(output, d);
    output << ",datesVisiting:<";
    for(int i = 0; i < d->datesVisiting->size(); i++)
    {
        d->datesVisiting->at(i)->write(output, d->datesVisiting->at(i));
        if(i < d->datesVisiting->size()-1)
        {
            output << "$";
        }
    }
    output << ">]";
}
int Auditor::getNumberOfVisits()
{
    return datesVisiting->size();
}
string Auditor::verticalHeader(int row)
{  
    if (row == 0)
    {
        return this->getName();
    }
    else if (row == 1)
    {
        return this->getLastname();
    }
    else if (row == 2)
    {
        return this->getDateBirth()->getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(this->getSalary());
    }
    return "";
}
string Auditor::horizontalHeader(int colomn)
{
    if (colomn == 0)
    {
        return "Name";
    }
    else if (colomn == 1)
    {
        return "Lastname";
    }
    else if (colomn == 2)
    {
        return "Date birth";
    }
    else if (colomn == 3)
    {
        return "Salary";
    }
    return "";
}