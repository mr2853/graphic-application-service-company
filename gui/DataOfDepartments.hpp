#ifndef DATA_OF_DEPARTMENTS_HPP
#define DATA_OF_DEPARTMENTS_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../Class/Company.hpp"

class DataOfDepartments : public Fl_Group{
protected:
    Fl_Choice *chDepartment;
    Fl_Choice *chWorkerType;
    Fl_Button *btnDetails;
    Fl_Button *btnAdd;
    Fl_Button *btnRemove;
    Fl_Button *btnChange;
    Fl_Button *btnGoBack;
    Company &company;

    static void details(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    static void remove(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);

public:
    DataOfDepartments(int x, int y, int w, int h, Company &company, void *data, const char *l=0);
    virtual ~DataOfDepartments();
};

#endif