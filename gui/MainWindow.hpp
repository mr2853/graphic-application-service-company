#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include <iostream>
#include <string>
#include "../Class/Company.hpp"

#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

class MainWindow : public Fl_Group{
protected:
    Fl_Button *btnAudits;
    Fl_Button *btnCompany;
    Fl_Button *btnDepartments;
    Fl_Button *btnAccountant;
    Fl_Button *btnCommercialist;
    Fl_Button *btnAuditors;
    Fl_Button *btnWorkers;
    Company &company;
    int x,y,w,h;

public:
    MainWindow(int x, int y, int w, int h, const char *label, Company &company);
    virtual ~MainWindow();

    static void callTableAudits(Fl_Widget *widget, void *data);
    static void callTableCompany(Fl_Widget *widget, void *data);
    static void callTableDepartments(Fl_Widget *widget, void *data);
    static void callTableAccountant(Fl_Widget *widget, void *data);
    static void callTableCommercialist(Fl_Widget *widget, void *data);
    static void callTableAuditors(Fl_Widget *widget, void *data);
    static void callTableWorkers(Fl_Widget *widget, void *data);

};




#endif