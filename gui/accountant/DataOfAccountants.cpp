#include "DataOfAccountants.hpp"
#include "../../Class/Accountant.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../MainWindow.hpp"
#include "../../Util.hpp"
#include <sstream>
#include <FL/fl_message.H>

using namespace std;

/*struct Event
{
    ArrayAccountants *accountants;
    AccountantTable *tabela;
    DisplayAccountant *displayAccountant;
};*/
AccountantTable* DataOfAccountants::getAccountantTable()
{
    return accountantTable;
}
void DataOfAccountants::isArrayEmpty()
{
    if(accountants->numberOfElement() == 0)
    {
        btnChange->deactivate();
        btnRemove->deactivate();
        btnNext->deactivate();
        btnPrevious->deactivate();
    }
    else
    {
        btnChange->activate();
        btnRemove->activate();
        btnNext->activate();
        btnPrevious->activate();
    }
}
void DataOfAccountants::addAccountant(Accountant* a)
{
    accountants->add(a);
}
int DataOfAccountants::numberOfAccountants()
{
    return accountants->numberOfElement();
}

DataOfAccountants::DataOfAccountants(int x, int y, int w, int h, ArrayAccountants *accountants, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), accountants(accountants)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);
    displayAccountant = new DisplayAccountant(x+50, y, 300, 390, "");
    accountantTable = new AccountantTable(x+200, y+340, 400, 280, accountants);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+300, y+300, 70, 30, "Add");
    btnRemove = new Fl_Button(x+380, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");
    btnPrevious = new Fl_Button(x+170, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+220, y, 45, 70, "@->");

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);
    btnAdd->callback(add, this);

    if(accountants->numberOfElement() != 0){
        this->setDisplay(current);
    }

    accountants->subscribeListener(this);

    //btnView->callback(DataOfAccountants::view, ev);
    btnRemove->callback(DataOfAccountants::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfAccountants::goBack, v);
    
    vector<Fl_Widget*> *v1 = new vector<Fl_Widget*>(0);
    v1->push_back(this);
    v1->push_back(displayAccountant);
    v1->push_back(accountantTable);
    btnChange->callback(change, v1);
    this->isArrayEmpty();
    this->checkButtons();
    this->end();
}
void DataOfAccountants::updateLabel()
{
    stringstream sstream;
    sstream << "Accountant " << current + 1 << "/" << accountants->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DataOfAccountants::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= accountants->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

void DataOfAccountants::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < accountants->numberOfElement())
    {
        current = indeks;
        this->displayAccountant->displayWorker(accountants->getElement(indeks));
        // this->displayAccountant->bodyIssuedPermit = new Fl_Input(this->x(), this->y()+200, 200, 70, "Issued Permit:");
        // this->displayAccountant->maxAmountCompanyIncome = new Fl_Input(this->x(), this->y()+280, 200, 70, "Max Income:");
        this->displayAccountant->setBodyIssuedPermit(accountants->getElement(indeks)->getBodyIssuedPermit().c_str());
        this->displayAccountant->setMaxAmountCompanyIncome(to_string(accountants->getElement(indeks)->getMaxAmountCompanyIncome()).c_str());
    }
    updateLabel();
}

void DataOfAccountants::nextElement(Fl_Widget *widget, void *data){
    DataOfAccountants *dataOf = (DataOfAccountants *) data;
    if (dataOf->current + 1 < dataOf->accountants->numberOfElement())
    {
        dataOf->current++;
        dataOf->setDisplay(dataOf->current);
    }

    dataOf->checkButtons();
}

void DataOfAccountants::previousElement(Fl_Widget *widget, void *data)
{
    DataOfAccountants *dataOf = (DataOfAccountants *) data;
    if (dataOf->current - 1 >= 0)
    {
        dataOf->current--;
        dataOf->setDisplay(dataOf->current);
    }

    dataOf->checkButtons();
}

void DataOfAccountants::elementPushed(int indeks, Accountant *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DataOfAccountants::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DataOfAccountants::getCurrent()
{
    return current;
}

void DataOfAccountants::add(Fl_Widget *widget, void *data)
{
    DataOfAccountants *d = (DataOfAccountants*)data;
    Accountant *novaOsoba;
    try{
        novaOsoba = new Accountant(d->displayAccountant->getValueName(), d->displayAccountant->getValueLastName(),
                        d->displayAccountant->getValueDateBirth(), d->displayAccountant->getValueSalary(),
                        d->displayAccountant->getBodyIssuedPermit(), d->displayAccountant->getMaxAmountCompanyIncome());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
                    
    d->accountantTable->add(novaOsoba);
    d->setDisplay(d->accountants->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
DataOfAccountants::~DataOfAccountants()
{
    delete displayAccountant;
    delete accountantTable;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfAccountants::hideGroup()
{
    this->label("");
    this->displayAccountant->hide();
    this->accountantTable->hide();
    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
}
void DataOfAccountants::change(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAccountants *data = (DataOfAccountants*)v->at(0);
    DisplayAccountant *displayAccountant = (DisplayAccountant*)v->at(1);
    AccountantTable *accountantTable = (AccountantTable*)v->at(2);
    Accountant *a = data->accountants->getRow(data->getCurrent());
    try{
        a->setName(displayAccountant->getValueName());
        a->setLastname(displayAccountant->getValueLastName());
        a->setSalary(displayAccountant->getValueSalary());
        a->setDateBirth(displayAccountant->getValueDateBirth());
        a->setBodyIssuedPermit(displayAccountant->getBodyIssuedPermit());
        a->setMaxAmountCompanyIncome(displayAccountant->getMaxAmountCompanyIncome());
        accountantTable->redraw();
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
}
void DataOfAccountants::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfAccountants *data = (DataOfAccountants*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

/*void DataOfAccountants::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayAccountant->displayAccountant(event->accountants->getElement(endRow));
}*/

void DataOfAccountants::removeElem(Fl_Widget *widget, void *data)
{
    DataOfAccountants *e = (DataOfAccountants *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->accountantTable->get_selection(startRow, colLeft, endRow, colRight);
    for (int i = endRow; i >= startRow; i--)
    {
        e->accountants->removeRow(i);
    }
    if(e->accountants->numberOfElement() == 0){
        e->setDisplay(0);
    }
    else{
        e->setDisplay(e->accountants->numberOfElement()-1);
    }
    e->updateLabel();
    e->isArrayEmpty();
    e->checkButtons();
}

// Company& DataOfAccountants::getCompany()
// {
//     return company;
// }
void DataOfAccountants::refreshTable()
{
    accountantTable->refreshTable();
}
