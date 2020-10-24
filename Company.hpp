#ifndef COMPANY_HPP
#define COMPANY_HPP
#include <iostream>
#include <string>
#include <vector>

#include "Department.hpp"

using namespace std;

class Company{
private:
    string name;
    string taxIdentificationNumber;
    string identificationNumber;
    vector<Department*> departments;

public:
    Company();
    ~Company();
    Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*> departments);
    
    string getName();
	void setName(string name);
	string getTaxIdentificationNumber();
	void setTaxIdentificationNumber(string taxIdentificationNumber);
	string getIdentificationNumber();
	void setIdentificationNumber(string identificationNumber);
	Department* getDepartments(int indeks);
	void pushDepartments(Department *department);
    void setDepartments(vector<Department*> departments);
    void readData1(string path);
    string toString() const;

};

#endif