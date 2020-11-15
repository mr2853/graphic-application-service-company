#include "DataOfDepartments.hpp"
#include "../../Class/Department.hpp"
#include "ArrayDepartments.hpp"
#include "DisplayDepartment.hpp"

#include "../MainWindow.hpp"

#include "../Auditor/DataOfAuditors.hpp"
#include "../Accountant/DataOfAccountants.hpp"
#include "../Commercialist/DataOfCommercialists.hpp"

using namespace std;

DepartmentTable* DataOfDepartments::getDepartmentTable()
{
    return departmentTable;
}
void DataOfDepartments::addDepartment(Department* a)
{
    departments->add(a);
}
int DataOfDepartments::numberOfDepartments()
{
    return departments->numberOfElement();
}

DataOfDepartments::DataOfDepartments(int x, int y, int w, int h, Company &company, void *mainWindow, const char *l) : Fl_Group(x , y ,w ,h ,l), company(company){

    this->departments = new ArrayDepartments(company.getDepartments());
    
    displayDepartment = new DisplayDepartment(x+50, y, 200, 300, "");
    departmentTable = new DepartmentTable(x+190, y+340, 400, 280, departments);

    chDepartment = new Fl_Choice(x+450, y, 100, 40, "Departments:");
    this->updateChDepart();
    chWorkerType = new Fl_Choice(x+450, y+50, 100, 40, "Worker type:");
    chWorkerType->add("Accountant|Auditor|Commercialist");
    chWorkerType->value(0);
    btnDetails = new Fl_Button(x+450, y+100, 150, 50, "Data of worker type");
    
    btnRemove = new Fl_Button(x+190, y+300, 70, 30, "Remove");
    btnChange = new Fl_Button(x+270, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+350, y+300, 70, 30, "Add");
    btnGoBack = new Fl_Button(x+430, y+300, 70, 30, "Go back");

    btnPrevious = new Fl_Button(x+170, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+220, y, 45, 70, "@->");

    //btnView->callback(DataOfDepartments::view, ev);
    btnRemove->callback(DataOfDepartments::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    MainWindow *main = (MainWindow*)mainWindow;
    v->push_back(main);
    v->push_back(this);

    btnGoBack->callback(DataOfDepartments::goBack, v);
    btnDetails->callback(details, v);

    btnChange->callback(change, this);

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);
    btnAdd->callback(add, this);

    if(departments->numberOfElement() != 0){
        this->setDisplay(current);
        this->checkButtons();
    }

    departments->subscribeListener(this);

    this->end();
}
void DataOfDepartments::updateChDepart(){
    string depart = "";
    chDepartment->clear();
    for(int i = 0; i < company.getDepartmentsSize(); i++)
    {
        depart.append(company.getDepartment(i)->getName());
        depart.append("|");
    }
    chDepartment->add(depart.c_str());
    chDepartment->redraw();
    chDepartment->value(0);
}
void DataOfDepartments::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < departments->numberOfElement())
    {
        current = indeks;
        string type = departments->getDepartment(current)->getHeadOfDepartment()->getType();
        //this->displayWorker(departments->getDepartment(indeks)->getHeadOfDepartment());
        displayDepartment->setName(departments->getDepartment(indeks)->getName().c_str());
        if(type == "Accountant") //Accountant
        {
            displayDepartment->displayHeadOfDepartment(departments->getDepartment(indeks)->getHeadOfDepartment());
        }
        else if(type == "Auditor") //Auditor
        {
            displayDepartment->displayHeadOfDepartment(departments->getDepartment(indeks)->getHeadOfDepartment());
        }
        else if(type == "Commercialist") //Commercialist
        {
            displayDepartment->displayHeadOfDepartment(departments->getDepartment(indeks)->getHeadOfDepartment());
        }
    }
    updateLabel();
}

void DataOfDepartments::nextElement(Fl_Widget *widget, void *d){
    DataOfDepartments *data = (DataOfDepartments *) d;
    if (data->current + 1 < data->departments->numberOfElement())
    {
        data->current++;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfDepartments::previousElement(Fl_Widget *widget, void *d)
{
    DataOfDepartments *data = (DataOfDepartments *) d;
    if (data->current - 1 >= 0)
    {
        data->current--;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfDepartments::elementPushed(int indeks, Department *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DataOfDepartments::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DataOfDepartments::getCurrent()
{
    return current;
}
void DataOfDepartments::updateLabel()
{
    stringstream sstream;
    sstream << "Department " << current + 1 << "/" << departments->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DataOfDepartments::checkButtons()
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
void DataOfDepartments::change(Fl_Widget *widget, void *d)
{
    DataOfDepartments *data = (DataOfDepartments*)d;
    Department *dep = data->departments->getRow(data->getCurrent());
    dep->setName(data->displayDepartment->getName());
    string type = data->departments->getDepartment(data->getCurrent())->getHeadOfDepartment()->getType();
    AbstractWorker* head = data->displayDepartment->getNewHeadOfDepartment();
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
    data->departmentTable->redraw();
    data->updateChDepart();
}

void DataOfDepartments::hideGroup(){
    this->label("");
    this->displayDepartment->hideGroup();
    this->departmentTable->hide();

    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnDetails->hide();
    this->btnChange->hide();
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();

    this->chDepartment->hide();
    this->chWorkerType->hide();
}
void DataOfDepartments::unhide(){
    this->redraw_label();
    this->updateLabel();
    this->displayDepartment->unhide();
    this->departmentTable->show();

    this->btnRemove->show();
    this->btnGoBack->show();
    this->btnDetails->show();
    this->btnChange->show();
    this->btnNext->show();
    this->btnPrevious->show();
    this->btnAdd->show();
    
    this->chDepartment->show();
    this->chWorkerType->show();
}
void DataOfDepartments::details(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    MainWindow *mainWindow = (MainWindow*)v->at(0);
    DataOfDepartments *data = (DataOfDepartments*)v->at(1);
    int intDep = data->chDepartment->value();
    int workerType = data->chWorkerType->value();
    Department *department = data->company.getDepartment(intDep);
    if(workerType == 0){
        DataOfAccountants *dataOfAccountants = new DataOfAccountants(data->x(),
                        data->y(), data->w(), data->h(), new ArrayAccountants(department->getAccountants()), v);
        data->hideGroup();
        mainWindow->add(dataOfAccountants);
    }
    else if(workerType == 1){
        DataOfAuditors *dataOfAuditors = new DataOfAuditors(data->x(),
                        data->y(), data->w(), data->h(), new ArrayAuditors(department->getAuditors()), v);
        data->hideGroup();
        mainWindow->add(dataOfAuditors);
    }
    else if(workerType == 2){
        DataOfCommercialists *dataOfCommercialists = new DataOfCommercialists(data->x(),
                        data->y(), data->w(), data->h(), new ArrayCommercialists(department->getCommercialists()), v);
        data->hideGroup();
        mainWindow->add(dataOfCommercialists);
    }
}
void DataOfDepartments::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)v->at(0);
    DataOfDepartments *data = (DataOfDepartments*)v->at(1);
    data->hideGroup();
    main->unhide();
}
DataOfDepartments::~DataOfDepartments(){}

void DataOfDepartments::removeElem(Fl_Widget *widget, void *data)
{
    DataOfDepartments *e = (DataOfDepartments *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->departmentTable->get_selection(startRow, colLeft, endRow, colRight);
    for (int i = endRow; i >= startRow; i--)
    {
        e->departments->removeRow(i);
    }
    if(e->departments->numberOfElement() == 0){
        e->setDisplay(0);
    }
    else{
        e->setDisplay(e->departments->numberOfElement()-1);
    }
    e->updateChDepart();
    e->checkButtons();
    e->updateLabel();
}

Company& DataOfDepartments::getCompany()
{
    return company;
}
void DataOfDepartments::refreshTable()
{
    departmentTable->refreshTable();
}

void DataOfDepartments::add(Fl_Widget *widget, void *data)
{
    DataOfDepartments *d = (DataOfDepartments*)data;
    AbstractWorker *worker = d->displayDepartment->getNewHeadOfDepartment();
    Department *department = new Department(worker, d->displayDepartment->getName());
    d->departmentTable->add(department);
    d->updateChDepart();
    d->setDisplay(d->departments->numberOfElement()-1);
    d->checkButtons();
    d->updateLabel();
}