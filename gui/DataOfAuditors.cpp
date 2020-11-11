#include "DataOfAuditors.hpp"
#include "../Class/Auditor.hpp"
#include "DataOfDepartments.hpp"
#include "MainWindow.hpp"
#include <sstream>

using namespace std;

/*struct Event
{
    ArrayAuditors *auditors;
    AuditorTable *tabela;
    DisplayAuditor *displayAuditor;
};*/
AuditorTable* DataOfAuditors::getAuditorTable()
{
    return auditorTable;
}
void DataOfAuditors::addAuditor(Auditor* a)
{
    auditors->add(a);
}
int DataOfAuditors::numberOfAuditors()
{
    return auditors->numberOfElement();
}

DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, ArrayAuditors *auditors, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), auditors(auditors)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, auditors, this, "");
    auditorTable = new AuditorTable(x+50, y+340, 400, 280, auditors);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnRemove = new Fl_Button(x+370, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");

    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfAuditors::goBack, v);
    
    vector<Fl_Widget*> *v1 = new vector<Fl_Widget*>(0);
    v1->push_back(this);
    v1->push_back(displayAuditor);
    v1->push_back(auditorTable);
    btnChange->callback(change, v1);
    this->end();
}
DataOfAuditors::~DataOfAuditors()
{
    delete displayAuditor;
    delete auditorTable;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfAuditors::hideGroup()
{
    this->displayAuditor->hide();
    this->auditorTable->hide();
    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
}
void DataOfAuditors::change(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAuditors *data = (DataOfAuditors*)v->at(0);
    DisplayAuditor *displayAuditor = (DisplayAuditor*)v->at(1);
    AuditorTable *auditorTable = (AuditorTable*)v->at(2);
    Auditor *a = data->auditors->getRow(displayAuditor->getCurrent());
    a->setName(displayAuditor->getValueName());
    a->setLastname(displayAuditor->getValueLastName());
    a->setSalary(stod(displayAuditor->getValueSalary()));
    a->setDateBirth(displayAuditor->getValueDateBirth());
    a->setDatesVisiting(displayAuditor->getDatesVisiting());
    auditorTable->redraw();
}
void DataOfAuditors::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfAuditors *data = (DataOfAuditors*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

/*void DataOfAuditors::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayAuditor->displayAuditor(event->auditors->getElement(endRow));
}*/

void DataOfAuditors::removeElem(Fl_Widget *widget, void *data)
{
    DataOfAuditors *e = (DataOfAuditors *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->auditorTable->get_selection(startRow, colLeft, endRow, colRight);
    // cout << "Dodje" << endl;
    // cout << "size1:" << e->auditors->numberOfElement() << endl;
    for (int i = endRow; i >= startRow; i--)
    {
        e->auditors->removeRow(i);
        // e->auditorTable->rows(e->auditors->numberOfRows());
        // e->auditorTable->cols(e->auditors->numberOfColumns());
    }
    // cout << "prodje" << endl;
}

// Company& DataOfAuditors::getCompany()
// {
//     return company;
// }
void DataOfAuditors::refreshTable()
{
    auditorTable->refreshTable();
}
