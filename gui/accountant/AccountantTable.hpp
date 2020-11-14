#ifndef AUDITOR_ACCOUNTANT_HPP
#define AUDITOR_ACCOUNTANT_HPP

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

#include "../../Class/Accountant.hpp"
#include "ArrayAccountants.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"

class AccountantTable : public Fl_Table_Row, protected AbstractDisplay<Accountant *>
{
protected:
    ArrayAccountants *accountants;
    virtual void draw_cell(TableContext context, int red = 0, int kolona = 0, int x = 0, int y = 0, int w = 0, int h = 0);
    virtual void elementPushed(int red, Accountant* element);
    virtual void elementRemoved(int red);

public:
    AccountantTable(int x, int y, int w, int h, ArrayAccountants *accountants);
    virtual ~AccountantTable();
    AccountantTable();
    void add(Accountant *p);
    void refreshTable();
    //void AccountantTable::removeAuditor(Accountant *r);
};

#endif