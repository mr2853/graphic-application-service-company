#ifndef COMMERCIALIST_TABLE_HPP
#define COMMERCIALIST_TABLE_HPP

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

#include "../../Class/Commercialist.hpp"
#include "ArrayCommercialists.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"

class CommercialistTable : public Fl_Table_Row, protected AbstractDisplay<Commercialist *>
{
protected:
    ArrayCommercialists *commercialists;
    virtual void draw_cell(TableContext context, int red = 0, int kolona = 0, int x = 0, int y = 0, int w = 0, int h = 0);
    virtual void elementPushed(int red, Commercialist* element);
    virtual void elementRemoved(int red);

public:
    CommercialistTable(int x, int y, int w, int h, ArrayCommercialists *commercialists);
    virtual ~CommercialistTable();
    CommercialistTable();
    void add(Commercialist *p);
    void refreshTable();
    //void CommercialistTable::removeAuditor(Commercialist *r);
};

#endif