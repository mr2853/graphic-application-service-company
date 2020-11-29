#include "Accountant.hpp"
#include "../Util.hpp"
#include <string>

using namespace std;

Accountant::Accountant(){};
Accountant::~Accountant()
{
	this->setDeleted();
};
void Accountant::setDeleted() {
	AbstractWorker::setDeleted();
}
Accountant::Accountant(string in, int changed)
{
    vector<string> parts = tokenization(in, ":", ",", "Date", changed);
    if(parts.size() == 6){
        this->setName(parts.at(0));
        this->setLastname(parts.at(1));
		this->setDateBirth(new Date(parts.at(2), changed));
		this->setSalary(stod(parts.at(3)));
		this->bodyIssuedPermit = parts.at(4);
		this->maxAmountCompanyIncome = stod(parts.at(5));
    }
	else if(parts.size() == 7){
        this->setName(parts.at(1));
        this->setLastname(parts.at(2));
		this->setDateBirth(new Date(parts.at(3), changed));
		this->setSalary(stod(parts.at(4)));
		this->bodyIssuedPermit = parts.at(5);
		this->maxAmountCompanyIncome = stod(parts.at(6));
		this->setDeleted();
    }
}
void Accountant::write(ostream &output, void *data)
{
    Accountant *d = (Accountant*)data;
	output << "Accountant[";
    AbstractWorker::write(output, d);
    output << ",bodyIssuedPermit:" << d->bodyIssuedPermit << ",maxAmountCompanyIncome:" << d->maxAmountCompanyIncome;
    output << "]";
}
Accountant::Accountant(string name, string lastname, Date *dateBirth, double salary)
: AbstractWorker(name, lastname, dateBirth, salary), bodyIssuedPermit(""), maxAmountCompanyIncome(0) {}

Accountant::Accountant(string name, string lastname, Date *dateBirth, double salary, string bodyIssuedPermit, double maxAmountCompanyIncome)
: AbstractWorker(name, lastname, dateBirth, salary), bodyIssuedPermit(bodyIssuedPermit), 
    maxAmountCompanyIncome(maxAmountCompanyIncome){}

string Accountant::getBodyIssuedPermit() const {
	return bodyIssuedPermit;
}

void Accountant::setBodyIssuedPermit(string bodyIssuedPermit) {
	ltrim(bodyIssuedPermit);
	this->bodyIssuedPermit = bodyIssuedPermit;
}

double Accountant::getMaxAmountCompanyIncome() const {
	return maxAmountCompanyIncome;
}

void Accountant::setMaxAmountCompanyIncome(double maxAmountCompanyIncome) {
	this->maxAmountCompanyIncome = maxAmountCompanyIncome;
}
string Accountant::getType() const
{
	return type;
}