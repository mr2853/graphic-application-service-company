#include "DataOfAuditors.hpp"
#include "../Class/Auditor.hpp"
#include "DataOfDepartments.hpp"
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

DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, ArrayAuditors *auditors, void *dataOfDepartments, const char *l)
 : Fl_Group(x , y ,w ,h ,l), auditors(auditors)
 {
    
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, auditors, this, "");
    auditorTable = new AuditorTable(x+50, y+340, 400, 280, auditors);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnRemove = new Fl_Button(x+370, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");

    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::remove, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    DataOfDepartments *parent = (DataOfDepartments*)dataOfDepartments;
    v->push_back(parent);
    v->push_back(this);
    btnGoBack->callback(DataOfAuditors::goBack, v);
    
    btnChange->callback(change, v);

    this->end();
}

void DataOfAuditors::change(Fl_Widget *widget, void *data)
{

}
void DataOfAuditors::hideGroup()
{
    this->label("");
    this->displayAuditor->hideGroup();
    this->auditorTable->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnChange->hide();
    this->hide();
}
void DataOfAuditors::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfAuditors *data = (DataOfAuditors*)v->at(1);
    data->hideGroup();
    //delete data;
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
DataOfAuditors::~DataOfAuditors(){}

void DataOfAuditors::remove(Fl_Widget *widget, void *data)
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
