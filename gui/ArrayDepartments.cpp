#include "ArrayDepartments.hpp"

ArrayDepartments::ArrayDepartments() : AbstractTableModel<Department*>()
{
    departments = new vector<Department*>();
}
ArrayDepartments::ArrayDepartments(vector<Department*> *departments) : AbstractTableModel<Department*>(), departments(departments)
{
}
int ArrayDepartments::numberOfRows()
{
    return departments->size();
}

int ArrayDepartments::numberOfColumns()
{
    return 4;
}
Department *ArrayDepartments::getRow(int indeks)
{
    return departments->at(indeks);
}

/*string ArrayDepartments::verticalHeader(int red)
{  
    stringstream sstream;
    sstream << red+1;
    return sstream.str();
}*/

void ArrayDepartments::pushRow(int row, Department* elem){
    departments->insert(departments->begin() + row, elem);
    AbstractTableModel<Department *>::pushRow(row, elem);
};

void ArrayDepartments::removeRow(int index)
{
    departments->erase(departments->begin() + index);
    AbstractTableModel::removeRow(index);
}

void ArrayDepartments::write(ostream &output)
{
    output << departments->size() << endl;
    for (int i = 0; i < departments->size(); i++)
    {
        output << departments->at(i) << endl;
    }
}
void ArrayDepartments::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        Department *novaOsoba;
        input >> tip;
        if (tip == "Department")
        {
            novaOsoba = new Department();
        }
        //input >> novaOsoba;
        pushElement(departments->size(), novaOsoba);
    }
}

string ArrayDepartments::getText(int row, int column)
{
    Department *o = departments->at(row);
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
string ArrayDepartments::verticalHeader(int row){  
    /*if (row == 0)
    {
        return departments->at(row)->getName();
    }
    else if (row == 1)
    {
        return departments->at(row)->getLastname();
    }
    else if (row == 2)
    {
        return departments->at(row)->getDateBirth().getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(departments->at(row)->getSalary());
    }
    else if (row == 4)
    {
        return departments->at(row)->getDateVisiting(0).getDateWithTime();
    }*/
    return to_string(row+1);
};
void ArrayDepartments::pushElement(int row, Department *a)
{
    this->pushRow(row, a);
}
ArrayDepartments::~ArrayDepartments(){}

void ArrayDepartments::add(Department *p)
{
    departments->push_back(p);
}
Department* ArrayDepartments::getDepartment(int in)
{
    return departments->at(in);
}