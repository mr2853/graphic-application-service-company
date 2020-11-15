#include "DataOfCommercialists.hpp"
#include "../Department/DataOfDepartments.hpp"
#include <sstream>

using namespace std;

/*struct Event
{
    ArrayCommercialists *commercialists;
    CommercialistTable *tabela;
    DisplayCommercialist *displayCommercialist;
};*/
CommercialistTable* DataOfCommercialists::getCommercialistTable()
{
    return commercialistTable;
}
void DataOfCommercialists::addCommercialist(Commercialist* a)
{
    commercialists->add(a);
}
int DataOfCommercialists::numberOfCommercialists()
{
    return commercialists->numberOfElement();
}

DataOfCommercialists::DataOfCommercialists(int x, int y, int w, int h, ArrayCommercialists *commercialists, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), commercialists(commercialists)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);
    displayCommercialist = new DisplayCommercialist(x+50, y, 300, 390, "");
    commercialistTable = new CommercialistTable(x+200, y+340, 400, 280, commercialists);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+300, y+300, 70, 30, "Add");
    btnRemove = new Fl_Button(x+380, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");
    btnPrevious = new Fl_Button(x+170, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+220, y, 45, 70, "@->");

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);

    btnAdd->callback(add, this);
    //btnView->callback(DataOfCommercialists::view, ev);
    btnRemove->callback(DataOfCommercialists::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfCommercialists::goBack, v);
    
    btnChange->callback(change, this);

    if(commercialists->numberOfElement() != 0){
        this->setDisplay(current);
    }
    this->checkButtons();
    
    commercialists->subscribeListener(this);
    this->end();
}
void DataOfCommercialists::updateLabel()
{
    stringstream sstream;
    sstream << "Commercialist " << current + 1 << "/" << commercialists->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DataOfCommercialists::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= commercialists->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

void DataOfCommercialists::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < commercialists->numberOfElement())
    {
        current = indeks;
        displayCommercialist->displayWorker(commercialists->getElement(indeks));
        displayCommercialist->setBusinessContact("");
        string t = "";
        for(int i = 0; i < commercialists->getElement(current)->getNumberOfBusinessContact(); i++)
        {
            t.append((*commercialists->getElement(current)->getContact(i)));
            if(commercialists->getElement(current)->getNumberOfBusinessContact()-1 != i){
                t.append(",\n");
            }
        }
        displayCommercialist->setBusinessContact(t);
    }
    updateLabel();
}

void DataOfCommercialists::nextElement(Fl_Widget *widget, void *d){
    DataOfCommercialists *data = (DataOfCommercialists *) d;
    if (data->current + 1 < data->commercialists->numberOfElement())
    {
        data->current++;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfCommercialists::previousElement(Fl_Widget *widget, void *d)
{
    DataOfCommercialists *data = (DataOfCommercialists *) d;
    if (data->current - 1 >= 0)
    {
        data->current--;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

void DataOfCommercialists::elementPushed(int indeks, Commercialist *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DataOfCommercialists::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DataOfCommercialists::getCurrent()
{
    return current;
}
DataOfCommercialists::~DataOfCommercialists()
{
    delete displayCommercialist;
    delete commercialistTable;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfCommercialists::add(Fl_Widget *widget, void *data)
{
    DataOfCommercialists *d = (DataOfCommercialists*)data;
    CommercialistTable *commercialistTable = d->getCommercialistTable();

    Commercialist *novaOsoba = new Commercialist(d->displayCommercialist->getValueName(), d->displayCommercialist->getValueLastName(),
                    d->displayCommercialist->getValueDateBirth(), stod(d->displayCommercialist->getValueSalary()));
    
    novaOsoba->setBusinessContact(d->displayCommercialist->getBusinessContacts());                
    commercialistTable->add(novaOsoba);
    d->setDisplay(d->commercialists->numberOfElement()-1);
    d->checkButtons();
    d->updateLabel();
}
void DataOfCommercialists::hideGroup()
{
    this->label("");
    this->displayCommercialist->hide();
    this->commercialistTable->hide();

    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
}
void DataOfCommercialists::change(Fl_Widget *widget, void *d)
{
    DataOfCommercialists *data = (DataOfCommercialists*)d;
    Commercialist *a = data->commercialists->getRow(data->getCurrent());
    a->setName(data->displayCommercialist->getValueName());
    a->setLastname(data->displayCommercialist->getValueLastName());
    a->setSalary(stod(data->displayCommercialist->getValueSalary()));
    a->setDateBirth(data->displayCommercialist->getValueDateBirth());
    a->setBusinessContact(data->displayCommercialist->getBusinessContacts());
    data->commercialistTable->redraw();
}
void DataOfCommercialists::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfCommercialists *data = (DataOfCommercialists*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

/*void DataOfCommercialists::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayCommercialist->displayCommercialist(event->commercialists->getElement(endRow));
}*/

void DataOfCommercialists::removeElem(Fl_Widget *widget, void *data)
{
    DataOfCommercialists *e = (DataOfCommercialists *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->commercialistTable->get_selection(startRow, colLeft, endRow, colRight);
    for (int i = endRow; i >= startRow; i--)
    {
        e->commercialists->removeRow(i);
    }
    if(e->commercialists->numberOfElement() == 0){
        e->setDisplay(0);
    }
    else{
        e->setDisplay(e->commercialists->numberOfElement()-1);
    }
    e->checkButtons();
    e->updateLabel();
}

// Company& DataOfCommercialists::getCompany()
// {
//     return company;
// }
void DataOfCommercialists::refreshTable()
{
    commercialistTable->refreshTable();
}
