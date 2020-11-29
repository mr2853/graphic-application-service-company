#ifndef DISPLAY_COMPANY_HPP
#define DISPLAY_COMPANY_HPP
#include <iostream>
#include <string>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Input.H>

#include "../DisplayWorker.hpp"

class DisplayCompany : public Fl_Group{
protected:
    Fl_Input *name;
    Fl_Input *taxIdentificationNumber;
    Fl_Input *identificationNumber;

public:
    DisplayCompany(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayCompany();
    void hideGroup();
    void unhide();
    string getName() const;
    void setName(string t);
    string getTaxIdentificationNumber() const;
    void setTaxIdentificationNumber(string t);
    string getIdentificationNumber() const;
    void setIdentificationNumber(string t);
    bool isInputsEmpty() const;
};

#endif