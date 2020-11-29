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

DataOfAudits::DataOfAudits(int x, int y, int w, int h, Array<Department*> *originalDepartments, Array<Department*> *changedDepartments, void *mainWindow, const char *l)
 : DataOf(x, y, w, h, new Array<Audit*>(), new Array<Audit*>(), mainWindow, l), changedDepartments(changedDepartments), originalDepartments(originalDepartments)
 {
    this->refreshArrays();
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
    btnRemove->callback(removeElem, v);

    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    chAuditor->callback(displayAud, this);
    chDepartment->callback(displayDep, this);

    this->insertDataInChDepartment();
    this->refreshArrays(1);
    
    if(this->changed->numberOfElement() != 0){
        this->displayAudit->displayThisAudit(this->changed->getElement(this->changed->numberOfElement()-1),
         this->changedDepartments->getElement(this->chDepartment->value())->getAuditors()->at(this->chAuditor->value()));
    }
    
    this->isEmpty();
    this->end();
}

void DataOfAudits::isEmpty()
{
    this->isAuditsEmpty();
    this->isAuditorsEmpty();
    this->checkButtons();
    this->table->refreshTable();
}
void DataOfAudits::refreshArrays(int start)
{
    Department* dep1;
    int counterDep1 = 0;
    for(int i = 0; i < originalDepartments->numberOfElement(); i++)
    {
        if(!originalDepartments->getElement(i)->isDeleted())
        {
            if(start == 0)
            {
                dep1 = originalDepartments->getElement(i);
                counterDep1++;
                break;
            }
            else if(chDepartment->value() == counterDep1 && start != 0)
            {
                dep1 = originalDepartments->getElement(i);
                counterDep1++;
                break;
            }
            counterDep1++;
        }
    }
    
    if(counterDep1 != 0)
    {
        original = new Array<Audit*>(dep1->getAudits());
    }

    Department* dep2;
    if(changedDepartments->numberOfElement() != 0)
    {
        if(start == 0)
        {
            dep2 = changedDepartments->getElement(0);
        }
        else
        {
            dep2 = changedDepartments->getElement(chDepartment->value());
        }
        changed = new Array<Audit*>(dep2->getAudits());
    }

    this->table->setArray(changed);

    this->updateLabel();
}
void DataOfAudits::removeElem(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAudits *e = (DataOfAudits*)v->at(1);
    DataOfCompanies *parent = (DataOfCompanies*)v->at(0);

    int startRow = -1;
    int endRow = -1;
    int colLeft = -1;
    int colRight = -1;
    try{
        e->table->get_selection(startRow, colLeft, endRow, colRight);
        if(startRow == -1 || endRow == -1 || colLeft == -1 || colRight == -1 || startRow >= e->changed->numberOfElement())
        {
            throw UnselectedDataToRemove();
        }
    }
    catch(UnselectedDataToRemove e)
    {
        fl_message(e.what());
        return;
    }
    for (int i = endRow; i >= startRow; i--)
    {
        Auditor *changA = e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->getAuditor();
        Date* date1 = e->changed->getElement(i)->getDate();
        changA->removeDateVisiting(date1);
        e->changed->getElement(i)->getAuditor()->removeDateVisiting(date1);
        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->getAuditor()->removeDateVisiting(date1);
        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->setAuditor(nullptr);
        parent->getElement(parent->getValueChCompany())->getDepartment(e->chDepartment->value())->getAuditors()->at(e->chAuditor->value())->removeDateVisiting(date1);
        

        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->erase(e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->begin()+i);
        
        e->table->refreshTable();

        int counterA = 0;
        for(int j = 0; j < e->original->numberOfElement(); j++)
        {
            if(!e->original->getElement(j)->isDeleted())
            {
                if(counterA == i)
                {
                    counterA = j;
                    break;
                }
                counterA++;
            }
        }

        int counter = 0;
        int counter1 = 0;
        bool found = false;
        Auditor *a1;
        for(int z = 0; z < e->originalDepartments->numberOfElement(); z++)
        {
            if(!e->originalDepartments->getElement(z)->isDeleted())
            {
                if(counter == e->chDepartment->value())
                {
                    counter1 = 0;
                    for(int j = 0; j < e->originalDepartments->getElement(z)->getAuditors()->size(); j++)
                    {
                        if(!e->originalDepartments->getElement(z)->getAuditors()->at(j)->isDeleted())
                        {
                            if(counter1 == e->chAuditor->value())
                            {
                                Date* date2 = e->original->getElement(counterA)->getDate();
                                a1 = e->originalDepartments->getRow(z)->getAuditors()->at(j);
                                a1->removeDateVisiting(date2, 1);
                                e->original->getElement(counterA)->getAuditor()->removeDateVisiting(date2, 1);
                                e->originalDepartments->getElement(z)->getAudits()->at(counterA)->setDeleted();
                                e->originalDepartments->getElement(z)->getAudits()->at(counterA)->getAuditor()->removeDateVisiting(date2, 1);
                                int counterC = 0;
                                // for(int x = 0; x < parent->getArrayOriginal()->numberOfElement(); x++)
                                // {
                                //     if(!parent->getArrayOriginal()->getElement(z)->isDeleted())
                                //     {
                                //         if(counterC == parent->getValueChCompany())
                                //         {
                                //             parent->getArrayOriginal()->getElement(x)->getDepartment(z)->getAuditors()->at(j)->removeDateVisiting(date2);
                                //             break;
                                //         }
                                //     }
                                // }
                                found = true;
                                counter = z;
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
    }
    
    if(e->changed->numberOfElement() != 0)
    {
        e->displayAudit->displayThisAudit(e->changed->getElement(0),
         e->changedDepartments->getElement(e->chDepartment->value())->getAuditors()->at(e->chAuditor->value()));
    }
    
    e->updateLabel();
    e->isEmpty();
    displayDep(widget, e);
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
    data->refreshArrays(1);
    if(data->changed->numberOfElement() != 0){
        data->displayAudit->displayThisAudit(data->changed->getElement(data->changed->numberOfElement() - 1),
         data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value()));
    }
    data->isEmpty();
}
void DataOfAudits::insertDataInChDepartment()
{
    string aud = "";
    chDepartment->clear();
    
    for(int i = 0; i < changedDepartments->numberOfElement(); i++)
    {
        string s = to_string(i+1).append(".");
        s.append(changedDepartments->getElement(i)->getName());
        aud.append(s);
        aud.append("|");
    }
    
    chDepartment->add(aud.c_str());
    chDepartment->redraw();
    if(changedDepartments->numberOfElement() != 0)
    {
        chDepartment->value(changedDepartments->numberOfElement() - 1);
        this->insertDataInChAuditor(changedDepartments->getElement(chDepartment->value())->getAuditors());
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
        s.append(auditors->at(i)->getLastname());
        aud.append(s);
        aud.append("|");
    }
    
    chAuditor->add(aud.c_str());
    chAuditor->redraw();
    
    if(auditors->size() != 0)
    {
        chAuditor->value(auditors->size() - 1);
        displayAudit->displayThisAuditor(auditors->at(auditors->size() - 1));
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
        displayAudit->displayThisAudit(this->getElement(current),
         this->changedDepartments->getElement(this->chDepartment->value())->getAuditors()->at(this->chAuditor->value()));
    }
    updateLabel();
}

void DataOfAudits::isAuditsEmpty() const
{
    this->isArrayEmpty();
    if(this->sizeOfArray() == 0 || this->changedDepartments->getElement(chDepartment->value())->getAuditors()->size() == 0){
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

void DataOfAudits::isAuditorsEmpty() const
{
    if(this->changedDepartments->numberOfElement() != 0)
    {
        if(this->changedDepartments->getElement(chDepartment->value())->getAuditors()->size() == 0)
        {
            this->btnAdd->deactivate();
        }
        else{
            this->btnAdd->activate();
        }
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
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
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

    Audit *changed1 = new Audit(worker, d->displayAudit->getDate());
    Audit *original1 = new Audit(a1, d->displayAudit->getDate());
    // d->table->add(changed1);
    // d->original->add(original1);
    d->changedDepartments->getElement(d->chDepartment->value())->getAudits()->push_back(changed1);
    d->originalDepartments->getElement(counter)->getAudits()->push_back(original1);
    d->setDisplay(d->sizeOfArray()-1);
    d->updateLabel();
    d->isEmpty();
    displayDep(widget, data);
    // d->refreshArrays(1);
}
void DataOfAudits::change(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    if(!data->displayAudit->isInputsEmpty())
    {
        return;
    }
    Audit *depC = data->changed->getRow(data->getCurrent());
    // Audit *depCD = data->changedDepartments->getRow(data->chDepartment->value())->getAudits()->at(data->getCurrent());
    Auditor* head1 = data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value());
    // Auditor* head1 = data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value());
    Date oldDate = *data->getElement(data->getCurrent())->getDate();
    try
    {
        if(!head1->isAvailabe(data->displayAudit->getDate()))
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
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    depC->setDate(data->displayAudit->getDate());
    depC->getAuditor()->removeDateVisiting(&oldDate);
    // depC->getAuditor()->addDateVisiting(data->displayAudit->getDate());
    
    head1->removeDateVisiting(&oldDate);
    head1->addDateVisiting(data->displayAudit->getDate());
    depC->setAuditor(head1);

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
    displayDep(widget, d);
    // data->refreshArrays(1);
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
