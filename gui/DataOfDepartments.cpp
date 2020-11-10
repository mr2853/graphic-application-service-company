#include "DataOfDepartments.hpp"
#include "../Class/Department.hpp"
#include "MainWindow.hpp"
#include "DataOfAuditors.hpp"
#include "ArrayDepartments.hpp"

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
    
    displayDepartment = new DisplayDepartment(x+50, y, 300, 390, departments, this, "");
    departmentTable = new DepartmentTable(x, y+340, 400, 280, departments);

    chDepartment = new Fl_Choice(x+450, y, 100, 40, "Departments:");
    string depart = "";
    for(int i = 0; i < company.getDepartmentsSize(); i++)
    {
        depart.append(company.getDepartment(i)->getName());
        depart.append("|");
    }
    
    chDepartment->add(depart.c_str());
    chDepartment->value(0);

    chWorkerType = new Fl_Choice(x+450, y+50, 100, 40, "Worker type:");
    chWorkerType->add("Accountant|Auditor|Commercialist");
    chWorkerType->value(0);
    btnDetails = new Fl_Button(x+450, y+100, 150, 50, "Data of worker type");
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnRemove = new Fl_Button(x+370, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");

    //btnView->callback(DataOfDepartments::view, ev);
    btnRemove->callback(DataOfDepartments::remove, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    MainWindow *main = (MainWindow*)mainWindow;
    v->push_back(main);
    v->push_back(this);

    btnGoBack->callback(DataOfDepartments::goBack, v);
    btnDetails->callback(details, v);

    btnChange->callback(change, v);

    this->end();
}

void DataOfDepartments::change(Fl_Widget *widget, void *data)
{

}

void DataOfDepartments::hideGroup(){
    this->label("");
    this->displayDepartment->hideGroup();
    this->departmentTable->hide();

    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnDetails->hide();
    this->btnChange->hide();

    this->chDepartment->hide();
    this->chWorkerType->hide();
    this->hide();
}
void DataOfDepartments::unhide(){
    this->displayDepartment->unhide();
    this->departmentTable->show();
    this->btnRemove->show();
    this->btnGoBack->show();
    this->btnDetails->show();
    this->btnChange->show();
    this->chDepartment->show();
    this->chWorkerType->show();
    this->show();
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

    }
    else if(workerType == 1){
        data->hideGroup();
        DataOfAuditors *dataOfAuditors = new DataOfAuditors(data->x(),
                        data->y(), data->w(), data->h(), new ArrayAuditors(department->getAuditors()), data);
        mainWindow->add(dataOfAuditors);
    }
    else if(workerType == 2){
        
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

/*void DataOfDepartments::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayAuditor->displayAuditor(event->departments->getElement(endRow));
}*/
DataOfDepartments::~DataOfDepartments(){}

void DataOfDepartments::remove(Fl_Widget *widget, void *data)
{
    DataOfDepartments *e = (DataOfDepartments *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->departmentTable->get_selection(startRow, colLeft, endRow, colRight);
    // cout << "Dodje" << endl;
    // cout << "size1:" << e->departments->numberOfElement() << endl;
    for (int i = endRow; i >= startRow; i--)
    {
        e->departments->removeRow(i);
        // e->auditorTable->rows(e->departments->numberOfRows());
        // e->auditorTable->cols(e->departments->numberOfColumns());
    }
    // cout << "prodje" << endl;
}

Company& DataOfDepartments::getCompany()
{
    return company;
}
void DataOfDepartments::refreshTable()
{
    departmentTable->refreshTable();
}

// #include "DataOfDepartments.hpp"
// #include "MainWindow.hpp"

// DataOfDepartments::DataOfDepartments(int x, int y, int w, int h, Company &company, void *data, const char *l) : Fl_Group(x,y,w,h,l),
//     company(company)
// {
    // chDepartment = new Fl_Choice(x+150, y, 100, 40, "Departments:");
    // string depart = "";
    // for(int i = 0; i < company.getDepartmentsSize(); i++)
    // {
    //     depart.append(company.getDepartments(i)->getName());
    //     depart.append("|");
    // }
    
    // chDepartment->add(depart.c_str());
    // chDepartment->value(0);

    // chWorkerType = new Fl_Choice(x+150, y+50, 100, 40, "Worker type:");
    // chWorkerType->add("Accountant|Department|Commercialist");
    // chWorkerType->value(0);

    // btnDetails = new Fl_Button(x+270, y, 150, 50, "Data of worker type");
    // btnAdd = new Fl_Button(x+270, y+60, 100, 50, "Add");
    // btnRemove = new Fl_Button(x+270, y+110, 100, 50, "Remove");
    // btnChange = new Fl_Button(x+270, y+160, 150, 50, "Change Department data");
    // btnGoBack = new Fl_Button(x+270, y+210, 100, 50, "Go back");

    // btnDetails->callback(details, this);
    // btnAdd->callback(add, this);
    // btnRemove->callback(remove, this);
    // btnChange->callback(change, this);

//     vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
//     MainWindow *main = (MainWindow*)data;
//     v->push_back(main);
//     v->push_back(this);

//     btnGoBack->callback(goBack, v);

//     this->end();
// }
// DataOfDepartments::~DataOfDepartments(){}

// void DataOfDepartments::details(Fl_Widget *widget, void *data)
// {

// }
// void DataOfDepartments::add(Fl_Widget *widget, void *data)
// {
    
// }
// void DataOfDepartments::remove(Fl_Widget *widget, void *d)
// {
//     DataOfDepartments *data = (DataOfDepartments*)d;
//     data->company.removeDepartment(data->chDepartment->value());
// }
// void DataOfDepartments::change(Fl_Widget *widget, void *data)
// {
    
// }
// void DataOfDepartments::goBack(Fl_Widget *widget, void *data)
// {
//     vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)data;
//     MainWindow *main = (MainWindow*)v->at(0);
//     DataOfDepartments *dataA = (DataOfDepartments*)v->at(1);
//     dataA->hide();
//     main->unhide();
// }