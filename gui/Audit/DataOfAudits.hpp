#ifndef DATA_OF_AUDITS_HPP
#define DATA_OF_AUDITS_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../../Class/Audit.hpp"
#include "DisplayAudit.hpp"
#include "../DataOf.hpp"
#include "../ArrayWorkers.hpp"
#include "ArrayAudits.hpp"

class DataOfAudits : public DataOf<Audit>{
protected:
    Fl_Choice *chAuditor;
    DisplayAudit *displayAudit;
    
    static void add(Fl_Widget *widget, void *data);
    static void details(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    void insertDataInChAuditor(ArrayAudits *array);
    void setDisplay(int indeks);
    void isAuditsEmpty();
    void displayAuditor();
public:
    DataOfAudits(int x, int y, int w, int h, ArrayAudits *array, void *mainWindow, const char *l=0);
    virtual ~DataOfAudits();
    void hideGroup();
    void unhideGroup();
};

#endif