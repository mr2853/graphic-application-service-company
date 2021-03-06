#ifndef DATA_OF_ACCOUNTANT_HPP
#define DATA_OF_ACCOUNTANT_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "../../Class/Accountant.hpp"
#include "../DisplayWorker.hpp"
#include "DisplayAccountant.hpp"
#include "../DataOfWorker.hpp"
#include "../Array.hpp"

class DataOfAccountants : public DataOfWorker<Accountant*>{
protected:
    DisplayAccountant *displayAccountant;
    
    static void add(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);

public:
    DataOfAccountants(int x, int y, int w, int h, Array<Accountant*> *original, Array<Accountant*> *changed, Company *company, void *mainWindow, const char *l=0);
    virtual ~DataOfAccountants();
    virtual void setDisplay(int indeks);
    void hideGroup();
};


#endif