#include <iostream>
#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <fstream>

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

using namespace std;

void save(Fl_Widget *widget, void *data)
{
    Array<Company*> *original = (Array<Company*>*)data;
    int answer = fl_choice("Do you want to save changes before closing?", "Yes", "No", "Go back");
    if (answer == 0)
    {
        ofstream datoteka("data.txt");
        original->write(datoteka);
        datoteka.close();
    }
    if (answer < 2)
    {
        widget->hide();
    }
}

int main()
{
    Array<Company*> *original = new Array<Company*>(Company::readData1("data.txt"));
    Array<Company*> *changed = new Array<Company*>(Company::readData1("data.txt", 1));

    Fl_Window *window = new Fl_Window(900, 700, "Project");
    DataOfCompanies *dataOfCompanies = new DataOfCompanies(50, 50, 900, 700, original, changed, window, "");
    window->resizable(dataOfCompanies);
    window->end();
    
    window->callback(save, original);
    window->show();
    return Fl::run();
}