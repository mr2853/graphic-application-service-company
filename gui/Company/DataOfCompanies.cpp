#include "DataOfCompanies.hpp"
#include "../../Class/Company.hpp"
#include "DisplayCompany.hpp"

#include "../Auditor/DataOfAuditors.hpp"
#include "../Accountant/DataOfAccountants.hpp"
#include "../Commercialist/DataOfCommercialists.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>
#include "../Department/DataOfDepartments.hpp"
#include "../Audit/DataOfAudits.hpp"

using namespace std;

DataOfCompanies::DataOfCompanies(int x, int y, int w, int h, ArrayWorkers<Company*> *original, ArrayWorkers<Company*> *changed, void *data, const char *l)
 : DataOf(x , y ,w ,h , original, changed, data, l){
    
    display = new DisplayCompany(x+50, y, 200, 300, "");
    
    chCompany = new Fl_Choice(x+450, y, 100, 40, "Companies:");
    this->updateChCompany();
    btnDetails = new Fl_Button(x+450, y+50, 150, 50, "Data of Company");
    btnAudits = new Fl_Button(x+450, y+110, 150, 50, "Data of Audits");

    btnDetails->callback(details, this);
    btnChange->callback(change, this);
    btnAdd->callback(add, this);
    btnAudits->callback(audits, this);

    remove(btnGoBack);
    
    if(changed->numberOfElement() != 0){
        this->setDisplay(this->getCurrent());
    }
    this->isCompaniesEmpty();
    this->end();
}

void DataOfCompanies::updateChCompany(){
    string depart = "";
    chCompany->clear();
    for(int i = 0; i < this->sizeOfArray(); i++)
    {
        string s = to_string(i+1).append(".").append(this->getElement(i)->getName());
        depart.append(s);
        depart.append("|");
    }
    chCompany->add(depart.c_str());
    chCompany->redraw();
    chCompany->value(0);
}

void DataOfCompanies::setDisplay(int indeks)
{
    if (indeks >= 0 && indeks < this->sizeOfArray())
    {
        current = indeks;
        display->setName(this->getElement(indeks)->getName().c_str());
        display->setTaxIdentificationNumber(this->getElement(indeks)->getTaxIdentificationNumber().c_str());
        display->setIdentificationNumber(this->getElement(indeks)->getIdentificationNumber().c_str());
    }
    updateLabel();
}

void DataOfCompanies::isCompaniesEmpty()
{
    this->isArrayEmpty();
    if(this->sizeOfArray() == 0){
        btnChange->deactivate();
        btnDetails->deactivate();
        btnAudits->deactivate();
    }
    else
    {
        btnChange->activate();
        btnDetails->activate();
        btnAudits->activate();
    }
}
void DataOfCompanies::change(Fl_Widget *widget, void *d)
{
    DataOfCompanies *data = (DataOfCompanies*)d;
    if(!data->display->isInputsEmpty())
    {
        return;
    }
    Company *dep = data->changed->getRow(data->getCurrent());

    dep->setName(data->display->getName());
    dep->setTaxIdentificationNumber(data->display->getTaxIdentificationNumber());
    dep->setIdentificationNumber(data->display->getIdentificationNumber());

    int counter = 0;
    for(int i = 0; i < data->original->numberOfElement(); i++)
    {
        if(!data->original->getElement(i)->isDeleted())
        {
            if(counter == data->getCurrent())
            {
                Company *dep1 = data->original->getRow(i);
                dep1->setName(data->display->getName());
                dep1->setTaxIdentificationNumber(data->display->getTaxIdentificationNumber());
                dep1->setIdentificationNumber(data->display->getIdentificationNumber());
                break;
            }
            counter++;
        }
    }
    data->table->redraw();
    data->updateChCompany();
}

void DataOfCompanies::hideGroup(){
    DataOf<Company*>::hideGroup();
    this->label("");
    this->display->hideGroup();

    this->btnDetails->hide();
    this->btnChange->hide();
    this->btnAdd->hide();
    this->btnAudits->hide();

    this->chCompany->hide();
}
void DataOfCompanies::unhideGroup(){
    DataOf<Company*>::unhideGroup();
    this->redraw_label();
    this->updateLabel();
    this->display->unhide();

    this->btnDetails->show();
    this->btnChange->show();
    this->btnAdd->show();
    this->btnAudits->show();
    
    this->chCompany->show();
}
void DataOfCompanies::details(Fl_Widget *widget, void *d)
{
    DataOfCompanies *data = (DataOfCompanies*)d;
    int intDep = data->chCompany->value();
    Company *company1;
    int counter = 0;
    cout << "ovde" << endl;
    for(int j = 0; j < data->original->numberOfElement(); j++)
    {
        if(!data->original->getElement(j)->isDeleted())
        {
            if(counter == intDep)
            {
                company1 = data->original->getElement(j);
            }
            counter++;
        }
    }
    cout << "ovde1" << endl;
    Company *company2 = data->changed->getElement(intDep);
    cout << "ovde2" << endl;
    
    DataOfDepartments *dataOfDepartments = new DataOfDepartments(data->x(),
                    data->y(), data->w(), data->h(), new ArrayWorkers<Department*>(company1->getDepartments()),
                     new ArrayWorkers<Department*>(company2->getDepartments()), data);
    cout << "ovde3" << endl;

    data->hideGroup();
    cout << "ovde4" << endl;
    data->Fl_Group::add(dataOfDepartments);
    cout << "ovde5" << endl;
}
void DataOfCompanies::audits(Fl_Widget *widget, void *d)
{
    DataOfCompanies *data = (DataOfCompanies*)d;
    int intDep = data->chCompany->value();
    Company *company1;
    int counter = 0;
    for(int j = 0; j < data->original->numberOfElement(); j++)
    {
        if(!data->original->getElement(j)->isDeleted())
        {
            if(counter == intDep)
            {
                company1 = data->original->getElement(j);
                break;
            }
            counter++;
        }
    }
    Company *company2 = data->changed->getElement(intDep);
    cout << "pocetak" << endl;
    vector<Audit*>* audits1 = new vector<Audit*>();
    for(int i = 0; i < company1->getDepartments()->size(); i++)
    {
        if(company1->getDepartments()->at(i)->isDeleted())
        {
            continue;
        }
        for(int j = 0; j < company1->getDepartments()->at(i)->getAudits()->size(); j++)
        {
            if(company1->getDepartments()->at(i)->getAudits()->at(j)->isDeleted())
            {
                continue;
            }
            audits1->push_back(company1->getDepartments()->at(i)->getAudits()->at(j));
        }
    }

    vector<Audit*>* audits2 = new vector<Audit*>();
    for(int i = 0; i < company2->getDepartments()->size(); i++)
    {
        for(int j = 0; j < company2->getDepartments()->at(i)->getAudits()->size(); j++)
        {
            audits2->push_back(company2->getDepartments()->at(i)->getAudits()->at(j));
        }
    }

    DataOfAudits *dataOfAudits = new DataOfAudits(data->x(), data->y(), data->w(), data->h(), 
        new ArrayWorkers<Audit*>(audits1), new ArrayWorkers<Audit*>(audits2),
         new ArrayWorkers<Department*>(company1->getDepartments()), new ArrayWorkers<Department*>(company2->getDepartments()), data);
    cout << "krajj" << endl;
    data->hideGroup();
    data->Fl_Group::add(dataOfAudits);
}


DataOfCompanies::~DataOfCompanies(){}

void DataOfCompanies::add(Fl_Widget *widget, void *data)
{
    DataOfCompanies *d = (DataOfCompanies*)data;
    if(!d->display->isInputsEmpty())
    {
        return;
    }
    // Company *company = new Company(d->display->getName(),d->display->getTaxIdentificationNumber(),d->display->getIdentificationNumber());
    d->table->add(new Company(d->display->getName(),d->display->getTaxIdentificationNumber(),d->display->getIdentificationNumber()));
    d->original->add(new Company(d->display->getName(),d->display->getTaxIdentificationNumber(),d->display->getIdentificationNumber()));
    d->updateChCompany();
    d->setDisplay(d->changed->numberOfElement()-1);
    d->updateLabel();
    d->isCompaniesEmpty();
    d->checkButtons();
}