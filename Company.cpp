#include "Company.hpp"
#include <iostream>
#include <fstream>
#include <string>

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

void Company::ucitajPodatke()
{
    Company *company = this;

}