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
    AbstractWorker *headOfDepartment;
    string name;
    vector<Audit*> audits;

public:
    Department();
    ~Department();
    Department(vector<AbstractWorker*> worker, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits);
    
};

#endif