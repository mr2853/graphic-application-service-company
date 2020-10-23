#ifndef AUDITOR_HPP
#define AUDITOR_HPP
#include <iostream>
#include <vector>

#include "Date.hpp"
#include "AbstractWorker.hpp"

using namespace std;

class Auditor : public AbstractWorker{
private:
    vector<Date> *datesVisiting;

public:
    Auditor();
    ~Auditor();
    Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date> *datesVisiting);

    void pushDateVisiting(Date date);
    Date getDateVisiting(int indeks);
};

#endif