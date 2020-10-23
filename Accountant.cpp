#include "Accountant.hpp"

using namespace std;

Accountant::Accountant(){};
Accountant::~Accountant(){};
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