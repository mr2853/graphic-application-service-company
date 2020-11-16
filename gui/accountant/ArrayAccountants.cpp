#include "ArrayAccountants.hpp"
ArrayAccountants::ArrayAccountants() : ArrayWorkers(){}
ArrayAccountants::ArrayAccountants(vector<Accountant*> *array) : ArrayWorkers(array){}
ArrayAccountants::~ArrayAccountants(){}
int ArrayAccountants::numberOfColumns()
{
    return 6;
}

string ArrayAccountants::getText(int row, int column)
{
    Accountant *o = this->getRow(row);
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
    else if (column == 4)
    {
        return o->getBodyIssuedPermit();
    }
    else if (column == 5)
    {
        return to_string(o->getMaxAmountCompanyIncome());
    }
    return "";
}
string ArrayAccountants::horizontalHeader(int column)
{
    if (column == 0)
    {
        return "Name";
    }
    else if (column == 1)
    {
        return "Lastname";
    }
    else if (column == 2)
    {
        return "Date birth";
    }
    else if (column == 3)
    {
        return "Salary";
    }
    else if (column == 4)
    {
        return "Issued permit";
    }
    else if (column == 5)
    {
        return "Max company income";
    }
    return "";
}
