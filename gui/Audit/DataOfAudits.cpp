#include "DataOfAudits.hpp"
#include "../../Class/Audit.hpp"
#include "DisplayAudit.hpp"

#include "../Company/DataOfCompanies.hpp"

#include "../Auditor/DataOfAuditors.hpp"
#include "../Accountant/DataOfAccountants.hpp"
#include "../Commercialist/DataOfCommercialists.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>

using namespace std;

DataOfAudits::DataOfAudits(int x, int y, int w, int h, ArrayAudits *array, void *mainWindow, const char *l)
 : DataOf(x , y ,w ,h , array, mainWindow, l){
    chAuditor = new Fl_Choice(x+50, y, 100, 50, "");
    displayAudit = new DisplayAudit(x+50, y+60, 200, 300, "");

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    DataOfCompanies *main = (DataOfCompanies*)mainWindow;
    v->push_back(main);
    v->push_back(this);
    btnGoBack->callback(DataOfAudits::goBack,v);

    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    this->insertDataInChAuditor(array);
    this->chAuditor->value(0);
    this->displayAuditor();
    this->end();
}

void DataOfAudits::displayAuditor()
{
    displayAudit->displayThisAuditor(this->array->getElement(chAuditor->value())->getAuditor());
}
void DataOfAudits::insertDataInChAuditor(ArrayAudits *array)
{
    string aud = "";
    chAuditor->clear();
    for(int i = 0; i < this->sizeOfArray(); i++)
    {
        string s = to_string(i+1).append(".");
        s.append(this->array->getElement(i)->getAuditor()->getName()).append(" ");
        s.append(this->array->getElement(i)->getAuditor()->getName());
        aud.append(s);
        aud.append("|");
    }
    chAuditor->add(aud.c_str());
    chAuditor->redraw();
    chAuditor->value(0);
}
void DataOfAudits::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAudits *data = (DataOfAudits*)v->at(1);
    DataOfCompanies *parent = (DataOfCompanies*)v->at(0);
    
    data->hideGroup();
    data->hide();
    parent->remove(data);
    parent->unhideGroup();
}

void DataOfAudits::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        string type = this->getElement(current)->getAuditor()->getType();
        displayAudit->setDate(this->getElement(indeks)->getDate()->getDateWithTime().c_str());
        displayAudit->displayThisAuditor(this->getElement(indeks)->getAuditor());
    }
    updateLabel();
}

void DataOfAudits::isAuditsEmpty()
{
    this->isArrayEmpty();
    if(this->sizeOfArray() == 0){
        btnChange->deactivate();
    }
    else
    {
        btnChange->activate();
    }
}
void DataOfAudits::change(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    if(!data->displayAudit->isInputsEmpty())
    {
        return;
    }
    Audit *dep = data->array->getRow(data->getCurrent());
    dep->setDate(data->displayAudit->getDate());
    string type = data->array->getElement(data->getCurrent())->getAuditor()->getType();
    Auditor* head;
    try{
        head = data->displayAudit->getAuditor();
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    dep->setAuditor(new Auditor(head->getName(), head->getLastname(), head->getDateBirth(), head->getSalary()));
    data->table->redraw();
}

void DataOfAudits::hideGroup(){
    DataOf<Audit>::hideGroup();
    this->label("");
    this->displayAudit->hideGroup();

    this->btnChange->hide();
    this->btnAdd->hide();
}
void DataOfAudits::unhideGroup(){
    DataOf<Audit>::unhideGroup();
    this->redraw_label();
    this->updateLabel();
    this->displayAudit->unhide();

    this->btnChange->show();
    this->btnAdd->show();
}

DataOfAudits::~DataOfAudits(){}

void DataOfAudits::add(Fl_Widget *widget, void *data)
{
    DataOfAudits *d = (DataOfAudits*)data;
    if(!d->displayAudit->isInputsEmpty())
    {
        return;
    }
    Auditor* worker;
    try{
        worker = d->displayAudit->getAuditor();
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    Audit *department = new Audit(worker, d->displayAudit->getDate());
    d->table->add(department);
    d->setDisplay(d->array->numberOfElement()-1);
    d->updateLabel();
    d->isAuditsEmpty();
    d->checkButtons();
}