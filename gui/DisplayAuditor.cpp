#include "DisplayAuditor.hpp"
DisplayAuditor::DisplayAuditor(int x, int y, int w, int h, AbstractModel<Auditor *> *auditors, const char *l=0)
: Fl_Group(x, y, w, h, l), auditors(auditors)
{
    if(this->auditors->numberOfElement() != 0)
    {
        displayWorker = new DisplayWorker(x, y, 200, 40, "");
        datesVisiting = new Fl_Multiline_Input(x, y+200, 200, 70, "Dates visiting:");
    
        /*for(int i = 0; i < auditors->getElement(0)->getNumberOfVisits(); i++)
        {
            datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
        }*/
        btnPrevious = new Fl_Button(x, y, 45, 70, "@<-");
        btnNext = new Fl_Button(x + 255, y, 45, 70, "@->");

        btnNext->callback(nextElement, this);
        btnPrevious->callback(previousElement, this);

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
            datesVisiting->insert(auditors->getElement(indeks)->getDateVisiting(i)->getDateWithTime().c_str());
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

vector<Date*> DisplayWorker::getDatesVisiting()
{
    string t = datesVisiting->value();

    int index = t.find("-");
    int hour = stoi(t.substr(0, index));
    t.erase(0, index);

    index = t.find("-");
    int minute = stoi(t.substr(0, index));
    t.erase(0, index);

    index = t.find("-");
    int day = stoi(t.substr(0, index));
    t.erase(0, index);

    index = t.find("-");
    int month = stoi(t.substr(0, index));
    t.erase(0, index);

    index = t.find("-");
    int year = stoi(t.substr(0, index));
    t.erase(0, index);

    Date *d = new Date(hour, minute, day, month, year);
    return d;
}
void DisplayAuditor::addAuditor(Fl_Widget *widget, void *data)
{
    DisplayAuditor *forma = (DisplayAuditor *) data;
    Auditor *novaOsoba;
    novaOsoba = new Auditor(forma->displayWorker->getValueName(), forma->displayWorker->getValueLastName(),
                    forma->displayWorker->getValueDateBirth(), stod(forma->displayWorker->getValueSalary()), forma->datesVisiting->value());
    forma->auditors->pushElement(forma->auditors->numberOfElement(), novaOsoba);
}
