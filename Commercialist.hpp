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
public:
    Commercialist();
    ~Commercialist();
    Commercialist(string name, string lastname, Date *dateBirth, double salary);

    string getContact(int indeks);
    void pushContact(string contact);
};

#endif