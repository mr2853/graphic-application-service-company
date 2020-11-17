#include "DisplayCompany.hpp"
#include "../../Class/Auditor.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/Commercialist.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>

DisplayCompany::DisplayCompany(int x, int y, int w, int h, const char *l)
: Fl_Group(x,y,w,h,l)
{
    name = new Fl_Input(x, y, 100, 40, "Name:");
    taxIdentificationNumber = new Fl_Input(x, y+50, 100, 40, "Tax ID:");
    identificationNumber = new Fl_Input(x, y+100, 100, 40, "ID:");

    this->end();
}

DisplayCompany::~DisplayCompany(){}

void DisplayCompany::isInputsEmpty()
{
    string a = name->value();
    string b = taxIdentificationNumber->value();
    string c = identificationNumber->value();
    try{
        if(a.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Name"));
        return;
    }
    try{
        if(b.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Tax ID"));
        return;
    }
    try{
        if(c.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("ID"));
        return;
    }
}
void DisplayCompany::setName(string t)
{
    name->value(t.c_str());
}

string DisplayCompany::getName()
{
    string s = name->value();
    ltrim(s);
    return s;
}

string DisplayCompany::getTaxIdentificationNumber()
{
    string s = taxIdentificationNumber->value();
    ltrim(s);
    return s;
}
void DisplayCompany::setTaxIdentificationNumber(string t)
{
     taxIdentificationNumber->value(t.c_str());
}
string DisplayCompany::getIdentificationNumber()
{
    string s = identificationNumber->value();
    ltrim(s);
    return s;
}
void DisplayCompany::setIdentificationNumber(string t)
{
     identificationNumber->value(t.c_str());
}

void DisplayCompany::hideGroup() {
    this->label("");
    this->name->hide();
    this->taxIdentificationNumber->hide();
    this->identificationNumber->hide();
}
void DisplayCompany::unhide() {
    this->name->show();
    this->taxIdentificationNumber->show();
    this->identificationNumber->show();
}