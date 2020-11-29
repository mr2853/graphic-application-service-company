#ifndef DISPLAY_AUDIT_HPP
#define DISPLAY_AUDIT_HPP
#include <iostream>
#include <string>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Input.H>

#include "../Auditor/DisplayAuditor.hpp"
#include "../../Class/Audit.hpp"

class DisplayAudit : public Fl_Group{
protected:
    DisplayAuditor *displayAuditor;
    Fl_Input *date;

public:
    DisplayAudit(int x, int y, int w, int h, const char *l=0);
    virtual ~DisplayAudit();
    void hideGroup();
    void unhide();
    Date* getDate() const;
    void setDate(string t);
    void displayThisAudit(Audit* audit);
    void displayThisAuditor(Auditor* worker);
    Audit* getAudit() const;
    bool isInputsEmpty() const;
};

#endif