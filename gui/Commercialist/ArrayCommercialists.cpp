#include "ArrayCommercialists.hpp"

ArrayCommercialists::ArrayCommercialists() : ArrayWorkers(){}
ArrayCommercialists::ArrayCommercialists(vector<Commercialist*> *commercialists) : ArrayWorkers(commercialists){}
ArrayCommercialists::~ArrayCommercialists(){}
string ArrayCommercialists::getText(int row, int column)
{
    Commercialist *o = this->getRow(row);
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