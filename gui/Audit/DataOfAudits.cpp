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

DataOfAudits::DataOfAudits(int x, int y, int w, int h, ArrayAudits *original, ArrayAudits *changed, ArrayDepartments *changedDepartments, ArrayDepartments *originalDepartments, void *mainWindow, const char *l)
 : DataOf(x, y, w, h, original, changed, mainWindow, l), changedDepartments(changedDepartments), originalDepartments(originalDepartments)
 {
    chAuditor = new Fl_Choice(x+50, y, 100, 50, "");
    chDepartment = new Fl_Choice(x+160, y, 100, 50, "");
    displayAudit = new DisplayAudit(x+50, y+60, 200, 300, "");


    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    DataOfCompanies *main = (DataOfCompanies*)mainWindow;
    v->push_back(main);
    v->push_back(this);
    btnGoBack->callback(DataOfAudits::goBack,v);

    btnChange->callback(change, this);
    btnAdd->callback(add, this);

    this->insertDataInChDepartment();
    chAuditor->callback(displayAud, this);
    chDepartment->callback(displayDep, this);
    displayAudit->displayThisAudit(changed->getElement(chAuditor->value()));
    this->end();
}

void DataOfAudits::displayAud(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    //cout << "proslo" << endl;
    //cout << data->changed->numberOfElement() << endl;
    data->displayAudit->displayThisAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value()));
    //cout << "proslo1" << endl;
}
void DataOfAudits::displayDep(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    data->insertDataInChAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors());
}
void DataOfAudits::insertDataInChDepartment()
{
    string aud = "";
    chDepartment->clear();
    
    for(int i = 0; i < changedDepartments->numberOfElement(); i++)
    {
        string s = to_string(i+1).append(".");
        s.append(changedDepartments->getElement(i)->getName()).append(" ");
        s.append(changedDepartments->getElement(i)->getName());
        aud.append(s);
        aud.append("|");
    }
    chDepartment->add(aud.c_str());
    chDepartment->redraw();
    if(changedDepartments->numberOfElement() != 0)
    {
        chDepartment->value(0);
        // //cout << "size auditors:" << departments->getElement(0)->getAuditors()->size() << endl;
        this->insertDataInChAuditor(changedDepartments->getElement(0)->getAuditors());
    }
}
void DataOfAudits::insertDataInChAuditor(vector<Auditor*>* auditors)
{
    string aud = "";
    chAuditor->clear();
    
    for(int i = 0; i < auditors->size(); i++)
    {
        string s = to_string(i+1).append(".");
        s.append(auditors->at(i)->getName()).append(" ");
        s.append(auditors->at(i)->getName());
        aud.append(s);
        aud.append("|");
    }
    chAuditor->add(aud.c_str());
    chAuditor->redraw();
    if(auditors->size() != 0)
    {
        chAuditor->value(0);
    }
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
        displayAudit->setDate(this->getElement(current)->getDate()->getDateWithTime().c_str());
        displayAudit->displayThisAudit(this->getElement(current));
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

void DataOfAudits::add(Fl_Widget *widget, void *data)
{
    DataOfAudits *d = (DataOfAudits*)data;
    if(!d->displayAudit->isInputsEmpty())
    {
        return;
    }
    
    d->displayAudit->getAudit()->setAuditor(d->getElement(d->getCurrent())->getAuditor());
    Auditor* worker = d->changedDepartments->getElement(d->chDepartment->value())->getAuditors()->at(d->chAuditor->value());
    Date* date = d->displayAudit->getDate();

    if(!worker->isAvailabe(date))
    {
        fl_message("Auditor is not available at that time, please choose another time!");
        return;
    }
    int counter = 0;
    bool found = false;
    for(int i = 0; i < d->originalDepartments->numberOfElement(); i++)
    {
        if(!d->originalDepartments->getElement(i)->isDeleted())
        {
            if(counter == d->chDepartment->value())
            {
                int counter1 = 0;
                for(int j = 0; j < d->originalDepartments->getElement(i)->getAuditors()->size(); j++)
                {
                    if(!d->originalDepartments->getElement(i)->getAuditors()->at(j)->isDeleted())
                    {
                        if(counter1 == d->chAuditor->value())
                        {
                            Auditor *a1 = d->originalDepartments->getRow(i)->getAuditors()->at(j);
                            a1->addDateVisiting(d->displayAudit->getDate());
                            break;
                        }
                        counter1++;
                    }
                }
                if(found)
                {
                    break;
                }
            }
            counter++;
        }
    }
    Audit *audit = new Audit(worker, date);
    worker->addDateVisiting(date);

    d->table->add(audit);
    d->setDisplay(d->sizeOfArray()-1);
    d->updateLabel();
    d->isAuditsEmpty();
    d->checkButtons();
}
void DataOfAudits::change(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    if(!data->displayAudit->isInputsEmpty())
    {
        return;
    }
    Audit *dep = data->changed->getRow(data->getCurrent());
    Auditor* head = data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value());
    Date* date = data->displayAudit->getDate();
    if(!head->isAvailabe(date))
    {
        fl_message("Auditor is not available at that time, please choose another time!");
        return;
    }
    dep->setDate(date);
    // string type = data->changed->getElement(data->getCurrent())->getAuditor()->getType();
    data->changed->getElement(data->getCurrent())->getAuditor()->removeDateVisiting(data->displayAudit->getDate());
    head->addDateVisiting(data->displayAudit->getDate());
    dep->setAuditor(head);

    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == data->getCurrent())
            {
                Audit *a1 = data->original->getRow(i);
                data->original->getElement(i)->getAuditor()->removeDateVisiting(data->displayAudit->getDate());
                a1->setDate(data->displayAudit->getDate());
                a1->setAuditor(head);
                break;
            }
            counter++;
        }
    }
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
