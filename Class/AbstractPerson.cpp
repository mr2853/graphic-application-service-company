#include "AbstractPerson.hpp"
#include "../Util.hpp"

AbstractPerson::AbstractPerson(){};
AbstractPerson::~AbstractPerson()
{
	this->setDeleted();
};
AbstractPerson::AbstractPerson(string name, string lastname, Date *dateBirth) : name(name), lastname(lastname), dateBirth(dateBirth){}

void AbstractPerson::write(ostream &output, void *data)
{
    AbstractPerson *d = (AbstractPerson*)data;
    output << "deleted:";
    if(d->deleted)
    {
        output << "true";
    }
    else
    {
        output << "false";
    }

	output << ",name:" << d->name << ",lastname:" << d->lastname << ",dateBirth:";
	d->dateBirth->write(output, d->dateBirth);
}
string AbstractPerson::getName() const {
	return name;
}

void AbstractPerson::setName(string name) {
    try
    {
        trim(name);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
	this->name = name;
}

string AbstractPerson::getLastname() const {
	return lastname;
}

bool AbstractPerson::isDeleted() {
	return deleted;
}

void AbstractPerson::setDeleted() {
	dateBirth->setDeleted();
	deleted = true;
}

void AbstractPerson::setLastname(string lastname) {
    try
    {
        trim(lastname);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
	this->lastname = lastname;
}

void AbstractPerson::setDateBirth(Date *dateBirth) {
	this->dateBirth = dateBirth;
}

Date* AbstractPerson::getDateBirth() const {
	return dateBirth;
}
string AbstractPerson::getType() const
{
	return type;
}