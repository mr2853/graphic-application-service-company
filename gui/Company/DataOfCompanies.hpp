#ifndef DATA_OF_COMPANIES_HPP
#define DATA_OF_COMPANIES_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include "../../Class/Company.hpp"
#include "../../Class/Company.hpp"
#include "DisplayCompany.hpp"
#include "../DataOf.hpp"
#include "../ArrayWorkers.hpp"

class DataOfCompanies : public DataOf<Company*>{
protected:
    DisplayCompany *display;
    Fl_Button *btnDetails;
    Fl_Button *btnAudits;

    Fl_Choice *chCompany;

    void setDisplay(int indeks);
    void updateChCompany();
    
    static void add(Fl_Widget *widget, void *data);
    static void details(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    static void audits(Fl_Widget *widget, void *data);
    void isCompaniesEmpty();
public:
    DataOfCompanies(int x, int y, int w, int h, ArrayWorkers<Company*> *original, ArrayWorkers<Company*> *changed, void *data, const char *l=0);
    virtual ~DataOfCompanies();
    void hideGroup();
    void unhideGroup();
};

#endif