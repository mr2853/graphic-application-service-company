#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP
#include <iostream>
#include <string>
#include <vector>

#include "AbstractWorker.hpp"
#include "Audit.hpp"

using namespace std;

class Department
{
private:
    vector<AbstractWorker*> worker;
    AbstractWorker* headOfDepartment;
    string name;
    vector<Audit*> audits;

public:
    Department();
    ~Department();
    Department(string &in);
    Department(vector<AbstractWorker*> worker, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits);
    //static vector<Department*> readData1(string in);

    vector<AbstractWorker*> getWorker();
    void setWorker(vector<AbstractWorker*> worker);
    AbstractWorker* getHeadOfDepartment();
    void setHeadOfDepartment(AbstractWorker *headOfDepartment);
    string getName();
    void setName(string name);
    vector<Audit*> getAudits();
    void setAudits(vector<Audit*> audits);
};

#endif