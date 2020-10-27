#include "MainWindow.hpp"
#include "AuditorTable.hpp"
#include "AbstractTableModel.hpp"
#include "../Class/Auditor.hpp"
#include "ArrayAuditors.hpp"

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
    vector<Auditor *> *p = prikazOsoba->company.getCompanyAuditors();
    ArrayAuditors *auditors = new ArrayAuditors();

    prikazOsoba->btnWorkers->hide();
    prikazOsoba->btnDepartments->hide();
    prikazOsoba->btnCompany->hide();
    prikazOsoba->btnCommercialist->hide();
    prikazOsoba->btnAudits->hide();
    prikazOsoba->btnAuditors->hide();
    prikazOsoba->btnAccountant->hide();

    AuditorTable *tableAuditors = new AuditorTable(prikazOsoba->x, prikazOsoba->y, prikazOsoba->w, prikazOsoba->h, auditors);
    
    for(Auditor *aud : *p)
        tableAuditors->add(aud);
    
    /*tableAuditors->when(FL_WHEN_RELEASE | FL_WHEN_CHANGED);
    tableAuditors->table_box(FL_NO_BOX);
    tableAuditors->col_resize_min(4);
    tableAuditors->row_resize_min(4);
    tableAuditors->row_height_all(20);
    tableAuditors->col_resize(1);
    tableAuditors->col_header(1);
    tableAuditors->col_header_height(25);
    tableAuditors->col_width_all(80);
    tableAuditors->cols(3);*/
    
    
    prikazOsoba->add(tableAuditors);
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