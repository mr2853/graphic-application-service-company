#include "DataOfAuditors.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include <sstream>

using namespace std;

DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, ArrayWorkers<Auditor> *array, void *d, const char *l)
 : DataOfWorker(x , y , w, h, array, d, l)
 {
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, "");
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
    updateLabel();
}

DataOfAuditors::~DataOfAuditors()
{
    delete displayAuditor;
}
void DataOfAuditors::add(Fl_Widget *widget, void *data)
{
    DataOfAuditors *d = (DataOfAuditors*)data;
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
    d->setDisplay(d->array->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
void DataOfAuditors::hideGroup()
{
    this->label("");
    this->displayAuditor->hide();
}
void DataOfAuditors::change(Fl_Widget *widget, void *d)
{
    DataOfAuditors *data = (DataOfAuditors*)d;
    Auditor *a = data->array->getRow(data->getCurrent());
    try{
        a->setName(data->displayAuditor->getValueName());
        a->setLastname(data->displayAuditor->getValueLastName());
        a->setSalary(data->displayAuditor->getValueSalary());
        a->setDateBirth(data->displayAuditor->getValueDateBirth());
        a->setDatesVisiting(data->displayAuditor->getDatesVisiting());
        data->table->redraw();
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
}