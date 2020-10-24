#include "Accountant.hpp"
#include "Util.hpp"
#include <string>

using namespace std;

Accountant::Accountant(){};
Accountant::~Accountant(){};
Accountant::Accountant(string in)
{
    vector<string> parts = tokenization(in, ":", ",");
    if(parts.size() == 6){
        this->setName(parts.at(0));
        this->setLastname(parts.at(1));
		this->setDateBirth(new Date(parts.at(2)));
		this->setSalary(stod(parts.at(3)));
		this->bodyIssuedPermit = parts.at(4);
		this->maxAmountCompanyIncome = stod(parts.at(5));
    }
}
Accountant::Accountant(string name, string lastname, Date *dateBirth, double salary, string bodyIssuedPermit, double maxAmountCompanyIncome)
: AbstractWorker(name, lastname, dateBirth, salary), bodyIssuedPermit(bodyIssuedPermit), 
    maxAmountCompanyIncome(maxAmountCompanyIncome){}

string Accountant::getBodyIssuedPermit() {
	return bodyIssuedPermit;
}

void Accountant::setBodyIssuedPermit(string bodyIssuedPermit) {
	this->bodyIssuedPermit = bodyIssuedPermit;
}

double Accountant::getMaxAmountCompanyIncome() {
	return maxAmountCompanyIncome;
}

void Accountant::setMaxAmountCompanyIncome(double maxAmountCompanyIncome) {
	this->maxAmountCompanyIncome = maxAmountCompanyIncome;
}