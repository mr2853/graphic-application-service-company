#ifndef ACCOUNTANT_HPP
#define ACCOUNTANT_HPP
#include <iostream>
#include <string>

#include "AbstractWorker.hpp"

using namespace std;

class Accountant : public AbstractWorker{
private:
    string bodyIssuedPermit;
    double maxAmountCompanyIncome;
    const string type = "Accountant";

public:
    Accountant();
    Accountant(string in, int changed);
    Accountant(string name, string lastname, Date *dateBirth, double salary);
    Accountant(string name, string lastname, Date *dateBirth, double salary, string bodyIssuedPermit, double maxAmountCompanyIncome);
    ~Accountant();

    string getBodyIssuedPermit() const;
	void setBodyIssuedPermit(string bodyIssuedPermit);
	double getMaxAmountCompanyIncome() const;
	void setMaxAmountCompanyIncome(double maxAmountCompanyIncome);
    virtual string getType() const;
    virtual void write(ostream &output, void *d);
    virtual void setDeleted();
};

#endif