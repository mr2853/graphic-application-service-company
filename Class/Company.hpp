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
    bool deleted = false;

public:
    Company();
    ~Company();
    Company(string name, string taxIdentificationNumber, string identificationNumber);
    Company(string name, string taxIdentificationNumber, string identificationNumber, vector<Department*>* departments);
    
    string getName() const;
	void setName(string name);
    virtual bool isDeleted();
    virtual void setDeleted();
	string getTaxIdentificationNumber() const;
	void setTaxIdentificationNumber(string taxIdentificationNumber);
	string getIdentificationNumber() const;
	void setIdentificationNumber(string identificationNumber);
	Department* getDepartment(int indeks) const;
	void pushDepartments(Department *department);
    void setDepartments(vector<Department*>* departments);
    vector<Department*>* getDepartments();
    
    int getDepartmentsSize() const;
    static vector<Company*>* readData1(string path, int changed=0);
    string toString() const;
    
    void removeDepartment(int index);
    double getMaxSalary() const;
    double getMinSalary() const;
    int getNumbOfWorkers() const;
    void write(ostream &output, Company *d);
    string getData(int column) const;

};


#endif