#ifndef DISPLAY_ABSTRACT_HPP
#define DISPLAY_ABSTRACT_HPP
#include <iostream>
#include "Auditor/AuditorTable.hpp"
#include "../Class/Auditor.hpp"
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include "../Class/AbstractWorker.hpp"


class DisplayWorker : public Fl_Group{
protected:
    Fl_Input *name;
    Fl_Input *lastName;
    Fl_Input *dateBirth;
    Fl_Value_Input *salary;
public:
    DisplayWorker(int x, int y, int w, int h, const char *l);
    virtual ~DisplayWorker();
    virtual void displayWorker(AbstractWorker *worker);
    string getValueName();
    string getValueLastName();
    Date* getValueDateBirth();
    double getValueSalary();
    virtual void hide();
    void unhide();
    virtual string getType();
    bool isInputsEmpty();
};


#endif