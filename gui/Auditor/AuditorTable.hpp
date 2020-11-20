#ifndef AUDITOR_TABLE_HPP
#define AUDITOR_TABLE_HPP

#include <vector>
#include <string>
#include <sstream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Spinner.H>

#include "../../Class/Auditor.hpp"
#include "ArrayAuditors.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"
#include "../WorkerTable.hpp"

class AuditorTable : public WorkerTable<Auditor>
{
public:
    AuditorTable(int x, int y, int w, int h, ArrayAuditors *original, ArrayAuditors *changed, const char* l=0);
    virtual ~AuditorTable();
};

#endif