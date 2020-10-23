#include "AbstractPerson.hpp"

AbstractPerson::AbstractPerson(){};
AbstractPerson::AbstractPerson(string name, string lastname, Date *dateBirth) : name(name), lastname(lastname), dateBirth(dateBirth){}
AbstractPerson::~AbstractPerson(){};

string AbstractPerson::getName() {
	return name;
}

void AbstractPerson::setName(string name) {
	this->name = name;
}

string AbstractPerson::AbstractPerson::getLastname() {
	return lastname;
}

void AbstractPerson::setLastname(string lastname) {
	this->lastname = lastname;
}