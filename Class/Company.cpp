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
    : name(name), taxIdentificationNumber(taxIdentificationNumber), identificationNumber(identificationNumber), departments(departments)
{
    // for(int i = 0; i < departments->size(); i++)
    // {
    //     for(int j = 0; j < departments->at(i)->getAudits()->size(); j++)
    //     {
    //         audits->push_back(departments->at(i)->getAudits()->at(j));
    //     }
    // }
}

// vector<Audit*>* Company::getAudits()
// {
//     return audits;
// }
string Company::getData(int column)
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
double Company::getMaxSalary()
{
    double max = -1;
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getCommercialists()->size(); j++)
        {
            if(max < departments->at(i)->getCommercialists()->at(j)->getSalary() || max == -1)
            {
                max = departments->at(i)->getCommercialists()->at(j)->getSalary();
            }
        }

        for(int j = 0; j < departments->at(i)->getAccountants()->size(); j++)
        {
            if(max < departments->at(i)->getAccountants()->at(j)->getSalary() || max == -1)
            {
                max = departments->at(i)->getAccountants()->at(j)->getSalary();
            }
        }

        for(int j = 0; j < departments->at(i)->getAuditors()->size(); j++)
        {
            if(max < departments->at(i)->getAuditors()->at(j)->getSalary() || max == -1)
            {
                max = departments->at(i)->getAuditors()->at(j)->getSalary();
            }
        }
    }

    for(int j = 0; j < departments->size(); j++)
    {
        if(max < departments->at(j)->getHeadOfDepartment()->getSalary() || max == -1)
        {
            max = departments->at(j)->getHeadOfDepartment()->getSalary();
        }
    }
    return max;
}
double Company::getMinSalary()
{
    double min = -1;
    for(int i = 0; i < departments->size(); i++)
    {
        for(int j = 0; j < departments->at(i)->getCommercialists()->size(); j++)
        {
            if(min > departments->at(i)->getCommercialists()->at(j)->getSalary() || min == -1)
            {
                min = departments->at(i)->getCommercialists()->at(j)->getSalary();
            }
        }

        for(int j = 0; j < departments->at(i)->getAccountants()->size(); j++)
        {
            if(min > departments->at(i)->getAccountants()->at(j)->getSalary() || min == -1)
            {
                min = departments->at(i)->getAccountants()->at(j)->getSalary();
            }
        }

        for(int j = 0; j < departments->at(i)->getAuditors()->size(); j++)
        {
            if(min > departments->at(i)->getAuditors()->at(j)->getSalary() || min == -1)
            {
                min = departments->at(i)->getAuditors()->at(j)->getSalary();
            }
        }
    }

    for(int j = 0; j < departments->size(); j++)
    {
        if(min > departments->at(j)->getHeadOfDepartment()->getSalary() || min == -1)
        {
            min = departments->at(j)->getHeadOfDepartment()->getSalary();
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
    //cout << "prosao" << endl;
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
        
        //cout << "path size: " << path.size() << endl;
        path.erase(0,index+1);
        //cout << "path size: " << path.size() << endl;
        vector<Department*>* departments = new vector<Department*>();
        if(path.find("$Company[") != string::npos)
        {
            index = path.find("$Company[");
            departments = Department::readArray(path.substr(0, index), changed);
            path.erase(0,index);
        }
        else
        {
            //cout << "ovde" << endl;
            departments = Department::readArray(path, changed);
            //cout << "ovde1" << endl;
            //cout << "path size: " << path.size() << endl;
            //cout << index << endl;
            path.erase(0,index);
            //cout << "ovde1.2" << endl;
            path.erase(0, path.length());
            //cout << "ovde2" << endl;
        }
        //cout << "ovde3" << endl;
        company->setName(name);
        company->setTaxIdentificationNumber(taxIdentificationNumber);
        company->setIdentificationNumber(identificationNumber);
        company->setDepartments(departments);
        
        //cout << "prosao1" << endl;
        if(deleted == "true")
        {
            if(changed == 1)
            {
                //cout << "here1" << endl;
                continue;
                //cout << "here2" << endl;
            }
            
            //cout << "here11" << endl;
            company->setDeleted();
        }
        //cout << "prosao2" << endl;

        ret->push_back(company);
    }
    in.close();
    //cout << "kraj" << endl;
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

// vector<Commercialist*>* Company::getCompanyCommercialists()
// {
//     vector<Commercialist*>* ret = new vector<Commercialist*>();
//     for(int i = 0; i < departments->size(); i++)
//     {
//         for(int j = 0; j < departments->at(i)->getCommercialists()->size(); j++)
//         {
//             ret->push_back(departments->at(i)->getCommercialists()->at(j));
//         }
//     }
//     return ret;
// }
// vector<Auditor*>* Company::getCompanyAuditors()
// {
//     vector<Auditor*> *ret = new vector<Auditor*>();
//     for(int i = 0; i < departments->size(); i++)
//     {
//         for(int j = 0; j < departments->at(i)->getAuditors()->size(); j++)
//         {
//             ret->push_back(departments->at(i)->getAuditors()->at(j));
//         }
//     }
//     return ret;
// }
// vector<Audit*>* Company::getCompanyAudits()
// {
//     vector<Audit*> *ret = new vector<Audit*>();
//     for(int i = 0; i < departments->size(); i++)
//     {
//         for(int j = 0; j < departments->at(i)->getAudits()->size(); j++)
//         {
//             ret->push_back(departments->at(i)->getAudits()->at(j));
//         }
//     }
//     return ret;
// }
// vector<Accountant*>* Company::getCompanyAccountants()
// {
//     vector<Accountant*>* ret = new vector<Accountant*>();
//     for(int i = 0; i < departments->size(); i++)
//     {
//         for(int j = 0; j < departments->at(i)->getAccountants()->size(); j++)
//         {
//             ret->push_back(departments->at(i)->getAccountants()->at(j));
//         }
//     }
//     return ret;
// }
void Company::removeDepartment(int index)
{
    departments->erase(departments->begin() + index);
}
vector<Department*>* Company::getDepartments()
{
    return departments;
}
// vector<Department> Company::getDepartmentsOriginal()
// {
//     vector<Department> ret = vector<Department>();
//     for(int i = 0; i < departments->size(); i++)
//     {
//         ret.push_back(*departments->at(i));
//     }
//     return ret;
// }
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

    // output << ">,audits:<";
    // for(int i = 0; i < d->audits->size(); i++)
    // {
    //     d->audits->at(i)->write(output, d->audits->at(i));
    //     if(i < d->audits->size()-1)
    //     {
    //         output << "$";
    //     }
    // }
    output << ">]";
}