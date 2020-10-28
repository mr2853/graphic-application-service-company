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
    Fl_Button *btnAdd;
    //Fl_Button *btnView;
    Fl_Button *btnRemove;

public:
    DataOfAuditors(int x, int y, int w, int h, Company &company, const char *l);
    virtual ~DataOfAuditors();
    static void add(Fl_Widget *widget, void *data);
    static void remove(Fl_Widget *widget, void *data);
    //static void view(Fl_Widget *widget, void *data);
    void addAuditor(Fl_Widget *widget, void *data);
};


#endif