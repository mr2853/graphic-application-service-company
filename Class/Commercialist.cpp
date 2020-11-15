#include "Commercialist.hpp"
#include "../Util.hpp"
#include <string>
using namespace std;

Commercialist::Commercialist(){};
Commercialist::~Commercialist(){};
Commercialist::Commercialist(string in)
{ //salary:300,businessContact<contact:contact 1$contact:contact 2$contact:contact 3>]#Auditor[d
    vector<string> parts = tokenization(in, ":", ",", "Commercialist");
    if(parts.size() == 5){
       this->setName(parts.at(0));
       this->setLastname(parts.at(1));
       this->setDateBirth(new Date(parts.at(2)));
       this->setSalary(stod(parts.at(3)));

       vector<string*>* businessContact = new vector<string*>(0);
       string part = parts.at(4).substr(0, parts.at(4).length()-1);
       vector<string> a = tokenization(part, ":", "$");
       
       for(string s : a){
           businessContact->push_back(new string(s));
       }
       this->setBusinessContact(businessContact);
    }
}
Commercialist::Commercialist(string name, string lastname, Date *dateBirth, double salary) : AbstractWorker(name, lastname, dateBirth, salary){}

string* Commercialist::getContact(int indeks)
{
    return businessContact->at(indeks);
}
void Commercialist::pushContact(string* contact)
{
    businessContact->push_back(contact);
}
int Commercialist::getNumberOfBusinessContact()
{
    return businessContact->size();
}
void Commercialist::setBusinessContact(vector<string*> *businessContact)
{
    this->businessContact = businessContact;
}
string Commercialist::getType()
{
	return type;
}