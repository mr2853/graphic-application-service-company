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
    cout << "ovdde" << endl;
    this->refreshArrays();
    cout << "ovdde1" << endl;
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
    
    cout << "ovdde2" << endl;
    if(this->changed->numberOfElement() != 0){
        cout << this->changed->numberOfElement() << endl;
        this->displayAudit->displayThisAudit(this->changed->getElement(0));
        // this->refreshArrays(1);
    }
    
    cout << "ovdde3" << endl;
    this->isEmpty();
    this->end();
}

void DataOfAudits::isEmpty()
{
    this->isAuditsEmpty();
    this->isAuditorsEmpty();
    this->checkButtons();
}
void DataOfAudits::refreshArrays(int start)
{
    // this->original = new Array<Audit*>();
    cout << "d1" << endl;
    Department* dep1;
    int counterDep1 = 0;
    cout << "d2" << endl;
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
                cout << "d3" << endl;
                dep1 = originalDepartments->getElement(i);
                cout << "d4" << endl;
                counterDep1++;
                break;
            }
            counterDep1++;
        }
    }
    cout << "delete1" << endl;
    if(counterDep1 != 0)
    {
        original = new Array<Audit*>(dep1->getAudits());
    }

    // this->changed = new Array<Audit*>();
    cout << "delete2" << endl;
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
    cout << "delete4" << endl;

    this->table->setArray(this->changed);

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
        cout << "size: " << e->changed->numberOfElement() << endl;
        // parent->getElement(parent->getCurrent())->getDepartments()->at(e->chDepartment->value())->getAudits()->at(i)->getAuditor()->removeDateVisiting(e->changed->getElement(i)->getDate());
        Auditor *changA = e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->getAuditor();
        cout << "ovde 1." << endl;

        changA->removeDateVisiting(e->changed->getElement(i)->getDate());
        // e->changed->getElement(i)->getAuditor()->removeDateVisiting(e->changed->getElement(i)->getDate());
        cout << "ovde 1.." << endl;

        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->getAuditor()->removeDateVisiting(e->changed->getElement(i)->getDate());
        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->at(i)->setAuditor(nullptr);
        // e->changed->getElement(i)->setAuditor(nullptr);
        cout << "ovde 1..." << endl;
        parent->getElement(parent->getValueChCompany())->getDepartment(e->chDepartment->value())->getAuditors()->at(e->chAuditor->value())->removeDateVisiting(e->changed->getElement(i)->getDate());
        
        // e->changed->removeRow(i);
        cout << "ovde 1.../" << endl;

        e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->erase(e->changedDepartments->getElement(e->chDepartment->value())->getAudits()->begin()+i);
        // e->changed->getElement(i)->getAuditor()->removeDateVisiting(e->changed->getElement(i)->getDate());
        // cout << "ovde 1" << endl;
        // e->changed->getElement(i)->setAuditor(nullptr);
        // cout << "ovde 2" << endl;
        e->table->refreshTable();
        // cout << "size: " << e->changed->numberOfElement() << endl;
        
        cout << "ovde 3" << endl;

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
                                cout << "here0" << endl;
                                a1 = e->originalDepartments->getRow(z)->getAuditors()->at(j);
                                cout << "here1" << endl;
                                a1->removeDateVisiting(e->original->getElement(counterA)->getDate(), 1);
                                cout << "here2" << endl;
                                // e->original->getElement(counterA)->getAuditor()->removeDateVisiting(e->original->getElement(counterA)->getDate(), 1);

                                // e->original->getElement(counterA)->setDeleted();
                                e->originalDepartments->getElement(z)->getAudits()->at(counterA)->setDeleted();
                                e->originalDepartments->getElement(z)->getAudits()->at(counterA)->getAuditor()->removeDateVisiting(e->original->getElement(counterA)->getDate(), 1);
                                cout << "here3" << endl;

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
    
    cout << "here4" << endl;
    cout << e->changed->numberOfElement() << endl;
    if(e->changed->numberOfElement() != 0)
    {
        e->displayAudit->displayThisAudit(e->changed->getElement(0));
    }
    cout << "here5" << endl;
    e->updateLabel();
    e->isEmpty();
    cout << "here6" << endl;
    displayDep(widget, e);
    cout << "here7" << endl;
    // e->refreshArrays(1);
}


void DataOfAudits::displayAud(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    data->displayAudit->displayThisAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors()->at(data->chAuditor->value()));
}
void DataOfAudits::displayDep(Fl_Widget *widget, void *d)
{
    DataOfAudits *data = (DataOfAudits*)d;
    cout << "displayDep" << endl;
    data->insertDataInChAuditor(data->changedDepartments->getElement(data->chDepartment->value())->getAuditors());
    cout << "displayDep1" << endl;
    data->isAuditorsEmpty();
    cout << "displayDep2" << endl;
    data->refreshArrays(1);
    cout << "displayDep3" << endl;
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
        chDepartment->value(0);
        this->insertDataInChAuditor(changedDepartments->getElement(0)->getAuditors());
    }
    // this->refreshArrays(1);
}
void DataOfAudits::insertDataInChAuditor(vector<Auditor*>* auditors)
{
    cout << "insert" << endl;
    string aud = "";
    chAuditor->clear();
    cout << "insert1" << endl;
    
    for(int i = 0; i < auditors->size(); i++)
    {
        string s = to_string(i+1).append(".");
        s.append(auditors->at(i)->getName()).append(" ");
        s.append(auditors->at(i)->getLastname());
        aud.append(s);
        aud.append("|");
    }
    cout << "insert1" << endl;
    cout << "insert" << endl;
    
    chAuditor->add(aud.c_str());
    chAuditor->redraw();
    cout << aud << endl;
    
    if(auditors->size() != 0)
    {
        cout << "insert3" << endl;
        chAuditor->value(0);
        cout << "insert4" << endl;
        displayAudit->displayThisAuditor(auditors->at(0));
        cout << "insert5" << endl;
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
        displayAudit->displayThisAudit(this->getElement(current));
    }
    updateLabel();
}

void DataOfAudits::isAuditsEmpty() const
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

void DataOfAudits::isAuditorsEmpty() const
{
    if(this->changedDepartments->getElement(chDepartment->value())->getAuditors()->size() == 0)
    {
        this->btnAdd->deactivate();
    }
    else{
        this->btnAdd->activate();
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
