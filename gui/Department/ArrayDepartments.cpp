#include "ArrayDepartments.hpp"

ArrayDepartments::ArrayDepartments() : ArrayWorkers(){}
ArrayDepartments::ArrayDepartments(vector<Department*> *array) : ArrayWorkers(array){}
ArrayDepartments::~ArrayDepartments(){}

string ArrayDepartments::getText(int row, int column)
{
    Department *o = this->getRow(row);
    if (column == 0)
    {
        return o->getName();
    }
    else if (column == 1)
    {
        return o->getHeadOfDepartment()->getName();
    }
    else if (column == 2)
    {
        return o->getHeadOfDepartment()->getLastname();
    }
    else if (column == 3)
    {
        return o->getHeadOfDepartment()->getType();
    }
    return "";
}
string ArrayDepartments::horizontalHeader(int column)
{
    if (column == 0)
    {
        return "Name";
    }
    else if (column == 1)
    {
        return "CEO name:";
    }
    else if (column == 2)
    {
        return "CEO lastname";
    }
    else if (column == 3)
    {
        return "CEO worker type";
    }
    return "";
}
