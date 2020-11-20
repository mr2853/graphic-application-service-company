#include "DataOfCommercialists.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../Company/DataOfCompanies.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include <sstream>

using namespace std;

DataOfCommercialists::DataOfCommercialists(int x, int y, int w, int h, ArrayCommercialists *original, ArrayCommercialists *changed, Company *company, void *d, const char *l)
 : DataOfWorker(x , y ,w ,h , original, changed, company, d, l) 
 {
    displayCommercialist = new DisplayCommercialist(x+100, y, 300, 390, "");
    btnPrevious->position(x+310,y);
    btnNext->position(x+390,y);
    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    if(changed->numberOfElement() != 0){
        this->setDisplay(this->getCurrent());
    }
    this->end();
 }

void DataOfCommercialists::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        displayCommercialist->displayWorker(this->getElement(indeks));
        displayCommercialist->setBusinessContact("");
        string t = "";
        for(int i = 0; i < this->getElement(current)->getNumberOfBusinessContact(); i++)
        {
            t.append((*this->getElement(current)->getContact(i)));
            if(this->getElement(current)->getNumberOfBusinessContact()-1 != i){
                t.append(",\n");
            }
        }
        displayCommercialist->setBusinessContact(t);
    }
    this->displaySalary->setCurrent(this->getElement(this->getCurrent())->getSalary());
    this->refreshDisplaySalary();
    updateLabel();
}

DataOfCommercialists::~DataOfCommercialists()
{
    delete displayCommercialist;
}
void DataOfCommercialists::add(Fl_Widget *widget, void *data)
{
    DataOfCommercialists *d = (DataOfCommercialists*)data;
    if(!d->displayCommercialist->isInputsEmpty())
    {
        return;
    }
    WorkerTable<Commercialist> *table = d->table;
    Commercialist *novaOsoba;
    try{
        novaOsoba = new Commercialist(d->displayCommercialist->getValueName(), d->displayCommercialist->getValueLastName(),
                        d->displayCommercialist->getValueDateBirth(), d->displayCommercialist->getValueSalary());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    
    novaOsoba->setBusinessContact(d->displayCommercialist->getBusinessContacts());                
    table->add(novaOsoba);
    d->setDisplay(d->changed->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
void DataOfCommercialists::hideGroup()
{
    DataOfWorker<Commercialist>::hideGroup();
    this->label("");
    this->displayCommercialist->hide();
}
void DataOfCommercialists::change(Fl_Widget *widget, void *d)
{
    DataOfCommercialists *data = (DataOfCommercialists*)d;
    if(!data->displayCommercialist->isInputsEmpty())
    {
        return;
    }
    Commercialist *a = data->changed->getRow(data->getCurrent());
    try{
        a->setName(data->displayCommercialist->getValueName());
        a->setLastname(data->displayCommercialist->getValueLastName());
        a->setSalary(data->displayCommercialist->getValueSalary());
        a->setDateBirth(data->displayCommercialist->getValueDateBirth());
        a->setBusinessContact(data->displayCommercialist->getBusinessContacts());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }

    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == data->getCurrent())
            {
                Commercialist *a1 = data->original->getRow(i);
                a1->setName(data->displayCommercialist->getValueName());
                a1->setLastname(data->displayCommercialist->getValueLastName());
                a1->setSalary(data->displayCommercialist->getValueSalary());
                a1->setDateBirth(data->displayCommercialist->getValueDateBirth());
                a1->setBusinessContact(data->displayCommercialist->getBusinessContacts());
                break;
            }
            counter++;
        }
    }
    data->table->redraw();
}