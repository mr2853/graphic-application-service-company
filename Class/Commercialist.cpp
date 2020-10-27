#include "Commercialist.hpp"
#include "../Util.hpp"
#include <string>
using namespace std;

Commercialist::Commercialist(){};
Commercialist::~Commercialist(){};
Commercialist::Commercialist(string in)
{
    vector<string> parts = tokenization(in, ":", ",", "");
    if(parts.size() == 2){
       this->setName(parts.at(0));
       this->setLastname(parts.at(1));
       this->setDateBirth(new Date(parts.at(2)));
       this->setSalary(stod(parts.at(3)));
       vector<string> businessContact = tokenization(parts.at(4), ":", "$", "");
        this->setBusinessContact(&businessContact);
    }
}
Commercialist::Commercialist(string name, string lastname, Date *dateBirth, double salary) : AbstractWorker(name, lastname, dateBirth, salary){}

string Commercialist::getContact(int indeks)
{
    return businessContact->at(indeks);
}
void Commercialist::pushContact(string contact)
{
    businessContact->push_back(contact);
}
void Commercialist::setBusinessContact(vector<string> *businessContact)
{
    this->businessContact = businessContact;
}
string Commercialist::getType()
{
	return type;
}