#include "DisplayDepartment.hpp"
#include "../../Class/Auditor.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/Commercialist.hpp"

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
                stod(headOfDepartment->getValueSalary()));
    }
    else if(type == "Auditor")
    {
        return new Auditor(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),headOfDepartment->getValueDateBirth(),
                stod(headOfDepartment->getValueSalary()));
    }
    else if(type == "Commercialist")
    {
        return new Commercialist(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),headOfDepartment->getValueDateBirth(),
                stod(headOfDepartment->getValueSalary()));
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
    return name->value();
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
// void DisplayDepartment::DisplayDepartment(Auditor *auditor)
// {
//     cout << "DisplayDepartment ovde" <<endl;
//     //this->auditor = auditor;
//     cout << "DisplayDepartment ovde1" <<endl;
//     headOfDepartment->headOfDepartment(auditor);
//     cout << "DisplayDepartment ovde2" <<endl;
//     datesVisiting->value("");
//     for(int i = 0; i < auditor->getNumberOfVisits(); i++)
//     {
//         datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
//     }
//     cout << "DisplayDepartment ovde3" <<endl;
// }

// vector<Date*>* DisplayDepartment::getDatesVisiting(){
//     string t = datesVisiting->value();
//     vector<Date*> *dates = new vector<Date*>();
//     int index;

//     while(t.find(",")){
//         index = t.find(",");
//         string subs = t.substr(0, index);
//         vector<int> d = getDate(subs);
//         t.erase(0, index + 1);
//         dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
//     }

//     vector<int> d = getDate(t);
//     t.erase(0, index + 1);
//     dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
    
//     return dates;
// }