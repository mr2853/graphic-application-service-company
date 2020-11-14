#ifndef DISPLAY_ACCOUNTANT_HPP
#define DISPLAY_ACCOUNTANT_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>

#include "AccountantTable.hpp"
#include "../../Class/Accountant.hpp"
#include "../DisplayWorker.hpp"
#include "../AbstractModel.hpp"
#include "../AbstractDisplay.hpp"
#include "ArrayAccountants.hpp"
#include "../../Class/AbstractWorker.hpp"

class DisplayAccountant : public DisplayWorker, protected AbstractDisplay<Accountant *>{
protected:
    Fl_Input *bodyIssuedPermit;
    Fl_Input *maxAmountCompanyIncome;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;
    
    int current = 0;
    ArrayAccountants *accountants;

    void updateLabel();
    void checkButtons();
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, Accountant *element);
    void elementRemoved(int indeks);
public:
    virtual void setDisplay(int indeks);
    DisplayAccountant(int x, int y, int w, int h, ArrayAccountants *accountants, void* data, const char *l=0);
    DisplayAccountant(int x, int y, int w, int h, ArrayAccountants *accountants, const char *l=0);
    virtual ~DisplayAccountant();
    string getBodyIssuedPermit();
    string getMaxAmountCompanyIncome();
    // virtual void displayWorker(Accountant *worker);
    virtual void hide();
    void unhide();
    int getCurrent();
    string getType();
};


#endif