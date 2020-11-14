#include "DisplayAccountant.hpp"
#include "DataOfAccountants.hpp"

DisplayAccountant::DisplayAccountant(int x, int y, int w, int h, ArrayAccountants *accountants, void* data, const char *l)
: DisplayWorker(x, y, 200, 190, ""), accountants(accountants)
{
    bodyIssuedPermit = new Fl_Input(x, y+200, 100, 40, "Issued Permit:");
    maxAmountCompanyIncome = new Fl_Input(x, y+280, 100, 40, "Max Income:");
    btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");

    /*for(int i = 0; i < accountants->getElement(0)->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }*/
    btnPrevious = new Fl_Button(x+220, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x + 270, y, 45, 70, "@->");

    vector<Fl_Widget*> *widgets = new vector<Fl_Widget*>();
    widgets->push_back(this);
    widgets->push_back((DataOfAccountants*)data);

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);
    btnAdd->callback(add, widgets);

    if(accountants->numberOfElement() != 0){
        this->setDisplay(current);
    }
    this->checkButtons();

    accountants->subscribeListener(this);
    this->end();
}
DisplayAccountant::DisplayAccountant(int x, int y, int w, int h, ArrayAccountants *accountants, const char *l)
: DisplayWorker(x, y, 200, 190, ""), accountants(accountants)
{
    bodyIssuedPermit = new Fl_Input(x, y+200, 100, 40, "Issued Permit:");
    maxAmountCompanyIncome = new Fl_Input(x, y+280, 100, 40, "Max Income:");
    btnAdd = new Fl_Button(x+250, y+300, 70, 30, "Add");

    /*for(int i = 0; i < accountants->getElement(0)->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }*/
    btnPrevious = new Fl_Button(x+220, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x + 270, y, 45, 70, "@->");

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);

    if(accountants->numberOfElement() != 0){
        this->setDisplay(current);
    }
    this->checkButtons();

    accountants->subscribeListener(this);
    this->end();
}
string DisplayAccountant::getType()
{
    return "DisplayAccountant";
}
DisplayAccountant::~DisplayAccountant()
{
    delete bodyIssuedPermit;
    delete maxAmountCompanyIncome;
    delete btnAdd;
    delete btnPrevious;
    delete btnNext;
}
void DisplayAccountant::hide()
{
    this->label("");
    DisplayWorker::hide();
    this->bodyIssuedPermit->hide();
    this->maxAmountCompanyIncome->hide();
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
}
void DisplayAccountant::unhide()
{
    DisplayWorker::unhide();
    this->bodyIssuedPermit->show();
    this->maxAmountCompanyIncome->show();
    this->btnNext->show();
    this->btnPrevious->show();
    this->btnAdd->show();
}
void DisplayAccountant::updateLabel()
{
    stringstream sstream;
    sstream << "Accountant " << current + 1 << "/" << accountants->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

void DisplayAccountant::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= accountants->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

void DisplayAccountant::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < accountants->numberOfElement())
    {
        current = indeks;
        this->displayWorker(accountants->getElement(indeks));
        bodyIssuedPermit = new Fl_Input(this->x(), this->y()+200, 200, 70, "Issued Permit:");
        maxAmountCompanyIncome = new Fl_Input(this->x(), this->y()+280, 200, 70, "Max Income:");
        this->bodyIssuedPermit->value(accountants->getElement(indeks)->getBodyIssuedPermit().c_str());
        this->maxAmountCompanyIncome->value(to_string(accountants->getElement(indeks)->getMaxAmountCompanyIncome()).c_str());
    }
    updateLabel();
}

void DisplayAccountant::nextElement(Fl_Widget *widget, void *data){
    DisplayAccountant *displayAccountant = (DisplayAccountant *) data;
    if (displayAccountant->current + 1 < displayAccountant->accountants->numberOfElement())
    {
        displayAccountant->current++;
        displayAccountant->setDisplay(displayAccountant->current);
    }

    displayAccountant->checkButtons();
}

void DisplayAccountant::previousElement(Fl_Widget *widget, void *data)
{
    DisplayAccountant *displayAccountant = (DisplayAccountant *) data;
    if (displayAccountant->current - 1 >= 0)
    {
        displayAccountant->current--;
        displayAccountant->setDisplay(displayAccountant->current);
    }

    displayAccountant->checkButtons();
}

void DisplayAccountant::elementPushed(int indeks, Accountant *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}
void DisplayAccountant::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}
int DisplayAccountant::getCurrent()
{
    return current;
}
/*void DisplayAccountant::displayAccountant(Accountant *auditor)
{
    cout << "displayAccountant ovde" <<endl;
    //this->auditor = auditor;
    cout << "displayAccountant ovde1" <<endl;
    displayWorker->displayWorker(auditor);
    cout << "displayAccountant ovde2" <<endl;
    datesVisiting->value("");
    for(int i = 0; i < auditor->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }
    cout << "displayAccountant ovde3" <<endl;
}*/


string DisplayAccountant::getBodyIssuedPermit()
{
    return bodyIssuedPermit->value();
}
string DisplayAccountant::getMaxAmountCompanyIncome()
{
    return maxAmountCompanyIncome->value();
}

void DisplayAccountant::add(Fl_Widget *widget, void *data)
{
    vector<Fl_Widget*> *widgets = (vector<Fl_Widget*>*)data;
    DisplayAccountant *displayAccountant = (DisplayAccountant*)widgets->at(0);
    DataOfAccountants *d = (DataOfAccountants*)widgets->at(1);
    AccountantTable *accountantTable = d->getAccountantTable();
    
    Accountant *novaOsoba = new Accountant(displayAccountant->getValueName(), displayAccountant->getValueLastName(),
                    displayAccountant->getValueDateBirth(), stod(displayAccountant->getValueSalary()),
                     displayAccountant->bodyIssuedPermit->value(), stod(displayAccountant->maxAmountCompanyIncome->value()));
                    
    accountantTable->add(novaOsoba);
}
// void DisplayAccountant::displayWorker(Accountant *worker)
// {
//     //this->worker = worker;
//     DisplayWorker::displayWorker(worker);
//     // datesVisiting = new Fl_Multiline_Input(x, y+200, 200, 70, "Dates visiting:");
//     datesVisiting->value("");
//     for(int i = 0; i < worker->getNumberOfVisits(); i++){
//         datesVisiting->insert(worker->getDateVisiting(i)->getDateWithTime().c_str());
//         datesVisiting->insert(",\n");
//     }
// }