#include "Auditor.hpp"

Auditor::Auditor(){}
Auditor::~Auditor(){}
Auditor::Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date> *datesVisiting)
    : AbstractWorker(name, lastname, dateBirth, salary), datesVisiting(datesVisiting){}

void Auditor::pushDateVisiting(Date date)
{
    datesVisiting->push_back(date);
}
Date Auditor::getDateVisiting(int indeks)
{
    return datesVisiting->at(indeks);
}