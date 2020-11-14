#ifndef DISPLAY_DEPARTMENT_HPP
#define DISPLAY_DEPARTMENT_HPP
#include <iostream>
#include <string>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>

#include "DisplayWorker.hpp"
#include "../Class/Department.hpp"
#include "ArrayDepartments.hpp"
#include "AbstractDisplay.hpp"

class DisplayDepartment : public Fl_Group, protected AbstractDisplay<Department *>{
protected:
    Fl_Input *name;
    DisplayWorker *headOfDepartment;
    Fl_Choice *chTypeOfHead;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;

    int current = 0;
    ArrayDepartments *departments;

    void updateLabel();
    void checkButtons();
    void setDisplay(int indeks);
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, Department *element);
    void elementRemoved(int indeks);
public:
    DisplayDepartment(int x, int y, int w, int h, ArrayDepartments *departments, void* data, const char *l);
    virtual ~DisplayDepartment();
    int getCurrent();
    void hideGroup();
    void unhide();
    string getName();
    AbstractWorker* getHeadOfDepartment() const;
};

#endif