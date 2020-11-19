#ifndef DEPARTMENT_TABLE_HPP
#define DEPARTMENT_TABLE_HPP

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

#include "../../Class/Department.hpp"
#include "ArrayDepartments.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"
#include "../WorkerTable.hpp"

class DepartmentTable : public WorkerTable<Department>
{
public:
    DepartmentTable(int x, int y, int w, int h, ArrayDepartments *departments, const char* l=0);
    virtual ~DepartmentTable();
};

#endif