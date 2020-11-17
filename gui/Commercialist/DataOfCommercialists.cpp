#include "DataOfCommercialists.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../Company/DataOfCompanies.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include <sstream>

using namespace std;

DataOfCommercialists::DataOfCommercialists(int x, int y, int w, int h, ArrayCommercialists *array, void *d, const char *l)
 : DataOfWorker(x , y ,w ,h ,array, d) 
 {
    displayCommercialist = new DisplayCommercialist(x+100, y, 300, 390, "");
    
    btnChange->callback(change, this);
    btnAdd->callback(add, this);
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
    d->setDisplay(d->array->numberOfElement()-1);
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
    Commercialist *a = data->array->getRow(data->getCurrent());
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
    data->table->redraw();
}