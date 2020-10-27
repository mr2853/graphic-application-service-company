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

#include "../Class/Auditor.hpp"
#include "ArrayAuditors.hpp"
#include "AbstractDisplay.hpp"

class AuditorTable : public Fl_Table_Row, protected AbstractDisplay<Auditor *>
{
protected:
    ArrayAuditors *auditors;
    virtual void draw_cell(TableContext context, int red = 0, int kolona = 0, int x = 0, int y = 0, int w = 0, int h = 0);
    virtual void elementPushed(int red, Auditor* element);
    virtual void elementRemoved(int red);

public:
    AuditorTable(int x, int y, int w, int h, ArrayAuditors *auditors);
    virtual ~AuditorTable();
    void add(Auditor *p);
};

#endif