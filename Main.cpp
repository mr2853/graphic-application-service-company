#include <iostream>
#include <FL/Fl_Window.H>
#include <FL/Fl.H>

#include "Util.hpp"
#include "Class/AbstractPerson.hpp"
#include "Class/Accountant.hpp"
#include "Class/AbstractWorker.hpp"
#include "Class/Audit.hpp"
#include "Class/Auditor.hpp"
#include "Class/Commercialist.hpp"
#include "Class/Department.hpp"
#include "Class/Date.hpp"
#include "Class/Company.hpp"
#include "gui/Company/DataOfCompanies.hpp"
#include "gui/Company/ArrayCompanies.hpp"

using namespace std;

int main()
{
    Company *company = new Company();
    company->readData1("podaci.txt");
    vector<Company*>* companies = new vector<Company*>();
    companies->push_back(company);
    ArrayCompanies *array = new ArrayCompanies(companies);
    Fl_Window *window = new Fl_Window(900, 700, "Projekat");
    DataOfCompanies *dataOfCompanies = new DataOfCompanies(50, 50, 900, 700, array, window, "");
    window->resizable(dataOfCompanies);
    window->end();
    window->show(); 
    return Fl::run();
}