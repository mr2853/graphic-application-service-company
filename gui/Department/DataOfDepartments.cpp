#include "DataOfDepartments.hpp"
#include "../../Class/Department.hpp"
#include "DisplayDepartment.hpp"

#include "../Company/DataOfCompanies.hpp"

#include "../Auditor/DataOfAuditors.hpp"
#include "../Accountant/DataOfAccountants.hpp"
#include "../Commercialist/DataOfCommercialists.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>

using namespace std;

DataOfDepartments::DataOfDepartments(int x, int y, int w, int h, Array<Department*> *original, Array<Department*> *changed, void *mainWindow, const char *l)
 : DataOf(x , y ,w ,h , original, changed, mainWindow, l){
    
    displayDepartment = new DisplayDepartment(x+50, y, 200, 300, "");
    
    chDepartment = new Fl_Choice(x+450, y, 100, 40, "Departments:");
    this->updateChDepart();
    chWorkerType = new Fl_Choice(x+450, y+50, 100, 40, "Worker type:");
    chWorkerType->add("Accountant|Auditor|Commercialist");
    chWorkerType->value(0);
    btnDetails = new Fl_Button(x+450, y+100, 150, 50, "Data of worker type");

    vector<void*> *v = new vector<void*>();
    v->push_back(mainWindow);
    v->push_back(this);
    btnDetails->callback(details, v);
    btnGoBack->callback(DataOfDepartments::goBack,v);

    btnChange->callback(change, this);
    btnAdd->callback(DataOfDepartments::add, this);
    btnRemove->callback(DataOfDepartments::removeElem, this);
    
    if(changed->numberOfElement() != 0){
        this->setDisplay(this->getCurrent());
    }
    
    this->isDepartmentsEmpty();
    this->checkButtons();
    this->end();
}
int DataOfDepartments::getChDepartmentValue() const
{
    return chDepartment->value();
}
void DataOfDepartments::removeElem(Fl_Widget *widget, void *d)
{
    DataOf<Department*>::removeElem(widget, d);
    DataOfDepartments *data = (DataOfDepartments*)d;
    data->updateChDepart();
}
void DataOfDepartments::goBack(Fl_Widget *widget, void *d)
{
    vector<void*> *v = (vector<void*>*)d;
    DataOfCompanies *parent = (DataOfCompanies*)v->at(0);
    DataOfDepartments *data = (DataOfDepartments*)v->at(1);
    
    data->hideGroup();
    data->hide();
    parent->remove(data);
    parent->unhideGroup();
}

void DataOfDepartments::updateChDepart(){
    string depart = "";
    chDepartment->clear();
    for(int i = 0; i < this->sizeOfArray(); i++)
    {
        string s = to_string(i+1).append(".").append(this->getElement(i)->getName());
        depart.append(s);
        depart.append("|");
    }
    chDepartment->add(depart.c_str());
    chDepartment->redraw();
    chDepartment->value(0);
}
void DataOfDepartments::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        string type = this->getElement(current)->getHeadOfDepartment()->getType();
        displayDepartment->setName(this->getElement(indeks)->getName().c_str());
        
        if(type == "Accountant")
        {
            displayDepartment->displayHeadOfDepartment(this->getElement(indeks)->getHeadOfDepartment());
        }
        else if(type == "Auditor")
        {
            displayDepartment->displayHeadOfDepartment(this->getElement(indeks)->getHeadOfDepartment());
        }
        else if(type == "Commercialist")
        {
            displayDepartment->displayHeadOfDepartment(this->getElement(indeks)->getHeadOfDepartment());
        }
    }
    updateLabel();
}

void DataOfDepartments::isDepartmentsEmpty()
{
    this->isArrayEmpty();
    if(this->sizeOfArray() == 0){
        btnChange->deactivate();
        btnDetails->deactivate();
    }
    else
    {
        btnChange->activate();
        btnDetails->activate();
    }
}
void DataOfDepartments::change(Fl_Widget *widget, void *d)
{
    DataOfDepartments *data = (DataOfDepartments*)d;
    if(!data->displayDepartment->isInputsEmpty())
    {
        return;
    }
    int current = data->getCurrent();
    Department *dep = data->changed->getRow(current);
    dep->setName(data->displayDepartment->getName());
    string type = data->changed->getElement(current)->getHeadOfDepartment()->getType();
    AbstractWorker* head;
    try{
        head = data->displayDepartment->getNewHeadOfDepartment();
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    if(type == "Accountant")
    {
        dep->setHeadOfDepartment(new Accountant(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
    }
    else if(type == "Auditor")
    {
        dep->setHeadOfDepartment(new Auditor(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
    }
    else if(type == "Commercialist")
    {
        dep->setHeadOfDepartment(new Commercialist(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
    }

    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == current)
            {
                Department *dep1 = data->original->getElement(i);
                dep1->setName(data->displayDepartment->getName());

                if(type == "Accountant")
                {
                    dep1->setHeadOfDepartment(new Accountant(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
                }
                else if(type == "Auditor")
                {
                    dep1->setHeadOfDepartment(new Auditor(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
                }
                else if(type == "Commercialist")
                {
                    dep1->setHeadOfDepartment(new Commercialist(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
                }
                break;
            }
            counter++;
        }
    }
    data->table->redraw();
    data->updateChDepart();
}

void DataOfDepartments::hideGroup(){
    DataOf<Department*>::hideGroup();
    this->label("");
    this->displayDepartment->hideGroup();

    this->btnDetails->hide();
    this->btnChange->hide();
    this->btnAdd->hide();

    this->chDepartment->hide();
    this->chWorkerType->hide();
}
void DataOfDepartments::unhideGroup(){
    DataOf<Department*>::unhideGroup();
    this->redraw_label();
    this->updateLabel();
    this->displayDepartment->unhide();

    this->btnDetails->show();
    this->btnChange->show();
    this->btnAdd->show();
    
    this->chDepartment->show();
    this->chWorkerType->show();
}
void DataOfDepartments::details(Fl_Widget *widget, void *d)
{
    vector<void*> *v = (vector<void*>*)d;
    DataOfCompanies *mainWindow = (DataOfCompanies*)v->at(0);
    DataOfDepartments *data = (DataOfDepartments*)v->at(1);
    int intDep = data->chDepartment->value();
    int workerType = data->chWorkerType->value();
    Department *department1;
    int counter = 0;
    for(int j = 0; j < data->original->numberOfElement(); j++)
    {
        if(!data->original->getElement(j)->isDeleted())
        {
            if(counter == intDep)
            {
                department1 = data->original->getElement(j);
            }
            counter++;
        }
    }
    Department *department2 = data->changed->getElement(intDep);
    Company* company = mainWindow->getElement(mainWindow->getCurrent());

    if(workerType == 0){
        DataOfAccountants *dataOfAccountants = new DataOfAccountants(data->x(),
                        data->y(), data->w(), data->h(), new Array<Accountant*>(department1->getAccountants()),
                         new Array<Accountant*>(department2->getAccountants()), company, data);
        data->hideGroup();
        mainWindow->Fl_Group::add(dataOfAccountants);
    }
    else if(workerType == 1){
        DataOfAuditors *dataOfAuditors = new DataOfAuditors(data->x(),
                        data->y(), data->w(), data->h(), new Array<Auditor*>(department1->getAuditors()),
                         new Array<Auditor*>(department2->getAuditors()), company, data);
        data->hideGroup();
        mainWindow->Fl_Group::add(dataOfAuditors);
    }
    else if(workerType == 2){
        DataOfCommercialists *dataOfCommercialists = new DataOfCommercialists(data->x(),
                        data->y(), data->w(), data->h(), new Array<Commercialist*>(department1->getCommercialists()),
                         new Array<Commercialist*>(department2->getCommercialists()), company, data);
        data->hideGroup();
        mainWindow->Fl_Group::add(dataOfCommercialists);
    }
}

DataOfDepartments::~DataOfDepartments(){}

void DataOfDepartments::add(Fl_Widget *widget, void *data)
{
    DataOfDepartments *d = (DataOfDepartments*)data;
    if(!d->displayDepartment->isInputsEmpty())
    {
        return;
    }
    AbstractWorker* worker;
    AbstractWorker* worker1;
    try{
        worker = d->displayDepartment->getNewHeadOfDepartment();
        worker1 = d->displayDepartment->getNewHeadOfDepartment();
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    d->table->add(new Department(worker, d->displayDepartment->getName()));
    d->original->add(new Department(worker1, d->displayDepartment->getName()));
    d->updateChDepart();
    d->setDisplay(d->changed->numberOfElement()-1);
    d->updateLabel();
    d->isDepartmentsEmpty();
    d->checkButtons();
}