#include "MainWindow.hpp"
#include "Auditor/AuditorTable.hpp"
#include "AbstractTableModel.hpp"
#include "../Class/Auditor.hpp"
#include "Auditor/ArrayAuditors.hpp"
#include "Auditor/DataOfAuditors.hpp"
#include "DataOfDepartments.hpp"

MainWindow::~MainWindow(){}
MainWindow::MainWindow(int x, int y, int w, int h, const char *label, Company &company)
    : Fl_Group(x, y, w, h, label), company(company), x(x), y(y), w(w), h(h)
{
    btnAudits = new Fl_Button(x, y, 200, 40, "DATA OF AUDITS");
    btnCompany = new Fl_Button(x, y+50, 200, 40, "DATA OF COMPANY");
    btnDepartments = new Fl_Button(x, y+100, 200, 40, "DATA OF DEPARTMENTS");
    btnWorkers = new Fl_Button(x+210, y+100, 200, 40, "DATA OF WORKERS");

    btnAudits->callback(MainWindow::callTableAudits,this);
    btnCompany->callback(MainWindow::callTableCompany,this);
    btnDepartments->callback(MainWindow::callTableDepartments,this);
    btnWorkers->callback(MainWindow::callTableWorkers,this);

    this->end();
};
void MainWindow::hide()
{
    this->btnWorkers->hide();
    this->btnDepartments->hide();
    this->btnCompany->hide();
    this->btnAudits->hide();
}
void MainWindow::unhide()
{
    this->btnWorkers->show();
    this->btnDepartments->show();
    this->btnCompany->show();
    this->btnAudits->show();
}
// void MainWindow::callTableAuditors(Fl_Widget *widget, void *data)
// {
//     MainWindow *mainWindow = (MainWindow *)data;
//     string type = "Auditor";
//     mainWindow->hide();
//     DataOfAuditors *dataOfAuditors = new DataOfAuditors(mainWindow->x, mainWindow->y, mainWindow->w, mainWindow->h, mainWindow->company, mainWindow, "");

//     mainWindow->add(dataOfAuditors);
// };
void MainWindow::callTableCompany(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableDepartments(Fl_Widget *widget, void *data)
{
    MainWindow *mainWindow = (MainWindow *)data;
    mainWindow->hide();
    DataOfDepartments *dataOfDepartments = new DataOfDepartments(mainWindow->x, mainWindow->y, mainWindow->w, mainWindow->h, mainWindow->company, mainWindow, "");

    mainWindow->add(dataOfDepartments);
};
void MainWindow::callTableAudits(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableWorkers(Fl_Widget *widget, void *data)
{

};