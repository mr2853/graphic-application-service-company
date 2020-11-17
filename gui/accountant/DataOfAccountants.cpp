#include "DataOfAccountants.hpp"
#include "../../Class/Accountant.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../../Util.hpp"
#include <sstream>
#include <FL/fl_message.H>

using namespace std;


DataOfAccountants::DataOfAccountants(int x, int y, int w, int h, ArrayWorkers<Accountant> *array, void *d, const char *l)
 : DataOfWorker(x, y, w, h, array, d, l)
 {
    displayAccountant = new DisplayAccountant(x+50, y, 300, 390, "");
    this->end();
}

void DataOfAccountants::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        this->displayAccountant->displayWorker(this->getElement(indeks));
        this->displayAccountant->setBodyIssuedPermit(this->getElement(indeks)->getBodyIssuedPermit().c_str());
        this->displayAccountant->setMaxAmountCompanyIncome(to_string(this->getElement(indeks)->getMaxAmountCompanyIncome()).c_str());
    }
    updateLabel();
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
                    
    d->table->add(novaOsoba);
    d->setDisplay(d->array->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
DataOfAccountants::~DataOfAccountants()
{
    delete displayAccountant;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfAccountants::hideGroup()
{
    DataOfWorker<Accountant>::hideGroup();
    this->label("");
    this->displayAccountant->hide();
}
void DataOfAccountants::change(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAccountants *data = (DataOfAccountants*)v->at(0);
    DisplayAccountant *displayAccountant = (DisplayAccountant*)v->at(1);
    AccountantTable *accountantTable = (AccountantTable*)v->at(2);
    Accountant *a = data->array->getRow(data->getCurrent());
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