#ifndef DATA_OF_AUDITORS_HPP
#define DATA_OF_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "AuditorTable.hpp"
#include "../Class/Auditor.hpp"
#include "DisplayWorker.hpp"
#include "DisplayAuditor.hpp"
#include "ArrayAuditors.hpp"
#include "MainWindow.hpp"

class DataOfAuditors : public Fl_Group{
protected:
    ArrayAuditors *auditors;
    DisplayAuditor *displayAuditor;
    AuditorTable *auditorTable;
    //Fl_Button *btnView;
    Fl_Button *btnRemove;
    Company &company;
    Fl_Button *btnGoBack;

public:
    DataOfAuditors(int x, int y, int w, int h, Company &company, void *mainWindow, const char *l=0);
    virtual ~DataOfAuditors();
    static void remove(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    //static void view(Fl_Widget *widget, void *data);
    void addAuditor(Fl_Widget *widget, void *data);
    Company& getCompany();
    void refreshTable();
    AuditorTable* getAuditorTable();
    void addAuditor(Auditor* a);
    int numberOfAuditors();
};


#endif