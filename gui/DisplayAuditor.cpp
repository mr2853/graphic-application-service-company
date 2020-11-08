#include "DisplayAuditor.hpp"
#include "DataOfAuditors.hpp"
#include "../Util.hpp"

DisplayAuditor::DisplayAuditor(int x, int y, int w, int h, ArrayAuditors *auditors, void* data, const char *l=0)
: DisplayWorker(x, y, w, h, l), auditors(auditors)
{
    if(this->auditors->numberOfElement() != 0)
    {
        DataOfAuditors *d = (DataOfAuditors*)data;
        displayWorker = new DisplayWorker(x, y, 200, 190, "");
        datesVisiting = new Fl_Multiline_Input(x, y+200, 200, 70, "Dates visiting:");
        btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");
    
        /*for(int i = 0; i < auditors->getElement(0)->getNumberOfVisits(); i++)
        {
            datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
        }*/
        btnPrevious = new Fl_Button(x+220, y, 45, 70, "@<-");
        btnNext = new Fl_Button(x + 270, y, 45, 70, "@->");

        vector<Fl_Widget*> *widgets = new vector<Fl_Widget*>();
        widgets->push_back(displayWorker);
        widgets->push_back(datesVisiting);
        widgets->push_back(this);
        widgets->push_back(d);

        btnNext->callback(nextElement, this);
        btnPrevious->callback(previousElement, this);
        btnAdd->callback(add, widgets);

        auditors->subscribeListener(this);
    }
    this->end();
}
DisplayAuditor::~DisplayAuditor(){}
void DisplayAuditor::updateLabel()
{
    stringstream sstream;
    sstream << "Osoba " << current + 1 << "/" << auditors->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DisplayAuditor::checkButtons()
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

void DisplayAuditor::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < auditors->numberOfElement())
    {
        current = indeks;
        displayWorker->displayWorker(auditors->getElement(indeks));
        datesVisiting->value("");
        for(int i = 0; i < auditors->getElement(0)->getNumberOfVisits(); i++)
        {
            datesVisiting->insert(auditors->getElement(0)->getDateVisiting(i)->getDateWithTime().c_str());
        }
    }
    updateLabel();
}

void DisplayAuditor::nextElement(Fl_Widget *widget, void *data){
    DisplayAuditor *displayAuditor = (DisplayAuditor *) data;
    if (displayAuditor->current + 1 < displayAuditor->auditors->numberOfElement())
    {
        displayAuditor->current++;
        displayAuditor->setDisplay(displayAuditor->current);
    }

    displayAuditor->checkButtons();
}

void DisplayAuditor::previousElement(Fl_Widget *widget, void *data)
{
    DisplayAuditor *displayAuditor = (DisplayAuditor *) data;
    if (displayAuditor->current - 1 >= 0)
    {
        displayAuditor->current--;
        displayAuditor->setDisplay(displayAuditor->current);
    }

    displayAuditor->checkButtons();
}

void DisplayAuditor::elementPushed(int indeks, Auditor *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DisplayAuditor::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
/*void DisplayAuditor::displayAuditor(Auditor *auditor)
{
    cout << "displayAuditor ovde" <<endl;
    //this->auditor = auditor;
    cout << "displayAuditor ovde1" <<endl;
    displayWorker->displayWorker(auditor);
    cout << "displayAuditor ovde2" <<endl;
    datesVisiting->value("");
    for(int i = 0; i < auditor->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }
    cout << "displayAuditor ovde3" <<endl;
}*/

vector<Date*>* DisplayAuditor::getDatesVisiting(){
    string t = datesVisiting->value();
    vector<Date*> *dates = new vector<Date*>();
    int index;

    while(t.find(",")){
        index = t.find(",");
        string subs = t.substr(0, index);
        vector<int> d = getDate(subs);
        t.erase(0, index + 1);
        dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
    }

    vector<int> d = getDate(t);
    t.erase(0, index + 1);
    dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
    
    return dates;
}
/*struct Event
{
    ArrayAuditors *auditors;
    AuditorTable *tabela;
    DisplayAuditor *displayAuditor;
};*/
void DisplayAuditor::add(Fl_Widget *widget, void *data)
{
    vector<Fl_Widget*> *widgets = (vector<Fl_Widget*>*)data;
    DisplayWorker *displayWorker = (DisplayWorker*)widgets->at(0);
    Fl_Multiline_Input *datesVisiting = (Fl_Multiline_Input*)widgets->at(1);
    DisplayAuditor *displayAuditor = (DisplayAuditor*)widgets->at(2);
    DataOfAuditors *d = (DataOfAuditors*)widgets->at(3);
    AuditorTable *auditorTable = d->getAuditorTable();

    Auditor *novaOsoba = new Auditor(displayWorker->getValueName(), displayWorker->getValueLastName(),
                    displayWorker->getValueDateBirth(), stod(displayWorker->getValueSalary()), displayAuditor->getDatesVisiting());
                    
    //displayAuditor->auditors->add(novaOsoba);
    auditorTable->add(novaOsoba);
    // cout << "numb of elem: " << d->numberOfAuditors() << endl;
    // d->addAuditor(novaOsoba);
    // cout << "numb of elem1: " << d->numberOfAuditors() << endl;
}