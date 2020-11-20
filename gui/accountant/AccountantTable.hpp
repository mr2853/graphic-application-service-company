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
#include "../WorkerTable.hpp"

class AccountantTable : public WorkerTable<Accountant>
{
public:
    AccountantTable(int x, int y, int w, int h, ArrayAccountants *original, ArrayAccountants *changed, const char* l=0);
    virtual ~AccountantTable();
};

#endif