#ifndef DISPLAY_ABSTRACT_HPP
#define DISPLAY_ABSTRACT_HPP
#include <iostream>
#include "AuditorTable.hpp"
#include "../Class/Auditor.hpp"
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>


class DisplayWorker : public Fl_Group{
protected:
    Fl_Output *name;
    Fl_Output *lastName;
    Fl_Output *dateBirth;
    Fl_Output *salary;
public:
    DisplayWorker(int x, int y, int width, int height, const char *label);
    virtual ~DisplayWorker();
};


#endif