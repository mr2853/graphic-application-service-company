#ifndef DATA_OF_AUDITORS_HPP
#define DATA_OF_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "../../Class/Auditor.hpp"
#include "../DisplayWorker.hpp"
#include "DisplayAuditor.hpp"
#include "../DataOfWorker.hpp"
#include "../ArrayWorkers.hpp"

class DataOfAuditors : public DataOfWorker<Auditor*>{
protected:
    DisplayAuditor *displayAuditor;

    static void change(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);

public:
    DataOfAuditors(int x, int y, int w, int h, ArrayWorkers<Auditor*> *original, ArrayWorkers<Auditor*> *changed, Company *company, void *mainWindow, const char *l=0);
    virtual ~DataOfAuditors();
    virtual void setDisplay(int indeks);
    void hideGroup();
};


#endif