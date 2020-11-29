#include "DisplayDepartment.hpp"
#include "../../Class/Auditor.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/Commercialist.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>

DisplayDepartment::DisplayDepartment(int x, int y, int w, int h, const char *l)
: Fl_Group(x,y,w,h,l)
{
    name = new Fl_Input(x, y, 100, 40, "Name:");
    headOfDepartment = new DisplayWorker(x, y+60, 100, 190, "Head of Department");
    
    chTypeOfHead = new Fl_Choice(x+90, y+250, 100, 50, "Type of HeadOD:");
    chTypeOfHead->add("Accountant|Auditor|Commercialist");
    chTypeOfHead->value(0);

    this->end();
}
void DisplayDepartment::displayHeadOfDepartment(AbstractWorker* worker)
{
    headOfDepartment->displayWorker(worker);
}

bool DisplayDepartment::isInputsEmpty() const
{
    string a = name->value();
    string b = headOfDepartment->getValueName();
    string c = headOfDepartment->getValueLastName();
    try
    {
        trim(a);
        trim(b);
        trim(c);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return false;
    }
    try{
        if(a.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Name of Department"));
        return false;
    }
    if(!headOfDepartment->isInputsEmpty())
    {
        return false;
    }
    return true;
}

AbstractWorker* DisplayDepartment::getNewHeadOfDepartment() const
{
    string type = this->getChTypeOfHead();
    try
    {
        if(type == "Accountant")
        {
            return new Accountant(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),headOfDepartment->getValueDateBirth(),
                    headOfDepartment->getValueSalary());
        }
        else if(type == "Auditor")
        {
            return new Auditor(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),headOfDepartment->getValueDateBirth(),
                    headOfDepartment->getValueSalary());
        }
        else if(type == "Commercialist")
        {
            return new Commercialist(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),headOfDepartment->getValueDateBirth(),
                    headOfDepartment->getValueSalary());
        }
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return nullptr;
    }
    return nullptr;
}

DisplayDepartment::~DisplayDepartment(){}

void DisplayDepartment::setName(string t)
{
    try
    {
        trim(t);
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    name->value(t.c_str());
}

string DisplayDepartment::getName() const
{
    string s = name->value();
    trim(s);
    return s;
}

void DisplayDepartment::hideGroup() {
    this->label("");
    this->name->hide();
    headOfDepartment->hide();
    
    this->chTypeOfHead->hide();
}
void DisplayDepartment::unhide() {
    this->name->show();
    headOfDepartment->unhide();
    this->chTypeOfHead->show();
}
string DisplayDepartment::getChTypeOfHead() const
{
    if(chTypeOfHead->value() == 0)
    {
        return "Accountant";
    }
    else if(chTypeOfHead->value() == 1)
    {
        return "Auditor";
    }
    else if(chTypeOfHead->value() == 2)
    {
        return "Commercialist";
    }
    return nullptr;
}