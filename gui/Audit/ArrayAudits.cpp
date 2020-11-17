#include "ArrayAudits.hpp"

ArrayAudits::ArrayAudits() : ArrayWorkers(){}
ArrayAudits::ArrayAudits(vector<Audit*> *array) : ArrayWorkers(array){}
ArrayAudits::~ArrayAudits(){}

string ArrayAudits::getText(int row, int column)
{
    Audit *o = this->getRow(row);
    if (column == 0)
    {
        return o->getDate()->getDateWithTime();
    }
    else if (column == 1)
    {
        return o->getAuditor()->getName();
    }
    else if (column == 2)
    {
        return o->getAuditor()->getLastname();
    }
    else if (column == 3)
    {
        return o->getAuditor()->getDateBirth()->getDate();
    }
    return "";
}
string ArrayAudits::horizontalHeader(int column)
{
    if (column == 0)
    {
        return "Date:";
    }
    else if (column == 1)
    {
        return "Name of Auditor:";
    }
    else if (column == 2)
    {
        return "Lastname of Auditor:";
    }
    else if (column == 3)
    {
        return "Date birth of Auditor:";
    }
    return "";
}
