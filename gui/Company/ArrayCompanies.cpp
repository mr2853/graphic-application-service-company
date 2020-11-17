#include "ArrayCompanies.hpp"

ArrayCompanies::ArrayCompanies() : ArrayWorkers(){}
ArrayCompanies::ArrayCompanies(vector<Company*> *array) : ArrayWorkers(array){}
ArrayCompanies::~ArrayCompanies(){}

int ArrayCompanies::numberOfColumns()
{
    return 3;
}
string ArrayCompanies::getText(int row, int column)
{
    Company *o = this->getRow(row);
    if (column == 0)
    {
        return o->getName();
    }
    else if (column == 1)
    {
        return o->getTaxIdentificationNumber();
    }
    else if (column == 2)
    {
        return o->getIdentificationNumber();
    }
    return "";
}
string ArrayCompanies::horizontalHeader(int column)
{
    if (column == 0)
    {
        return "Name";
    }
    else if (column == 1)
    {
        return "Tax ID:";
    }
    else if (column == 2)
    {
        return "ID";
    }
    return "";
}
