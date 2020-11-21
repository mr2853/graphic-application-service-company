#include "../Util.hpp"
#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Department.hpp"
using namespace std;
Company::Company(){}
Company::~Company(){}
Company::Company(string name, string taxIdentificationNumber, string identificationNumber)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(new vector<Department*>()){}

Company::Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*>* departments)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(departments){}


double Company::getMaxSalary()
{
    double max = -1;
    for(int j = 0; j < this->getCompanyAccountants()->size(); j++)
    {
        if(max < this->getCompanyAccountants()->at(j)->getSalary() || max == -1)
        {
            max = this->getCompanyAccountants()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCompanyCommercialists()->size(); j++)
    {
        if(max < this->getCompanyCommercialists()->at(j)->getSalary() || max == -1)
        {
            max = this->getCompanyCommercialists()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCompanyAuditors()->size(); j++)
    {
        if(max < this->getCompanyAuditors()->at(j)->getSalary() || max == -1)
        {
            max = this->getCompanyAuditors()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->departments->size(); j++)
    {
        if(max < this->departments->at(j)->getHeadOfDepartment()->getSalary() || max == -1)
        {
            max = this->departments->at(j)->getHeadOfDepartment()->getSalary();
        }
    }
    return max;
}
double Company::getMinSalary()
{
    double min = -1;
    for(int j = 0; j < this->getCompanyAccountants()->size(); j++)
    {
        if(min > this->getCompanyAccountants()->at(j)->getSalary() || min == -1)
        {
            min = this->getCompanyAccountants()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCompanyCommercialists()->size(); j++)
    {
        if(min > this->getCompanyCommercialists()->at(j)->getSalary() || min == -1)
        {
            min = this->getCompanyCommercialists()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCompanyAuditors()->size(); j++)
    {
        if(min > this->getCompanyAuditors()->at(j)->getSalary() || min == -1)
        {
            min = this->getCompanyAuditors()->at(j)->getSalary();
        }
    }
    
    for(int j = 0; j < this->departments->size(); j++)
    {
        if(min > this->departments->at(j)->getHeadOfDepartment()->getSalary() || min == -1)
        {
            min = this->departments->at(j)->getHeadOfDepartment()->getSalary();
        }
    }
    return min;
}
string Company::getName() {
    return name;
}
void Company::setName(string name) {
    this->name = name;
}
string Company::getTaxIdentificationNumber() {
    return taxIdentificationNumber;
}
void Company::setTaxIdentificationNumber(string taxIdentificationNumber) {
    this->taxIdentificationNumber = taxIdentificationNumber;
}
string Company::getIdentificationNumber() {
    return identificationNumber;
}
void Company::setIdentificationNumber(string identificationNumber) {
    this->identificationNumber = identificationNumber;
}
Department* Company::getDepartment(int indeks) {
    return departments->at(indeks);
}
void Company::pushDepartments(Department *department) {
    departments->push_back(department);
}
void Company::setDepartments(vector<Department*>* departments) {
    this->departments = departments;
}
int Company::getDepartmentsSize()
{
    return departments->size();
}

vector<Company*>* Company::readData1(string path, int changed)
{
    vector<Company*>* ret = new vector<Company*>();
    ifstream in(path);
    string str;
    path = "";
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
        if(deleted == "true")
        {
            if(changed == 1)
            {
                continue;
            }
            company->setDeleted();
        }

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
        if(path.find("$Company[") != string::npos)
        {
            index = path.find("$Company[");
            departments = Department::readArray(path.substr(0, index), changed);
            path.erase(0,index);
        }
        else
        {
            departments = Department::readArray(path, changed);
            path.erase(0,index);
            path.erase(0, path.length());
        }
        company->setName(name);
        company->setTaxIdentificationNumber(taxIdentificationNumber);
        company->setIdentificationNumber(identificationNumber);
        company->setDepartments(departments);
        ret->push_back(company);
    }
    in.close();
    return ret;
}

bool Company::isDeleted() {
	return deleted;
}
void Company::setDeleted() {
	deleted = true;
}
string Company::toString() const
{
    string t = "Name:" + name + ", Tax Identification Number:" + taxIdentificationNumber +
    ", Identification Number:" + identificationNumber;
    return t;
}

vector<Commercialist*>* Company::getCompanyCommercialists()
{
    vector<Commercialist*>* ret = new vector<Commercialist*>();
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getCommercialists()->size(); j++)
        {
            ret->push_back(departments->at(i)->getCommercialists()->at(j));
        }
    }
    return ret;
}
vector<Auditor*>* Company::getCompanyAuditors()
{
    vector<Auditor*> *ret = new vector<Auditor*>();
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getAuditors()->size(); j++)
        {
            ret->push_back(departments->at(i)->getAuditors()->at(j));
        }
    }
    return ret;
}
vector<Audit*>* Company::getCompanyAudits()
{
    vector<Audit*> *ret = new vector<Audit*>();
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getAudits()->size(); j++)
        {
            ret->push_back(departments->at(i)->getAudits()->at(j));
        }
    }
    return ret;
}
vector<Accountant*>* Company::getCompanyAccountants()
{
    vector<Accountant*>* ret = new vector<Accountant*>();
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getAccountants()->size(); j++)
        {
            ret->push_back(departments->at(i)->getAccountants()->at(j));
        }
    }
    return ret;
}
void Company::removeDepartment(int index)
{
    departments->erase(departments->begin() + index);
}
vector<Department*>* Company::getDepartments()
{
    return departments;
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