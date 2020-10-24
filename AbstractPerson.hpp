#ifndef ABSTRACT_PERSON_HPP
#define ABSTRACT_PERSON_HPP
#include <iostream>
#include <string>
#include "Date.hpp"

using namespace std;

class AbstractPerson
{
private:
    string name;
    string lastname;
    Date *dateBirth;

public:
    AbstractPerson();
    virtual ~AbstractPerson();
    AbstractPerson(string name, string lastname, Date *dateBirth);

    virtual string getName();
	virtual void setName(string name);
	virtual string getLastname();
	virtual void setLastname(string lastname);
    virtual Date* getDateBirth();
	virtual void setDateBirth(Date *dateBirth);
};

#endif