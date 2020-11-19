#ifndef COMPANY_HPP
#define COMPANY_HPP
#include <iostream>
#include <string>
#include <vector>

#include "Department.hpp"
#include "AbstractWorker.hpp"

using namespace std;

class Company{
private:
    string name;
    string taxIdentificationNumber;
    string identificationNumber;
    vector<Department*> *departments;

public:
    Company();
    ~Company();
    Company(string name, string taxIdentificationNumber, string identificationNumber);
    Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*>* departments);
    
    string getName();
	void setName(string name);
	string getTaxIdentificationNumber();
	void setTaxIdentificationNumber(string taxIdentificationNumber);
	string getIdentificationNumber();
	void setIdentificationNumber(string identificationNumber);
	Department* getDepartment(int indeks);
	void pushDepartments(Department *department);
    void setDepartments(vector<Department*>* departments);
    vector<Department*>* getDepartments();
    int getDepartmentsSize();
    void readData1(string path);
    string toString() const;
    vector<Commercialist*>* getCompanyCommercialists();
    vector<Auditor*>* getCompanyAuditors();
    vector<Audit*>* getCompanyAudits();
    vector<Accountant*>* getCompanyAccountants();
    void removeDepartment(int index);
    double getMaxSalary();
    double getMinSalary();

};


#endif