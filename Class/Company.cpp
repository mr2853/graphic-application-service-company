#include "../Util.hpp"
#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Department.hpp"

Company::Company(){}
Company::~Company(){}
Company::Company(string name, string taxIdentificationNumber, string identificationNumber)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(new vector<Department*>()){}

Company::Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*>* departments)
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(departments){}


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

void Company::readData1(string path)
{
    Company *company = this;
    ifstream in(path);
    string str;
    path = "";
    while(!in.eof()){
        getline(in, str);
        path += str;
    }
    //cout << "\n\nPathStart:" << path << "\n" << endl;
    string comma = ",";
    string lessThan = "<";
    string twoDots = ":";
    int index = path.find(twoDots);
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
    departments = Department::readArray(path); 
    company->setName(name);
    company->setTaxIdentificationNumber(taxIdentificationNumber);
    company->setIdentificationNumber(identificationNumber);
    company->setDepartments(departments);
    in.close();
}

string Company::toString() const
{
    string t = "Name:" + name + ", Tax Identification Number:" + taxIdentificationNumber +
    ", Identification Number:" + identificationNumber;
    return t;
}

vector<Commercialist*>* Company::getCompanyCommercialists()
{
    vector<Commercialist*>* ret;
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
        for(int j = 0; j < departments->at(i)->getAudits().size(); j++)
        {
            ret->push_back(departments->at(i)->getAudits().at(j));
        }
    }
    return ret;
}
vector<Accountant*>* Company::getCompanyAccountants()
{
    vector<Accountant*>* ret;
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