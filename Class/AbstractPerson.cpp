#include "AbstractPerson.hpp"

AbstractPerson::AbstractPerson(){};
AbstractPerson::~AbstractPerson(){};
AbstractPerson::AbstractPerson(string name, string lastname, Date *dateBirth) : name(name), lastname(lastname), dateBirth(dateBirth){}

string AbstractPerson::getName() {
	return name;
}

void AbstractPerson::setName(string name) {
	this->name = name;
}

string AbstractPerson::getLastname() {
	return lastname;
}

bool AbstractPerson::isDeleted() {
	return deleted;
}

void AbstractPerson::setDeleted() {
	deleted = true;
}

void AbstractPerson::setLastname(string lastname) {
	this->lastname = lastname;
}

void AbstractPerson::setDateBirth(Date *dateBirth) {
	this->dateBirth = dateBirth;
}

Date* AbstractPerson::getDateBirth() {
	return dateBirth;
}
string AbstractPerson::getType()
{
	return type;
}