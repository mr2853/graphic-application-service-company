#ifndef DISPLAY_AUDITORS_HPP
#define DISPLAY_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>

#include "AuditorTable.hpp"
#include "../Class/Auditor.hpp"
#include "DisplayWorker.hpp"
#include "AbstractModel.hpp"
#include "AbstractDisplay.hpp"
#include "ArrayAuditors.hpp"

class DisplayAuditor : public DisplayWorker, protected AbstractDisplay<Auditor *>{
protected:
    DisplayWorker *displayWorker;
    Fl_Multiline_Input *datesVisiting;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;
    
    int current = -1;
    ArrayAuditors *auditors;

    void updateLabel();
    void checkButtons();
    void setDisplay(int indeks);
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, Auditor *element);
    void elementRemoved(int indeks);
public:
    DisplayAuditor(int x, int y, int w, int h, ArrayAuditors *auditors, void* data, const char *l);
    virtual ~DisplayAuditor();
    vector<Date*>* getDatesVisiting();
};


#endif