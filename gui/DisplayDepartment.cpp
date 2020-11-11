#include "DisplayDepartment.hpp"
#include "DataOfDepartments.hpp"
#include "../Util.hpp"

DisplayDepartment::DisplayDepartment(int x, int y, int w, int h, ArrayDepartments *departments, void* data, const char *l=0)
: Fl_Group(x, y, w, h, l), departments(departments)
{
    DataOfDepartments *d = (DataOfDepartments*)data;
    name = new Fl_Input(x, y, 100, 40, "Name:");
    headOfDepartment = new DisplayWorker(x, y+60, 100, 190, "Head of Department");
    btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");

    btnPrevious = new Fl_Button(x+120, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+170, y, 45, 70, "@->");

    vector<Fl_Widget*> *widgets = new vector<Fl_Widget*>();
    widgets->push_back(headOfDepartment);
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

void DisplayDepartment::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < departments->numberOfElement())
    {
        current = indeks;
        headOfDepartment->displayWorker(departments->getDepartment(indeks)->getHeadOfDepartment());
        name->value(departments->getDepartment(indeks)->getName().c_str());
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
    this->headOfDepartment->hide();
    
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
}
void DisplayDepartment::unhide() {
    this->name->show();
    this->headOfDepartment->unhide();
    this->btnNext->show();
    this->btnPrevious->show();
    this->btnAdd->show();
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

    // Auditor *novaOsoba = new Auditor(headOfDepartment->getValueName(), headOfDepartment->getValueLastName(),
    //                 headOfDepartment->getValueDateBirth(), stod(headOfDepartment->getValueSalary()));
                    
    //DisplayDepartment->departments->add(novaOsoba);
    // auditorTable->add(novaOsoba);
    // cout << "numb of elem: " << d->numberOfAuditors() << endl;
    // d->addAuditor(novaOsoba);
    // cout << "numb of elem1: " << d->numberOfAuditors() << endl;
}