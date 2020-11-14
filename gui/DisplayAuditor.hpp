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
#include "../Class/AbstractWorker.hpp"

class DisplayAuditor : public DisplayWorker, protected AbstractDisplay<Auditor *>{
protected:
    Fl_Multiline_Input *datesVisiting;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;
    
    int current = 0;
    ArrayAuditors *auditors;

    void updateLabel();
    void checkButtons();
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, Auditor *element);
    void elementRemoved(int indeks);
public:
    virtual void setDisplay(int indeks);
    DisplayAuditor(int x, int y, int w, int h, ArrayAuditors *auditors, void* data, const char *l=0);
    DisplayAuditor(int x, int y, int w, int h, ArrayAuditors *auditors, const char *l=0);
    virtual ~DisplayAuditor();
    vector<Date*>* getDatesVisiting();
    virtual void displayWorker(Auditor *worker);
    virtual void hide();
    void unhide();
    int getCurrent();
    string getType();
};


#endif