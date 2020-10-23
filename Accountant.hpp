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

public:
    Accountant();
    Accountant(string name, string lastname, Date *dateBirth, double salary, string bodyIssuedPermit, double maxAmountCompanyIncome);
    ~Accountant();

    string getBodyIssuedPermit();

	void setBodyIssuedPermit(string bodyIssuedPermit);

	double getMaxAmountCompanyIncome();

	void setMaxAmountCompanyIncome(double maxAmountCompanyIncome);
};

#endif