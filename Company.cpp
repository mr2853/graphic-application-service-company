#include "Util.hpp"
#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Department.hpp"

Company::Company(){}
Company::~Company(){}
Company::Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*> departments)
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
Department* Company::getDepartments(int indeks) {
    return departments.at(indeks);
}
void Company::pushDepartments(Department *department) {
    departments.push_back(department);
}
void Company::setDepartments(vector<Department*> departments) {
    this->departments = departments;
}

void Company::readData1(string path)
{
    Company *company = this;
    ifstream in(path);
    getline(in, path);
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
    vector<Department*> departments = vector<Department*>();
    departments = readArray<Department>(path); 
    company->setName(name);
    company->setTaxIdentificationNumber(taxIdentificationNumber);
    company->setIdentificationNumber(identificationNumber);
    company->setDepartments(departments);
}

string Company::toString() const
{
    string t = "Name:" + name + ", Tax Identification Number:" + taxIdentificationNumber +
    ", Identification Number:" + identificationNumber;
    return t;
}