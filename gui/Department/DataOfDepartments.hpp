#ifndef DATA_OF_DEPARTMENTS_HPP
#define DATA_OF_DEPARTMENTS_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../../Class/Department.hpp"
#include "DisplayDepartment.hpp"
#include "../DataOf.hpp"
#include "../ArrayWorkers.hpp"
#include "ArrayDepartments.hpp"

class DataOfDepartments : public DataOf<Department>{
protected:
    DisplayDepartment *displayDepartment;
    Fl_Button *btnDetails;

    Fl_Choice *chDepartment;
    Fl_Choice *chWorkerType;

    void setDisplay(int indeks);
    void updateChDepart();
    
    static void add(Fl_Widget *widget, void *data);
    static void details(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    void isDepartmentsEmpty();
public:
    DataOfDepartments(int x, int y, int w, int h, ArrayDepartments *original, ArrayDepartments *changed, void *mainWindow, const char *l=0);
    virtual ~DataOfDepartments();
    void hideGroup();
    void unhideGroup();
};

#endif