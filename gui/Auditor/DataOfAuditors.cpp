#include "DataOfAuditors.hpp"
#include "../Department/DataOfDepartments.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include <sstream>

using namespace std;

/*struct Event
{
    ArrayAuditors *auditors;
    AuditorTable *tabela;
    DisplayAuditor *displayAuditor;
};*/
AuditorTable* DataOfAuditors::getAuditorTable()
{
    return auditorTable;
}
void DataOfAuditors::addAuditor(Auditor* a)
{
    auditors->add(a);
}
int DataOfAuditors::numberOfAuditors()
{
    return auditors->numberOfElement();
}
void DataOfAuditors::isArrayEmpty()
{
    if(auditors->numberOfElement() == 0)
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
DataOfAuditors::DataOfAuditors(int x, int y, int w, int h, ArrayAuditors *auditors, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), auditors(auditors)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);
    displayAuditor = new DisplayAuditor(x+50, y, 300, 390, "");
    auditorTable = new AuditorTable(x+200, y+340, 400, 280, auditors);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+300, y+300, 70, 30, "Add");
    btnRemove = new Fl_Button(x+380, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");
    btnPrevious = new Fl_Button(x+170, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+220, y, 45, 70, "@->");

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);

    btnAdd->callback(add, this);
    //btnView->callback(DataOfAuditors::view, ev);
    btnRemove->callback(DataOfAuditors::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfAuditors::goBack, v);
    
    btnChange->callback(change, this);

    if(auditors->numberOfElement() != 0){
        this->setDisplay(current);
    }
    
    auditors->subscribeListener(this);
    this->isArrayEmpty();
    this->checkButtons();
    this->end();
}
void DataOfAuditors::updateLabel()
{
    stringstream sstream;
    sstream << "Auditor " << current + 1 << "/" << auditors->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DataOfAuditors::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= auditors->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

void DataOfAuditors::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < auditors->numberOfElement())
    {
        current = indeks;
        displayAuditor->displayWorker(auditors->getElement(indeks));
        displayAuditor->setDatesVisiting("");
        string t = "";
        for(int i = 0; i < auditors->getElement(current)->getNumberOfVisits(); i++)
        {
            t.append(auditors->getElement(current)->getDateVisiting(i)->getDateWithTime());
            if(auditors->getElement(current)->getNumberOfVisits()-1 != i){
                t.append(",\n");
            }
        }
        displayAuditor->setDatesVisiting(t);
    }
    updateLabel();
}

void DataOfAuditors::nextElement(Fl_Widget *widget, void *d){
    DataOfAuditors *data = (DataOfAuditors *) d;
    if (data->current + 1 < data->auditors->numberOfElement())
    {
        data->current++;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfAuditors::previousElement(Fl_Widget *widget, void *d)
{
    DataOfAuditors *data = (DataOfAuditors *) d;
    if (data->current - 1 >= 0)
    {
        data->current--;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfAuditors::elementPushed(int indeks, Auditor *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DataOfAuditors::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DataOfAuditors::getCurrent()
{
    return current;
}
DataOfAuditors::~DataOfAuditors()
{
    delete displayAuditor;
    delete auditorTable;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfAuditors::add(Fl_Widget *widget, void *data)
{
    DataOfAuditors *d = (DataOfAuditors*)data;
    AuditorTable *auditorTable = d->getAuditorTable();
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
    d->setDisplay(d->auditors->numberOfElement()-1);
    d->updateLabel();
    d->isArrayEmpty();
    d->checkButtons();
}
void DataOfAuditors::hideGroup()
{
    this->label("");
    this->displayAuditor->hide();
    this->auditorTable->hide();

    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
}
void DataOfAuditors::change(Fl_Widget *widget, void *d)
{
    DataOfAuditors *data = (DataOfAuditors*)d;
    Auditor *a = data->auditors->getRow(data->getCurrent());
    try{
        a->setName(data->displayAuditor->getValueName());
        a->setLastname(data->displayAuditor->getValueLastName());
        a->setSalary(data->displayAuditor->getValueSalary());
        a->setDateBirth(data->displayAuditor->getValueDateBirth());
        a->setDatesVisiting(data->displayAuditor->getDatesVisiting());
        data->auditorTable->redraw();
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
void DataOfAuditors::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfAuditors *data = (DataOfAuditors*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

/*void DataOfAuditors::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayAuditor->displayAuditor(event->auditors->getElement(endRow));
}*/

void DataOfAuditors::removeElem(Fl_Widget *widget, void *data)
{
    DataOfAuditors *e = (DataOfAuditors *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->auditorTable->get_selection(startRow, colLeft, endRow, colRight);
    for (int i = endRow; i >= startRow; i--)
    {
        e->auditors->removeRow(i);
    }
    if(e->auditors->numberOfElement() == 0){
        e->setDisplay(0);
    }
    else{
        e->setDisplay(e->auditors->numberOfElement()-1);
    }
    e->updateLabel();
    e->isArrayEmpty();
    e->checkButtons();
}

// Company& DataOfAuditors::getCompany()
// {
//     return company;
// }
void DataOfAuditors::refreshTable()
{
    auditorTable->refreshTable();
}
