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

DataOfAudits::DataOfAudits(int x, int y, int w, int h, Array<Audit*> *original, Array<Audit*> *changed, Array<Department*> *originalDepartments, Array<Department*> *changedDepartments, void *mainWindow, const char *l)
 : DataOf(x, y, w, h, original, changed, mainWindow, l)
 {
    this->changedDepartments = changedDepartments;
    this->originalDepartments = originalDepartments;
    chAuditor = new Fl_Choice(x+50, y, 100, 50, "Auditor:");
    chDepartment = new Fl_Choice(x+160, y, 100, 50, "Department:");
    chDepartment->align(FL_ALIGN_TOP);
    displayAudit = new DisplayAudit(x+50, y+60, 200, 300, "");

    btnPrevious->resize(btnPrevious->x()+50, btnPrevious->y(), btnPrevious->w(), btnPrevious->h());
    btnNext->resize(btnNext->x()+50, btnNext->y(), btnNext->w(), btnNext->h());

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>();
    DataOfCompanies *main = (DataOfCompanies*)mainWindow;
    v->push_back(main);
    v->push_back(this);
    btnGoBack->callback(DataOfAudits::goBack,v);

    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    chAuditor->callback(displayAud, this);
    chDepartment->callback(displayDep, this);

    this->insertDataInChDepartment();

    if(changed->numberOfElement() != 0){
        displayAudit->displayThisAudit(changed->getElement(0));
    }
    
    this->isAuditsEmpty();
    this->checkButtons();
    this->end();
}

void DataOfAudits::displayAud(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    data->displayAudit->displayThisAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value()));
}
void DataOfAudits::displayDep(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    data->insertDataInChAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors());
    data->isAuditorsEmpty();
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
        displayAudit->displayThisAuditor(auditors->at(0));
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
    
    if(this->changedDepartments->numberOfElement() == 0)
    {
        btnAdd->deactivate();
    }
    else
    {
        btnAdd->activate();
    }
}

void DataOfAudits::isAuditorsEmpty()
{
    if(this->changedDepartments->getElement(chDepartment->value())->getAuditors()->size() == 0)
    {
        this->btnAdd->deactivate();
        this->btnChange->deactivate();
    }
    else{
        this->btnAdd->activate();
        this->btnChange->activate();
    }
}

void DataOfAudits::add(Fl_Widget *widget, void *data)
{
    DataOfAudits *d = (DataOfAudits*)data;
    if(!d->displayAudit->isInputsEmpty())
    {
        return;
    }
    
    Auditor* worker = d->changedDepartments->getElement(d->chDepartment->value())->getAuditors()->at(d->chAuditor->value());
    
    try
    {
        if(!worker->isAvailabe(d->displayAudit->getDate()))
        {
            fl_message("Auditor is not available at that time, please choose another time!");
            return;
        }
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date"));
        return;
    }
    
    int counter = 0;
    int counter1 = 0;
    bool found = false;
    Auditor *a1;
    for(int i = 0; i < d->originalDepartments->numberOfElement(); i++)
    {
        if(!d->originalDepartments->getElement(i)->isDeleted())
        {
            if(counter == d->chDepartment->value())
            {
                counter1 = 0;
                for(int j = 0; j < d->originalDepartments->getElement(i)->getAuditors()->size(); j++)
                {
                    if(!d->originalDepartments->getElement(i)->getAuditors()->at(j)->isDeleted())
                    {
                        if(counter1 == d->chAuditor->value())
                        {
                            a1 = d->originalDepartments->getRow(i)->getAuditors()->at(j);
                            a1->addDateVisiting(d->displayAudit->getDate());
                            found = true;
                            counter = i;
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
    
    worker->addDateVisiting(d->displayAudit->getDate());

    d->table->add(new Audit(worker, d->displayAudit->getDate()));
    d->original->add(new Audit(a1, d->displayAudit->getDate()));
    d->changedDepartments->getElement(d->chDepartment->value())->getAudits()->push_back(new Audit(worker, d->displayAudit->getDate()));
    d->originalDepartments->getElement(counter)->getAudits()->push_back(new Audit(a1, d->displayAudit->getDate()));
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
    Auditor* head1 = data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value());
    Date oldDate = *data->getElement(data->getCurrent())->getDate();
    if(!head1->isAvailabe(data->displayAudit->getDate()))
    {
        fl_message("Auditor is not available at that time, please choose another time!");
        return;
    }
    dep->setDate(data->displayAudit->getDate());
    dep->getAuditor()->removeDateVisiting(&oldDate);
    head1->removeDateVisiting(&oldDate);
    head1->addDateVisiting(data->displayAudit->getDate());
    dep->setAuditor(head1);

    int counter = 0;
    int counter1 = 0;
    bool found = false;
    Auditor *head2;
    for(int i = 0; i < data->originalDepartments->numberOfElement(); i++)
    {
        if(!data->originalDepartments->getElement(i)->isDeleted())
        {
            if(counter == data->chDepartment->value())
            {
                counter1 = 0;
                for(int j = 0; j < data->originalDepartments->getElement(i)->getAuditors()->size(); j++)
                {
                    if(!data->originalDepartments->getElement(i)->getAuditors()->at(j)->isDeleted())
                    {
                        if(counter1 == data->chAuditor->value())
                        {
                            head2 = data->originalDepartments->getRow(i)->getAuditors()->at(j);
                            found = true;
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


    int counterA = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counterA == data->getCurrent())
            {
                Audit *a1 = data->original->getRow(i);
                a1->setDate(data->displayAudit->getDate());
                a1->getAuditor()->removeDateVisiting(&oldDate, 1);
                head2->removeDateVisiting(&oldDate, 1);
                head2->addDateVisiting(data->displayAudit->getDate());
                a1->setAuditor(head2);
                break;
            }
            counterA++;
        }
    }
    
    data->changedDepartments->getElement(data->chDepartment->value())->getAudits()->at(data->getCurrent())->setDate(data->displayAudit->getDate());
    data->changedDepartments->getElement(data->chDepartment->value())->getAudits()->at(data->getCurrent())->setAuditor(head1);

    data->originalDepartments->getElement(counter)->getAudits()->at(counterA)->setDate(data->displayAudit->getDate());
    data->originalDepartments->getElement(counter)->getAudits()->at(counterA)->setAuditor(head2);

    data->table->redraw();
    
    data->setDisplay(data->getCurrent());
}

void DataOfAudits::hideGroup(){
    DataOf<Audit*>::hideGroup();
    this->label("");
    this->displayAudit->hideGroup();

    this->btnChange->hide();
    this->btnAdd->hide();
}
void DataOfAudits::unhideGroup(){
    DataOf<Audit*>::unhideGroup();
    this->redraw_label();
    this->updateLabel();
    this->displayAudit->unhide();

    this->btnChange->show();
    this->btnAdd->show();
}

DataOfAudits::~DataOfAudits(){}
