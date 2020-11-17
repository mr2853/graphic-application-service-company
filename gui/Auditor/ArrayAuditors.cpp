#include "ArrayAuditors.hpp"
ArrayAuditors::ArrayAuditors() : ArrayWorkers(){}
ArrayAuditors::ArrayAuditors(vector<Auditor*> *array) : ArrayWorkers(array){}
ArrayAuditors::~ArrayAuditors(){}

string ArrayAuditors::getText(int row, int column)
{
    Auditor *o = this->getRow(row);
    if (column == 0)
    {
        return o->getName();
    }
    else if (column == 1)
    {
        return o->getLastname();
    }
    else if (column == 2)
    {
        return o->getDateBirth()->getDateWithTime();
    }
    else if (column == 3)
    {
        return to_string(o->getSalary());
    }
    return "";
}