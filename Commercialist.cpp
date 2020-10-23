#include "Commercialist.hpp"

Commercialist::Commercialist(){};
Commercialist::~Commercialist(){};
Commercialist::Commercialist(string name, string lastname, Date *dateBirth, double salary) : AbstractWorker(name, lastname, dateBirth, salary){}

string Commercialist::getContact(int indeks)
{
    return businessContact->at(indeks);
}
void Commercialist::pushContact(string contact)
{
    businessContact->push_back(contact);
}
