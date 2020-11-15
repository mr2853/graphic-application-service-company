#ifndef DATA_OF_DEPARTMENTS_HPP
#define DATA_OF_DEPARTMENTS_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../../Class/Company.hpp"
#include "../../Class/Department.hpp"
#include "DisplayDepartment.hpp"
#include "ArrayDepartments.hpp"
#include "DepartmentTable.hpp"

class DataOfDepartments : public Fl_Group, protected AbstractDisplay<Department *>{
protected:
    ArrayDepartments *departments;
    DisplayDepartment *displayDepartment;
    DepartmentTable *departmentTable;
    Company &company;
    int current = 0;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    Fl_Button *btnDetails;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;

    Fl_Choice *chDepartment;
    Fl_Choice *chWorkerType;

    void updateLabel();
    void checkButtons();
    void setDisplay(int indeks);
    
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void details(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);

    void elementPushed(int indeks, Department *element);
    void elementRemoved(int indeks);
    void updateChDepart();

public:
    DataOfDepartments(int x, int y, int w, int h, Company &company, void *mainWindow, const char *l=0);
    virtual ~DataOfDepartments();
    //static void view(Fl_Widget *widget, void *data);
    void addDepartment(Fl_Widget *widget, void *data);
    int getCurrent();
    Company& getCompany();
    void refreshTable();
    DepartmentTable* getDepartmentTable();
    void addDepartment(Department* a);
    int numberOfDepartments();
    void hideGroup();
    void unhide();
};

#endif