#include "ArrayAuditors.hpp"

ArrayAuditors::ArrayAuditors() : AbstractTableModel<Auditor *>()
{
    auditors = new vector<Auditor *>();
}
int ArrayAuditors::numberOfRows()
{
    return auditors->size();
}

int ArrayAuditors::numberOfColumns()
{
    return 4;
}
Auditor *ArrayAuditors::getRow(int indeks)
{
    return auditors->at(indeks);
}

/*string ArrayAuditors::verticalHeader(int red)
{  
    stringstream sstream;
    sstream << red+1;
    return sstream.str();
}*/

void ArrayAuditors::pushRow(int row, Auditor* elem){
    auditors->insert(auditors->begin() + row, elem);
    AbstractTableModel<Auditor *>::pushRow(row, elem);
};

void ArrayAuditors::removeRow(int index)
{
    auditors->erase(auditors->begin() + index);
    AbstractTableModel::removeRow(index);
}

void ArrayAuditors::write(ostream &output)
{
    output << auditors->size() << endl;
    for (int i = 0; i < auditors->size(); i++)
    {
        output << auditors->at(i) << endl;
    }
}
void ArrayAuditors::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        Auditor *novaOsoba;
        input >> tip;
        if (tip == "Auditor")
        {
            novaOsoba = new Auditor();
        }
        //input >> novaOsoba;
        pushElement(auditors->size(), novaOsoba);
    }
}

string ArrayAuditors::getText(int row, int column)
{
    Auditor *o = auditors->at(row);
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
        return o->getDateBirth().getDateWithTime();
    }
    else if (column == 3)
    {
        return to_string(o->getSalary());
    }
    return "";
}
string ArrayAuditors::horizontalHeader(int column)
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
    return "";
}
string ArrayAuditors::verticalHeader(int row){  
    /*if (row == 0)
    {
        return auditors->at(row)->getName();
    }
    else if (row == 1)
    {
        return auditors->at(row)->getLastname();
    }
    else if (row == 2)
    {
        return auditors->at(row)->getDateBirth().getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(auditors->at(row)->getSalary());
    }
    else if (row == 4)
    {
        return auditors->at(row)->getDateVisiting(0).getDateWithTime();
    }*/
    return to_string(row+1);
};
void ArrayAuditors::pushElement(int row, Auditor *a)
{
    this->pushRow(row, a);
}
ArrayAuditors::~ArrayAuditors(){}

void ArrayAuditors::add(Auditor *p)
{
    auditors->push_back(p);
}