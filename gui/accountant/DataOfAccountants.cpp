#include "DataOfAccountants.hpp"
#include "../../Class/Accountant.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../../Util.hpp"
#include <sstream>
#include <FL/fl_message.H>

using namespace std;


DataOfAccountants::DataOfAccountants(int x, int y, int w, int h, Array<Accountant*> *original, Array<Accountant*> *changed, Company *company, void *d, const char *l)
 : DataOfWorker(x , y ,w ,h , original, changed, company, d, l) 
 {
    displayAccountant = new DisplayAccountant(x+50, y, 300, 390, "");
    
    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    if(changed->numberOfElement() != 0){
        this->setDisplay(this->getCurrent());
    }
    this->checkButtons();
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
    this->displaySalary->setCurrent(this->getElement(this->getCurrent())->getSalary());
    this->refreshDisplaySalary();
    updateLabel();
}

void DataOfAccountants::add(Fl_Widget *widget, void *data)
{
    DataOfAccountants *d = (DataOfAccountants*)data;
    if(!d->displayAccountant->isInputsEmpty())
    {
        return;
    }
    
    try{
        d->table->add(new Accountant(d->displayAccountant->getValueName(), d->displayAccountant->getValueLastName(),
                        d->displayAccountant->getValueDateBirth(), d->displayAccountant->getValueSalary(),
                        d->displayAccountant->getBodyIssuedPermit(), d->displayAccountant->getMaxAmountCompanyIncome()));

        d->original->add(new Accountant(d->displayAccountant->getValueName(), d->displayAccountant->getValueLastName(),
                        d->displayAccountant->getValueDateBirth(), d->displayAccountant->getValueSalary(),
                        d->displayAccountant->getBodyIssuedPermit(), d->displayAccountant->getMaxAmountCompanyIncome()));
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }

    d->setDisplay(d->changed->numberOfElement()-1);
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
    DataOfWorker<Accountant*>::hideGroup();
    this->label("");
    this->displayAccountant->hide();
}
void DataOfAccountants::change(Fl_Widget *widget, void *d)
{
    DataOfAccountants *data = (DataOfAccountants*)d;
    if(!data->displayAccountant->isInputsEmpty())
    {
        return;
    }
    Accountant *a = data->changed->getRow(data->getCurrent());
    try{
        a->setName(data->displayAccountant->getValueName());
        a->setLastname(data->displayAccountant->getValueLastName());
        a->setSalary(data->displayAccountant->getValueSalary());
        a->setDateBirth(data->displayAccountant->getValueDateBirth());
        a->setBodyIssuedPermit(data->displayAccountant->getBodyIssuedPermit());
        a->setMaxAmountCompanyIncome(data->displayAccountant->getMaxAmountCompanyIncome());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    catch(InputContainsForbiddenCharacter e)
    {
        fl_message(e.what());
        return;
    }
    
    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == data->getCurrent())
            {
                Accountant *a1 = data->original->getRow(i);
                a1->setName(data->displayAccountant->getValueName());
                a1->setLastname(data->displayAccountant->getValueLastName());
                a1->setSalary(data->displayAccountant->getValueSalary());
                a1->setDateBirth(data->displayAccountant->getValueDateBirth());
                a1->setBodyIssuedPermit(data->displayAccountant->getBodyIssuedPermit());
                a1->setMaxAmountCompanyIncome(data->displayAccountant->getMaxAmountCompanyIncome());
                break;
            }
            counter++;
        }
    }

    data->table->redraw();
    data->displaySalary->refresh();
}