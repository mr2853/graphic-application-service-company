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

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    //Company &company;

public:
    DataOfAuditors(int x, int y, int w, int h, ArrayAuditors *auditors, void *mainWindow, const char *l=0);
    virtual ~DataOfAuditors();
    
    static void remove(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);

    void addAuditor(Fl_Widget *widget, void *data);
    //Company& getCompany();
    void refreshTable();
    AuditorTable* getAuditorTable();
    void addAuditor(Auditor* a);
    int numberOfAuditors();
    void hideGroup();

};


#endif