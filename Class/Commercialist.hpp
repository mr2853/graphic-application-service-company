#ifndef COMMERCIALIST_HPP
#define COMMERCIALIST_HPP
#include <iostream>
#include <string>
#include <vector>

#include "AbstractWorker.hpp"

using namespace std;

class Commercialist : public AbstractWorker{
private:
    vector<string*> *businessContact = new vector<string*>();
    const string type = "Commercialist";
public:
    Commercialist();
    ~Commercialist();
    Commercialist(string in, int changed);
    Commercialist(string name, string lastname, Date *dateBirth, double salary);
    Commercialist(string name, string lastname, Date *dateBirth, double salary, vector<string*> *businessContact);

    virtual string getType() const;
    string* getContact(int indeks) const;
    void pushContact(string* contact);
    void setBusinessContact(vector<string*> *businessContact);
    int getNumberOfBusinessContact() const;
    string* getBusinessContact(int index) const;
    virtual void write(ostream &output, void *d);
    virtual void setDeleted();
};

#endif