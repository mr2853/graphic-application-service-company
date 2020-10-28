#include "DataOfAuditors.hpp"


struct Event
{
    ArrayAuditors *auditors;
    AuditorTable *tabela;
    DisplayAuditor *displayAuditor;
};
DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, Company &company, const char *l=0) : Fl_Group(x , y ,w ,h ,l){

    this->auditors = new ArrayAuditors();
    vector<Auditor *> *auditors = company.getCompanyAuditors();
    for(Auditor *aud : *auditors)
    {
        this->auditors->add(aud);
    }
    
    DisplayAuditor *displayAuditor = new DisplayAuditor(x+50, y, 300, 150, this->auditors, "");
    AuditorTable *auditorTable = new AuditorTable(x, y+340, 400, 280, this->auditors);
    
    for(Auditor *aud : *auditors)
    {
        auditorTable->add(aud);
        //this->auditors->add(aud);
    }

    btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");
    //btnView = new Fl_Button(x+330, y+300, 70, 30, "View");
    btnRemove = new Fl_Button(x+400, y+300, 70, 30, "Remove");

    Event *ev = new Event();
    ev->auditors = this->auditors;
    ev->displayAuditor = this->displayAuditor;
    ev->tabela = auditorTable;

    btnAdd->callback(DataOfAuditors::add, this);
    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::remove, ev);

    this->end();
}

void DataOfAuditors::add(Fl_Widget *widget, void *data)
{
    DataOfAuditors *dataOfAuditors = (DataOfAuditors *)data;
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
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    for (int i = endRow; i >= startRow; i--)
    {
        event->auditors->removeRow(i);
        event->tabela->rows(event->auditors->numberOfRows());
        event->tabela->cols(event->auditors->numberOfColumns());
    }
}