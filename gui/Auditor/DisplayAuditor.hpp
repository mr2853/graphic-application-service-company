#ifndef DISPLAY_AUDITORS_HPP
#define DISPLAY_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>

#include "../../Class/Auditor.hpp"
#include "../DisplayWorker.hpp"
#include "../AbstractModel.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/AbstractWorker.hpp"

class DisplayAuditor : public DisplayWorker{
protected:
    Fl_Multiline_Input *datesVisiting;

public:
    DisplayAuditor(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayAuditor();
    vector<Date*>* getDatesVisiting();
    void setDatesVisiting(string t);
    virtual void displayWorker(Auditor *worker);
    virtual void hide();
    void unhide();
    string getType();
    bool isInputsEmpty();
    void deactivate();
};


#endif