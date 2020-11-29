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
    vector<Commercialist*>* commercialists = new vector<Commercialist*>();
    vector<Auditor*>* auditors = new vector<Auditor*>();
    vector<Accountant*>* accountants = new vector<Accountant*>();

    AbstractWorker* headOfDepartment;
    string name;
    bool deleted = false;
    vector<Audit*>* audits = new vector<Audit*>();

public:
    Department();
    ~Department();
    Department(string &in, int changed);
    Department(AbstractWorker *headOfDepartment, string name);
    Department(vector<Commercialist*>* commercialists, vector<Auditor*>* auditors,
    vector<Accountant*>* accountants, AbstractWorker *headOfDepartment, string name, vector<Audit*>* audits);

    virtual bool isDeleted();
    virtual void setDeleted();
    vector<AbstractWorker*> getWorker() const;
    void setWorker(vector<AbstractWorker*>* worker);
    AbstractWorker* getHeadOfDepartment() const;
    void setHeadOfDepartment(AbstractWorker *headOfDepartment);
    string getName() const;
    void setName(string name);
    vector<Audit*>* getAudits();
    void setAudits(vector<Audit*>* audits);
    vector<Commercialist*>* getCommercialists() const;
	void setCommercialists(vector<Commercialist*>* commercialists);
	vector<Auditor*>* getAuditors() const;
	void setAuditors(vector<Auditor*>* auditors);
	vector<Accountant*>* getAccountants() const;
	void setAccountants(vector<Accountant*>* accountants);
    static vector<Department*>* readArray(string in, int changed);
    double getMaxSalary() const;
    double getMinSalary() const;
    void write(ostream &output, Department *osobe);
    string getData(int column) const;
    int getNumbOfWorkers() const;
};

#endif