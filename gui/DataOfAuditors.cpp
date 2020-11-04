#include "DataOfAuditors.hpp"
#include "../Class/Auditor.hpp"
using namespace std;

/*struct Event
{
    ArrayAuditors *auditors;
    AuditorTable *tabela;
    DisplayAuditor *displayAuditor;
};*/
DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, Company &company, const char *l=0) : Fl_Group(x , y ,w ,h ,l), company(company){

    this->auditors = new ArrayAuditors();
    
    auditorTable = new AuditorTable(x, y+340, 400, 280, this->company);
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, company, auditorTable, "");
    
    //btnView = new Fl_Button(x+330, y+300, 70, 30, "View");
    btnRemove = new Fl_Button(x+400, y+300, 70, 30, "Remove");

    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::remove, this);

    this->end();
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
    for (int i = endRow; i >= startRow; i--)
    {
        e->auditors->removeRow(i);
        e->auditorTable->rows(e->auditors->numberOfRows());
        e->auditorTable->cols(e->auditors->numberOfColumns());
    }
}

Company& DataOfAuditors::getCompany()
{
    return company;
}
void DataOfAuditors::refreshTable()
{
    auditorTable->refreshTable();
}
