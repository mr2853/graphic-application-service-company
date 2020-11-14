#include "ArrayAccountants.hpp"

ArrayAccountants::ArrayAccountants() : AbstractTableModel<Accountant*>()
{
    accountants = new vector<Accountant*>();
}
ArrayAccountants::ArrayAccountants(vector<Accountant*> *accountants) : AbstractTableModel<Accountant*>(), accountants(accountants)
{
}
int ArrayAccountants::numberOfRows()
{
    return accountants->size();
}

int ArrayAccountants::numberOfColumns()
{
    return 4;
}
Accountant *ArrayAccountants::getRow(int indeks)
{
    return accountants->at(indeks);
}

/*string ArrayAccountants::verticalHeader(int red)
{  
    stringstream sstream;
    sstream << red+1;
    return sstream.str();
}*/

void ArrayAccountants::pushRow(int row, Accountant* elem){
    accountants->insert(accountants->begin() + row, elem);
    AbstractTableModel<Accountant *>::pushRow(row, elem);
};

void ArrayAccountants::removeRow(int index)
{
    // cout << "line38" << endl;
    // cout << "size:" << accountants->size() << endl;
    accountants->erase(accountants->begin() + index);
    // cout << "line40" << endl;
    AbstractTableModel::removeRow(index);
}

void ArrayAccountants::write(ostream &output)
{
    output << accountants->size() << endl;
    for (int i = 0; i < accountants->size(); i++)
    {
        output << accountants->at(i) << endl;
    }
}
void ArrayAccountants::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        Accountant *novaOsoba;
        input >> tip;
        if (tip == "Accountant")
        {
            novaOsoba = new Accountant();
        }
        //input >> novaOsoba;
        pushElement(accountants->size(), novaOsoba);
    }
}

string ArrayAccountants::getText(int row, int column)
{
    Accountant *o = accountants->at(row);
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
    return "";
}
string ArrayAccountants::verticalHeader(int row){  
    /*if (row == 0)
    {
        return accountants->at(row)->getName();
    }
    else if (row == 1)
    {
        return accountants->at(row)->getLastname();
    }
    else if (row == 2)
    {
        return accountants->at(row)->getDateBirth().getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(accountants->at(row)->getSalary());
    }
    else if (row == 4)
    {
        return accountants->at(row)->getDateVisiting(0).getDateWithTime();
    }*/
    return to_string(row+1);
};
void ArrayAccountants::pushElement(int row, Accountant *a)
{
    this->pushRow(row, a);
}
ArrayAccountants::~ArrayAccountants(){}

void ArrayAccountants::add(Accountant *p)
{
    accountants->push_back(p);
}
Accountant* ArrayAccountants::getAccountant(int in)
{
    return accountants->at(in);
}