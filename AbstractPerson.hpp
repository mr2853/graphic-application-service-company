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
    ~AbstractPerson();
    AbstractPerson(string name, string lastname, Date *dateBirth);

    virtual string getName() = 0;
	virtual void setName(string name) = 0;
	virtual string getLastname() = 0;
	virtual void setLastname(string lastname) = 0;
};

#endif