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

class DepartmentTable : public Fl_Table_Row, protected AbstractDisplay<Department *>
{
protected:
    ArrayDepartments *departments;
    virtual void draw_cell(TableContext context, int red = 0, int kolona = 0, int x = 0, int y = 0, int w = 0, int h = 0);
    virtual void elementPushed(int red, Department* element);
    virtual void elementRemoved(int red);

public:
    DepartmentTable(int x, int y, int w, int h, ArrayDepartments *departments);
    virtual ~DepartmentTable();
    DepartmentTable();
    void add(Department *p);
    void refreshTable();
};

#endif