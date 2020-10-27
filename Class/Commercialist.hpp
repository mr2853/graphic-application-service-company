#ifndef COMMERCIALIST_HPP
#define COMMERCIALIST_HPP
#include <iostream>
#include <string>
#include <vector>

#include "AbstractWorker.hpp"

using namespace std;

class Commercialist : public AbstractWorker{
private:
    vector<string> *businessContact;
    const string type = "Commercialist";
public:
    Commercialist();
    ~Commercialist();
    Commercialist(string in);
    Commercialist(string name, string lastname, Date *dateBirth, double salary);

    virtual string getType();
    string getContact(int indeks);
    void pushContact(string contact);
    void setBusinessContact(vector<string> *businessContact);
};

#endif