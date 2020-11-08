#include "DataOfAuditors.hpp"
#include "../Class/Auditor.hpp"
#include "MainWindow.hpp"
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

DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, Company &company, void *mainWindow, const char *l=0) : Fl_Group(x , y ,w ,h ,l), company(company){

    this->auditors = new ArrayAuditors(company.getCompanyAuditors());
    
    auditorTable = new AuditorTable(x, y+340, 400, 280, auditors);
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, auditors, this, "");
    
    //btnView = new Fl_Button(x+330, y+300, 70, 30, "View");
    btnRemove = new Fl_Button(x+400, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+400, y+300, 70, 30, "Go back");

    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::remove, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    MainWindow *main = (MainWindow*)mainWindow;
    v->push_back(main);
    v->push_back(this);
    btnGoBack->callback(DataOfAuditors::goBack, v);

    this->end();
}
void DataOfAuditors::goBack(Fl_Widget *widget, void *data)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)data;
    MainWindow *main = (MainWindow*)v->at(0);
    DataOfAuditors *dataA = (DataOfAuditors*)v->at(1);
    dataA->hide();
    main->unhide();
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

Company& DataOfAuditors::getCompany()
{
    return company;
}
void DataOfAuditors::refreshTable()
{
    auditorTable->refreshTable();
}
