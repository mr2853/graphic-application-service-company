#ifndef DISPLAY_COMMERCIALISTS_HPP
#define DISPLAY_COMMERCIALISTS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>

#include "../../Class/Commercialist.hpp"
#include "../DisplayWorker.hpp"
#include "../AbstractModel.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/AbstractWorker.hpp"

class DisplayCommercialist : public DisplayWorker{
protected:
    Fl_Multiline_Input *businessContact;

public:
    DisplayCommercialist(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayCommercialist();
    vector<string*>* getBusinessContacts() const;
    void setBusinessContact(string t);
    virtual void displayWorker(Commercialist *worker);
    virtual void hide();
    void unhide();
    string getType() const;
    bool isInputsEmpty() const;
};


#endif