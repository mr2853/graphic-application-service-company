#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>


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
#include "gui/MainWindow.hpp"

using namespace std;

int main()
{
    Company *company = new Company();
    company->readData1("podaci.txt");
    Fl_Window *window = new Fl_Window(900, 700, "Projekat");
    MainWindow *mainWindow = new MainWindow(50, 50, 900, 700, "", *company);
    window->resizable(mainWindow);
    window->end();
    window->show(); 
    return Fl::run();
}