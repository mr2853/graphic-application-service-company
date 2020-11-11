#ifndef DATA_OF_DEPARTMENTS_HPP
#define DATA_OF_DEPARTMENTS_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../Class/Company.hpp"
#include "../Class/Department.hpp"
#include "DisplayDepartment.hpp"
#include "ArrayDepartments.hpp"
#include "DepartmentTable.hpp"

class DataOfDepartments : public Fl_Group{
protected:
    ArrayDepartments *departments;
    DisplayDepartment *displayDepartment;
    DepartmentTable *departmentTable;
    Company &company;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    Fl_Button *btnDetails;

    Fl_Choice *chDepartment;
    Fl_Choice *chWorkerType;

public:
    DataOfDepartments(int x, int y, int w, int h, Company &company, void *mainWindow, const char *l=0);
    virtual ~DataOfDepartments();
    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void details(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    //static void view(Fl_Widget *widget, void *data);
    void addDepartment(Fl_Widget *widget, void *data);
    Company& getCompany();
    void refreshTable();
    DepartmentTable* getDepartmentTable();
    void addDepartment(Department* a);
    int numberOfDepartments();
    void hideGroup();
    void unhide();
};

#endif