#include "MainWindow.hpp"
#include "AuditorTable.hpp"
#include "AbstractTableModel.hpp"
#include "../Class/Auditor.hpp"
#include "ArrayAuditors.hpp"
#include "DataOfAuditors.hpp"

MainWindow::~MainWindow(){}
MainWindow::MainWindow(int x, int y, int w, int h, const char *label, Company &company)
    : Fl_Group(x, y, w, h, label), company(company), x(x), y(y), w(w), h(h)
{
    btnAudits = new Fl_Button(x, y, 200, 40, "DATA OF AUDITS");
    btnCompany = new Fl_Button(x, y+50, 200, 40, "DATA OF COMPANY");
    btnDepartments = new Fl_Button(x, y+100, 200, 40, "DATA OF DEPARTMENTS");
    btnAccountant = new Fl_Button(x, y+150, 200, 40, "DATA OF ACCOUNTANT");

    btnCommercialist = new Fl_Button(x+210, y, 200, 40, "DATA OF COMMERCIALIST");
    btnAuditors = new Fl_Button(x+210, y+50, 200, 40, "DATA OF AUDITORS");
    btnWorkers = new Fl_Button(x+210, y+100, 200, 40, "DATA OF WORKERS");

    btnAudits->callback(MainWindow::callTableAudits,this);
    btnCompany->callback(MainWindow::callTableCompany,this);
    btnDepartments->callback(MainWindow::callTableDepartments,this);
    btnAccountant->callback(MainWindow::callTableAccountant,this);
    btnCommercialist->callback(MainWindow::callTableCommercialist,this);
    btnAuditors->callback(MainWindow::callTableAuditors,this);
    btnWorkers->callback(MainWindow::callTableWorkers,this);

    this->end();
};

void MainWindow::callTableAuditors(Fl_Widget *widget, void *data)
{
    MainWindow *prikazOsoba = (MainWindow *)data;
    string type = "Auditor";

    prikazOsoba->btnWorkers->hide();
    prikazOsoba->btnDepartments->hide();
    prikazOsoba->btnCompany->hide();
    prikazOsoba->btnCommercialist->hide();
    prikazOsoba->btnAudits->hide();
    prikazOsoba->btnAuditors->hide();
    prikazOsoba->btnAccountant->hide();

    DataOfAuditors *dataOfAuditors = new DataOfAuditors(prikazOsoba->x, prikazOsoba->y, prikazOsoba->w, prikazOsoba->h, prikazOsoba->company, "");

    prikazOsoba->add(dataOfAuditors);
};
void MainWindow::callTableCompany(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableDepartments(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableAccountant(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableCommercialist(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableAudits(Fl_Widget *widget, void *data)
{

};
void MainWindow::callTableWorkers(Fl_Widget *widget, void *data)
{

};