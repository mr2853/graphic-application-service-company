#ifndef DISPLAY_DEPARTMENT_HPP
#define DISPLAY_DEPARTMENT_HPP
#include <iostream>
#include <string>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Input.H>

#include "../DisplayWorker.hpp"

class DisplayDepartment : public Fl_Group{
protected:
    Fl_Input *name;
    DisplayWorker *headOfDepartment;
    Fl_Choice *chTypeOfHead;

public:
    DisplayDepartment(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayDepartment();
    void hideGroup();
    void unhide();
    string getName() const;
    void setName(string t);
    void displayHeadOfDepartment(AbstractWorker* worker);
    AbstractWorker* getNewHeadOfDepartment() const;
    string getChTypeOfHead() const;
    bool isInputsEmpty() const;
};

#endif