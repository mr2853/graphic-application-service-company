#ifndef DISPLAY_ACCOUNTANT_HPP
#define DISPLAY_ACCOUNTANT_HPP
#include <iostream>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>

#include "AccountantTable.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/AbstractWorker.hpp"
#include "../DisplayWorker.hpp"
#include "../AbstractModel.hpp"
#include "../AbstractDisplay.hpp"
#include "ArrayAccountants.hpp"

class DisplayAccountant : public DisplayWorker{
protected:
    Fl_Input *bodyIssuedPermit;
    Fl_Value_Input *maxAmountCompanyIncome;
    
public:
    DisplayAccountant(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayAccountant();
    string getBodyIssuedPermit();
    double getMaxAmountCompanyIncome();
    void setBodyIssuedPermit(string t);
    void setMaxAmountCompanyIncome(string t);
    // virtual void displayWorker(Accountant *worker);
    virtual void hide();
    void unhide();
    string getType();
};


#endif