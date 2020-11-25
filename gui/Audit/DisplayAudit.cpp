#include "DisplayAudit.hpp"
#include "../../Class/Auditor.hpp"
#include "../../Class/Accountant.hpp"
#include "../../Class/Commercialist.hpp"
#include "../../Util.hpp"
#include <FL/fl_message.H>

DisplayAudit::DisplayAudit(int x, int y, int w, int h, const char *l)
: Fl_Group(x,y,w,h,l)
{
    date = new Fl_Input(x, y, 100, 40, "Date:");
    displayAuditor = new DisplayAuditor(x, y+60, 100, 190, "Auditor:");
    displayAuditor->deactivate();
    this->end();
}
void DisplayAudit::displayThisAudit(Audit* audit)
{
    cout << "display ovde1" << endl;
    displayAuditor->displayWorker(audit->getAuditor());
    cout << "display ovde2" << endl;
    date->value(audit->getDate()->getDateWithTime().c_str());
    cout << "display ovde3" << endl;
}

void DisplayAudit::displayThisAuditor(Auditor* auditor)
{
    displayAuditor->displayWorker(auditor);
}

bool DisplayAudit::isInputsEmpty()
{
    string a = date->value();
    try{
        if(a.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Name of Department"));
        return false;
    }
    return true;
}

Audit* DisplayAudit::getAudit()
{
    
    try{
        return new Audit(nullptr, this->getDate());
    }
    catch(WrongDate e)
    {
        fl_message(e.what("Date birth"));
        return nullptr;
    }
    catch(WrongDateWithTime e)
    {
        fl_message(e.what("Dates visiting"));
        return nullptr;
    }
    return nullptr;
}

DisplayAudit::~DisplayAudit(){}

void DisplayAudit::setDate(string t)
{
    date->value(t.c_str());
}

Date* DisplayAudit::getDate()
{
    string t = date->value();
    ltrim(t);
    if(!correctDate(t, 1)){
        throw WrongDate();
    }
    int index = t.find("-");
    int a = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    index = t.find("-");
    int b = stoi(t.substr(0, index));
    t.erase(0, index+1);
    int c = -1;
    int d = -1;

    index = t.find("-");
    c = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    index = t.find("-");
    d = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    int e = stoi(t);
    
    return new Date(a,b,c,d,e);
}

void DisplayAudit::hideGroup() {
    this->label("");
    this->date->hide();
    displayAuditor->hide();
}
void DisplayAudit::unhide() {
    this->date->show();
    displayAuditor->unhide();
}