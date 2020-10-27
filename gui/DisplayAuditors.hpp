#ifndef DISPLAY_AUDITORS_HPP
#define DISPLAY_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>

#include "AuditorTable.hpp"
#include "../Class/Auditor.hpp"
#include "DisplayWorker.hpp"

class DisplayAuditor : public Fl_Group, public DisplayAbstract{
protected:
    DisplayAbstract *abs= new DisplayAbstract(2,2,2,2,"");
public:

};


#endif