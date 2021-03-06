#include "../Util.hpp"
#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Department.hpp"
using namespace std;
Company::Company(){}
Company::~Company()
{
    
};
Company::Company(string name, string taxIdentificationNumber, string identificationNumber)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(new vector<Department*>()){}

Company::Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*>* departments)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(departments){}

string Company::getData(int column) const
{
    if (column == 0)
    {
        return this->getName();
    }
    else if (column == 1)
    {
        return this->getTaxIdentificationNumber();
    }
    else if (column == 2)
    {
        return this->getIdentificationNumber();
    }
    return "";
}
double Company::getMaxSalary() const
{
    double max = -1;
    for(int i = 0; i < departments->size(); i++)
    {
        if(max < departments->at(i)->getMaxSalary() || max == -1)
        {
            max = departments->at(i)->getMaxSalary();
        }
    }

    return max;
}
double Company::getMinSalary() const
{
    double min = -1;
    for(int i = 0; i < departments->size(); i++)
    {
        if(min > departments->at(i)->getMinSalary() || min == -1)
        {
            min = departments->at(i)->getMinSalary();
        }
    }
    
    return min;
}

int Company::getNumbOfWorkers() const
{
    int number = 0;
    for(int i = 0; i < departments->size(); i++)
    {
        number += departments->at(i)->getNumbOfWorkers();
    }
    return number;
}
string Company::getName() const {
    return name;
}
void Company::setName(string name) {
    try
    {
        trim(name);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    this->name = name;
}
string Company::getTaxIdentificationNumber() const {
    return taxIdentificationNumber;
}
void Company::setTaxIdentificationNumber(string taxIdentificationNumber) {
    try
    {
        trim(taxIdentificationNumber);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    this->taxIdentificationNumber = taxIdentificationNumber;
}
string Company::getIdentificationNumber() const {
    return identificationNumber;
}
void Company::setIdentificationNumber(string identificationNumber) {
    try
    {
        trim(identificationNumber);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    this->identificationNumber = identificationNumber;
}
Department* Company::getDepartment(int indeks) const {
    return departments->at(indeks);
}
void Company::pushDepartments(Department *department) {
    departments->push_back(department);
}
void Company::setDepartments(vector<Department*>* departments) {
    this->departments = departments;
}
int Company::getDepartmentsSize() const
{
    return departments->size();
}

vector<Company*>* Company::readData1(string path, int changed)
{
    vector<Company*>* ret = new vector<Company*>();
    ifstream in(path);
    string str;
    path = "";
    if(!in.is_open())
    {
        return ret;
    }
    while(!in.eof()){
        getline(in, str);
        path += str;
    }
    string comma = ",";
    string lessThan = "<";
    string twoDots = ":";

    while(path.find("Company[") != string::npos)
    {
        int index = path.find(twoDots);
        path.erase(0,index+1);
        index = path.find(comma);
        string deleted = path.substr(0, index);
        Company *company = new Company();

        index = path.find(twoDots);
        path.erase(0,index+1);
        index = path.find(comma);
        string name = path.substr(0, index);

        index = path.find(twoDots);
        path.erase(0,index+1);
        index = path.find(comma);
        string taxIdentificationNumber = path.substr(0, index);

        index = path.find(twoDots);
        path.erase(0,index+1);
        index = path.find(comma);
        string identificationNumber = path.substr(0, index);
        index = path.find(lessThan);
        
        path.erase(0,index+1);
        vector<Department*>* departments = new vector<Department*>();
        if(path.find("]$Company[") != string::npos)
        {
            index = path.find("]$Company[");
            departments = Department::readArray(path.substr(0, index), changed);
            path.erase(0,index + 1);
        }
        else
        {
            index = path.find_last_of(">]");
            departments = Department::readArray(path.substr(0, index), changed);
            path.erase(0, path.length());
        }
        
        company->setName(name);
        company->setTaxIdentificationNumber(taxIdentificationNumber);
        company->setIdentificationNumber(identificationNumber);
        company->setDepartments(departments);
        
        if(deleted == "true")
        {
            if(changed == 1)
            {
                continue;
            }
            
            company->setDeleted();
        }
        ret->push_back(company);
    }
    in.close();
    return ret;
}

bool Company::isDeleted() {
	return deleted;
}
void Company::setDeleted() {
    for(int i = 0; i < departments->size(); i++)
    {
        departments->at(i)->setDeleted();
    }
	deleted = true;
}
string Company::toString() const
{
    string t = "Name:" + name + ", Tax Identification Number:" + taxIdentificationNumber +
    ", Identification Number:" + identificationNumber;
    return t;
}

void Company::removeDepartment(int index)
{
    departments->erase(departments->begin() + index);
}
vector<Department*>* Company::getDepartments()
{
    return departments;
}

double Company::getSumSalaries() const
{
    double number = 0;
    for(int i = 0; i < departments->size(); i++)
    {
        number += departments->at(i)->getSumSalaries();
    }
    return number;
}

void Company::write(ostream &output, Company *d)
{
    output << "Company[deleted:"; 
    if(d->deleted)
    {
        output << "true";
    }
    else
    {
        output << "false";
    }

    output << ",name:" << d->name << ",taxIdentificationNumber:" << d->taxIdentificationNumber;
    output << ",identificationNumber:" << d->identificationNumber << ",departments:<";
    for(int i = 0; i < d->departments->size(); i++)
    {
        d->departments->at(i)->write(output, d->departments->at(i));
        if(i < d->departments->size()-1)
        {
            output << "$";
        }
    }

    output << ">]";
}