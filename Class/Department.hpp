#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP
#include <iostream>
#include <string>
#include <vector>

#include "AbstractWorker.hpp"
#include "Audit.hpp"
#include "Commercialist.hpp"
#include "Accountant.hpp"

using namespace std;

class Department
{
private:
    vector<Commercialist*> commercialists;
    vector<Auditor*> auditors;
    vector<Accountant*> accountants;

    AbstractWorker* headOfDepartment;
    string name;
    bool deleted = false;
    vector<Audit*> audits;

public:
    Department();
    ~Department();
    Department(string &in, int changed);
    Department(AbstractWorker *headOfDepartment, string name);
    Department(vector<Commercialist*> commercialists, vector<Auditor*> auditors,
    vector<Accountant*> accountants, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits);

    virtual bool isDeleted();
    virtual void setDeleted();
    vector<AbstractWorker*> getWorker();
    void setWorker(vector<AbstractWorker*> worker);
    AbstractWorker* getHeadOfDepartment();
    void setHeadOfDepartment(AbstractWorker *headOfDepartment);
    string getName();
    void setName(string name);
    vector<Audit*>* getAudits();
    void setAudits(vector<Audit*> audits);
    vector<Commercialist*>* getCommercialists();
	void setCommercialists(vector<Commercialist*> commercialists);
	vector<Auditor*>* getAuditors();
	void setAuditors(vector<Auditor*> auditors);
	vector<Accountant*>* getAccountants();
	void setAccountants(vector<Accountant*> accountants);
    static vector<Department*>* readArray(string in, int changed);
    double getMaxSalary();
    double getMinSalary();
    void write(ostream &output, Department *osobe);
};

#endif