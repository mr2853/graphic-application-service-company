#include "ArrayCommercialists.hpp"

ArrayCommercialists::ArrayCommercialists() : AbstractTableModel<Commercialist*>()
{
    commercialists = new vector<Commercialist*>();
}
ArrayCommercialists::ArrayCommercialists(vector<Commercialist*> *commercialists) : AbstractTableModel<Commercialist*>(), commercialists(commercialists)
{
}
int ArrayCommercialists::numberOfRows()
{
    return commercialists->size();
}

int ArrayCommercialists::numberOfColumns()
{
    return 4;
}
Commercialist *ArrayCommercialists::getRow(int indeks)
{
    return commercialists->at(indeks);
}

/*string ArrayCommercialists::verticalHeader(int red)
{  
    stringstream sstream;
    sstream << red+1;
    return sstream.str();
}*/

void ArrayCommercialists::pushRow(int row, Commercialist* elem){
    commercialists->insert(commercialists->begin() + row, elem);
    AbstractTableModel<Commercialist *>::pushRow(row, elem);
};

void ArrayCommercialists::removeRow(int index)
{
    // cout << "line38" << endl;
    // cout << "size:" << commercialists->size() << endl;
    commercialists->erase(commercialists->begin() + index);
    // cout << "line40" << endl;
    AbstractTableModel::removeRow(index);
}

void ArrayCommercialists::write(ostream &output)
{
    output << commercialists->size() << endl;
    for (int i = 0; i < commercialists->size(); i++)
    {
        output << commercialists->at(i) << endl;
    }
}
void ArrayCommercialists::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        Commercialist *novaOsoba;
        input >> tip;
        if (tip == "Commercialist")
        {
            novaOsoba = new Commercialist();
        }
        //input >> novaOsoba;
        pushElement(commercialists->size(), novaOsoba);
    }
}

string ArrayCommercialists::getText(int row, int column)
{
    Commercialist *o = commercialists->at(row);
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
string ArrayCommercialists::horizontalHeader(int column)
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
string ArrayCommercialists::verticalHeader(int row){  
    /*if (row == 0)
    {
        return commercialists->at(row)->getName();
    }
    else if (row == 1)
    {
        return commercialists->at(row)->getLastname();
    }
    else if (row == 2)
    {
        return commercialists->at(row)->getDateBirth().getDateWithTime();
    }
    else if (row == 3)
    {
        return to_string(commercialists->at(row)->getSalary());
    }
    else if (row == 4)
    {
        return commercialists->at(row)->getDateVisiting(0).getDateWithTime();
    }*/
    return to_string(row+1);
};
void ArrayCommercialists::pushElement(int row, Commercialist *a)
{
    this->pushRow(row, a);
}
ArrayCommercialists::~ArrayCommercialists(){}

void ArrayCommercialists::add(Commercialist *p)
{
    commercialists->push_back(p);
}
Commercialist* ArrayCommercialists::getCommercialist(int in)
{
    return commercialists->at(in);
}