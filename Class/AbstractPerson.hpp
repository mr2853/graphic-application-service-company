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
    const string type = "AbstractPerson";
    bool deleted = false;

public:
    AbstractPerson();
    virtual ~AbstractPerson();
    AbstractPerson(string name, string lastname, Date *dateBirth);

    virtual string getType() const;
    virtual string getName() const;
	virtual void setName(string name);
	virtual string getLastname() const;
	virtual void setLastname(string lastname);
    virtual Date* getDateBirth() const;
	virtual void setDateBirth(Date *dateBirth);
    virtual bool isDeleted();
    virtual void setDeleted();
    virtual void write(ostream &output, void *d);
};

#endif