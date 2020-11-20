#include "DataOfAuditors.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include <sstream>

using namespace std;

DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, ArrayWorkers<Auditor> *original, ArrayWorkers<Auditor> *changed, Company *company, void *d, const char *l)
 : DataOfWorker(x , y ,w ,h , original, changed, company, d, l) 
 {
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, "");
    
    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    if(changed->numberOfElement() != 0){
        this->setDisplay(this->getCurrent());
    }
    this->end();
}

void DataOfAuditors::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        displayAuditor->displayWorker(this->getElement(indeks));
        displayAuditor->setDatesVisiting("");
        string t = "";
        for(int i = 0; i < this->getElement(current)->getNumberOfVisits(); i++)
        {
            t.append(this->getElement(current)->getDateVisiting(i)->getDateWithTime());
            if(this->getElement(current)->getNumberOfVisits()-1 != i){
                t.append(",\n");
            }
        }
        displayAuditor->setDatesVisiting(t);
    }
    this->displaySalary->setCurrent(this->getElement(this->getCurrent())->getSalary());
    this->refreshDisplaySalary();
    updateLabel();
}

DataOfAuditors::~DataOfAuditors()
{
    delete displayAuditor;
}
void DataOfAuditors::add(Fl_Widget *widget, void *data)
{
    DataOfAuditors *d = (DataOfAuditors*)data;
    if(!d->displayAuditor->isInputsEmpty())
    {
        return;
    }
    WorkerTable<Auditor> *auditorTable = d->table;
    Auditor* novaOsoba;
    try{
        novaOsoba = new Auditor(d->displayAuditor->getValueName(), d->displayAuditor->getValueLastName(),
                        d->displayAuditor->getValueDateBirth(), d->displayAuditor->getValueSalary(), d->displayAuditor->getDatesVisiting());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    catch(WrongDateWithTime e)
    {
        fl_message(e.what("Dates visiting"));
        return;
    }
                    
    auditorTable->add(novaOsoba);
    d->setDisplay(d->changed->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
void DataOfAuditors::hideGroup()
{
    DataOfWorker<Auditor>::hideGroup();
    this->label("");
    this->displayAuditor->hide();
}
void DataOfAuditors::change(Fl_Widget *widget, void *d)
{
    DataOfAuditors *data = (DataOfAuditors*)d;
    if(!data->displayAuditor->isInputsEmpty())
    {
        return;
    }
    Auditor *a = data->changed->getRow(data->getCurrent());
    try{
        a->setName(data->displayAuditor->getValueName());
        a->setLastname(data->displayAuditor->getValueLastName());
        a->setSalary(data->displayAuditor->getValueSalary());
        a->setDateBirth(data->displayAuditor->getValueDateBirth());
        a->setDatesVisiting(data->displayAuditor->getDatesVisiting());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return;
    }
    catch(WrongDateWithTime e)
    {
        fl_message(e.what("Dates visiting"));
        return;
    }

    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == data->getCurrent())
            {
                Auditor *a1 = data->original->getRow(i);
                a1->setName(data->displayAuditor->getValueName());
                a1->setLastname(data->displayAuditor->getValueLastName());
                a1->setSalary(data->displayAuditor->getValueSalary());
                a1->setDateBirth(data->displayAuditor->getValueDateBirth());
                a1->setDatesVisiting(data->displayAuditor->getDatesVisiting());
                break;
            }
            counter++;
        }
    }

    data->table->redraw();
}