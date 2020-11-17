#ifndef COMPANY_TABLE_HPP
#define COMPANY_TABLE_HPP

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

#include "../../Class/Company.hpp"
#include "../Department/ArrayDepartments.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"
#include "../WorkerTable.hpp"

class CompanyTable : public WorkerTable<Company>
{
public:
    CompanyTable(int x, int y, int w, int h, ArrayWorkers<Company> *departments);
    virtual ~CompanyTable();
};

#endif