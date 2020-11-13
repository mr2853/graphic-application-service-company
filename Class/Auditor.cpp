#include "../Util.hpp"
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
    vector<string> t = tokenization(in, ":", ",", "");
    text.erase(0, index+10);
    
    //index = text.find(twoDots);
    //text.erase(0,index+1);// bilo + 5
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
    vector<Date*> *dates = new vector<Date*>();
    *dates = Date::readArray(text);
    
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
Auditor::Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date*> *datesVisiting)
    : AbstractWorker(name, lastname, dateBirth, salary), datesVisiting(datesVisiting){}

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
/*void Auditor::zapisi(ostream &output)
{
    output << getType() << " " << this->getName() << endl << this->getLastname() << endl;
}
void Auditor::procitaj(istream &input)
{
    input >> ws;
    string ime, prezime;
    getline(input, ime, '\n');
    getline(input, prezime, '\n');
    this->setName(ime);
    this->setLastname(prezime);
}*/
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
        return this->getDateBirth().getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(this->getSalary());
    }
    /*else if (row == 4)
    {
        return auditors.at(row)->getDateVisiting(0).getDateWithTime();
    }*/
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