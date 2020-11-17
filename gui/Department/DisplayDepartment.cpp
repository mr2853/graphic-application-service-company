#include "DisplayDepartment.hpp"
#include "../../Class/Auditor.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/Commercialist.hpp"
#include "../../Util.hpp"

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
AbstractWorker* DisplayDepartment::getNewHeadOfDepartment()
{
    string type = this->getChTypeOfHead();
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
    return nullptr;
}

DisplayDepartment::~DisplayDepartment(){}

void DisplayDepartment::setName(string t)
{
    name->value(t.c_str());
}

string DisplayDepartment::getName()
{
    string s = name->value();
    ltrim(s);
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
string DisplayDepartment::getChTypeOfHead()
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