#include "DisplayDepartment.hpp"
#include "DataOfDepartments.hpp"
#include "DisplayAuditor.hpp"
#include "accountant/DisplayAccountant.hpp"
#include "../Util.hpp"

DisplayDepartment::DisplayDepartment(int x, int y, int w, int h, ArrayDepartments *departments, void* data, const char *l=0)
: Fl_Group(x,y,w,h,l), departments(departments)
{
    DataOfDepartments *d = (DataOfDepartments*)data;
    string type = departments->getDepartment(current)->getHeadOfDepartment()->getType();
    name = new Fl_Input(x, y, 100, 40, "Name:");
    if(type == "Accountant") //Accountant
    {
        headOfDepartment = new DisplayAccountant(x, y+60, 100, 190, new ArrayAccountants(departments->getDepartment(current)->getAccountants()), "Head of Department");
    }
    else if(type == "Auditor") //Auditor
    {
        headOfDepartment = new DisplayAuditor(x, y+60, 100, 190, new ArrayAuditors(departments->getDepartment(current)->getAuditors()),"Head of Department");
    }
    else if(type == "Commercialist") //Commercialist
    {
        //headOfDepartment = new DisplayCommercialist(x, y+60, 100, 190, "Head of Department");
    }
    
    chTypeOfHead = new Fl_Choice(x+90, y+250, 100, 50, "Type of HeadOD:");
    chTypeOfHead->add("Accountant|Auditor|Commercialist");
    chTypeOfHead->value(0);
    // chTypeOfHead->callback();
    btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");

    btnPrevious = new Fl_Button(x+120, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+170, y, 45, 70, "@->");

    vector<Fl_Widget*> *widgets = new vector<Fl_Widget*>();
    //widgets->push_back(headOfDepartment);
    widgets->push_back(name);
    widgets->push_back(this);
    widgets->push_back(d);

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);
    btnAdd->callback(add, widgets);

    if(departments->numberOfElement() != 0){
        this->setDisplay(current);
        this->checkButtons();
    }

    departments->subscribeListener(this);
    this->end();
}
AbstractWorker* DisplayDepartment::getHeadOfDepartment() const
{
    return departments->getElement(current)->getHeadOfDepartment();
}
DisplayDepartment::~DisplayDepartment(){}
void DisplayDepartment::updateLabel()
{
    stringstream sstream;
    sstream << "Department " << current + 1 << "/" << departments->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DisplayDepartment::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= departments->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

string DisplayDepartment::getName()
{
    return name->value();
}
void DisplayDepartment::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < departments->numberOfElement())
    {
        string type = departments->getDepartment(current)->getHeadOfDepartment()->getType();
        current = indeks;
        //this->displayWorker(departments->getDepartment(indeks)->getHeadOfDepartment());
        name->value(departments->getDepartment(indeks)->getName().c_str());
        if(type == "Accountant") //Accountant
        {
            headOfDepartment->displayWorker(departments->getDepartment(indeks)->getHeadOfDepartment());
        }
        else if(type == "Auditor") //Auditor
        {
            headOfDepartment->displayWorker(departments->getDepartment(indeks)->getHeadOfDepartment());
        }
        else if(type == "Commercialist") //Commercialist
        {
            
        }
    }
    updateLabel();
}

void DisplayDepartment::nextElement(Fl_Widget *widget, void *data){
    DisplayDepartment *displayDepartment = (DisplayDepartment *) data;
    if (displayDepartment->current + 1 < displayDepartment->departments->numberOfElement())
    {
        displayDepartment->current++;
        displayDepartment->setDisplay(displayDepartment->current);
    }

    displayDepartment->checkButtons();
}

void DisplayDepartment::previousElement(Fl_Widget *widget, void *data)
{
    DisplayDepartment *displayDepartment = (DisplayDepartment *) data;
    if (displayDepartment->current - 1 >= 0)
    {
        displayDepartment->current--;
        displayDepartment->setDisplay(displayDepartment->current);
    }

    displayDepartment->checkButtons();
}

void DisplayDepartment::elementPushed(int indeks, Department *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DisplayDepartment::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DisplayDepartment::getCurrent()
{
    return current;
}
void DisplayDepartment::hideGroup() {
    this->label("");
    this->name->hide();
    headOfDepartment->hide();
    
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
    this->chTypeOfHead->hide();
}
void DisplayDepartment::unhide() {
    this->name->show();
    headOfDepartment->unhide();
    this->btnNext->show();
    this->btnPrevious->show();
    this->btnAdd->show();
    this->chTypeOfHead->show();
    if(this->departments->numberOfElement() != 0){
        this->setDisplay(current);
        this->checkButtons();
    }
}
/*void DisplayDepartment::DisplayDepartment(Auditor *auditor)
{
    cout << "DisplayDepartment ovde" <<endl;
    //this->auditor = auditor;
    cout << "DisplayDepartment ovde1" <<endl;
    headOfDepartment->headOfDepartment(auditor);
    cout << "DisplayDepartment ovde2" <<endl;
    datesVisiting->value("");
    for(int i = 0; i < auditor->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }
    cout << "DisplayDepartment ovde3" <<endl;
}*/

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
/*struct Event
{
    ArrayDepartments *departments;
    AuditorTable *tabela;
    DisplayDepartment *DisplayDepartment;
};*/
void DisplayDepartment::add(Fl_Widget *widget, void *data)
{
    vector<Fl_Widget*> *widgets = (vector<Fl_Widget*>*)data;
    DisplayWorker *headOfDepartment = (DisplayWorker*)widgets->at(0);
    DisplayDepartment *displayDepartment = (DisplayDepartment*)widgets->at(1);
    string *name = (string*)widgets->at(2);
    DataOfDepartments *d = (DataOfDepartments*)widgets->at(3);
    DepartmentTable *departmentTable = d->getDepartmentTable();
    // AbstractWorker *worker =

    //  Department *department = new Department(displayDepartment->getValueName(), displayDepartment->getValueLastName(),
    //                 displayDepartment->getValueDateBirth(), stod(displayDepartment->getValueSalary()), displayDepartment->getDatesVisiting());
                    
    // departmentTable->add(department);
}