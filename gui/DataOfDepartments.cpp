#include "DataOfDepartments.hpp"
#include "MainWindow.hpp"

DataOfDepartments::DataOfDepartments(int x, int y, int w, int h, Company &company, void *data, const char *l) : Fl_Group(x,y,w,h,l),
    company(company)
{
    chDepartment = new Fl_Choice(x+150, y, 100, 40, "Departments:");
    string depart = "";
    for(int i = 0; i < company.getDepartmentsSize(); i++)
    {
        depart.append(company.getDepartments(i)->getName());
        depart.append("|");
    }
    
    chDepartment->add(depart.c_str());
    chDepartment->value(0);

    chWorkerType = new Fl_Choice(x+150, y+50, 100, 40, "Details of worker type:");
    chWorkerType->add("Accountant|Auditor|Commercialist");
    chWorkerType->value(0);

    btnDetails = new Fl_Button(x+270, y, 100, 50, "Details");
    btnAdd = new Fl_Button(x+270, y+60, 100, 50, "Add");
    btnRemove = new Fl_Button(x+270, y+110, 100, 50, "Remove");
    btnChange = new Fl_Button(x+270, y+160, 100, 50, "Change");
    btnGoBack = new Fl_Button(x+270, y+210, 100, 50, "Go back");

    btnDetails->callback(details, this);
    btnAdd->callback(add, this);
    btnRemove->callback(remove, this);
    btnChange->callback(change, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    MainWindow *main = (MainWindow*)data;
    v->push_back(main);
    v->push_back(this);

    btnGoBack->callback(goBack, v);

    this->end();
}
DataOfDepartments::~DataOfDepartments(){}

void DataOfDepartments::details(Fl_Widget *widget, void *data)
{

}
void DataOfDepartments::add(Fl_Widget *widget, void *data)
{
    
}
void DataOfDepartments::remove(Fl_Widget *widget, void *data)
{
    
}
void DataOfDepartments::change(Fl_Widget *widget, void *data)
{
    
}
void DataOfDepartments::goBack(Fl_Widget *widget, void *data)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)data;
    MainWindow *main = (MainWindow*)v->at(0);
    DataOfDepartments *dataA = (DataOfDepartments*)v->at(1);
    dataA->hide();
    main->unhide();
}