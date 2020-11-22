#include "DisplayAccountant.hpp"
#include "DataOfAccountants.hpp"
#include "../../Util.hpp"

DisplayAccountant::DisplayAccountant(int x, int y, int w, int h, const char *l)
: DisplayWorker(x, y, 200, 190, "")
{
    bodyIssuedPermit = new Fl_Input(x, y+200, 100, 40, "Issued Permit:");
    maxAmountCompanyIncome = new Fl_Value_Input(x, y+280, 100, 40, "Max Income:");
    maxAmountCompanyIncome->precision(2);
    this->end();
}
string DisplayAccountant::getType()
{
    return "DisplayAccountant";
}
DisplayAccountant::~DisplayAccountant()
{
    delete bodyIssuedPermit;
    delete maxAmountCompanyIncome;
}
bool DisplayAccountant::isInputsEmpty()
{
    if(!DisplayWorker::isInputsEmpty())
    {
        return false;
    }
    string a = bodyIssuedPermit->value();
    try{
        if(a.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Issued permit"));
        return false;
    }
    return true;
}
void DisplayAccountant::hide()
{
    this->label("");
    DisplayWorker::hide();
    this->bodyIssuedPermit->hide();
    this->maxAmountCompanyIncome->hide();
}
void DisplayAccountant::unhide()
{
    DisplayWorker::unhide();
    this->bodyIssuedPermit->show();
    this->maxAmountCompanyIncome->show();
}

void DisplayAccountant::setBodyIssuedPermit(string t)
{
    bodyIssuedPermit->value(t.c_str());
}
void DisplayAccountant::setMaxAmountCompanyIncome(string t)
{
    maxAmountCompanyIncome->value(stod(t));
}

string DisplayAccountant::getBodyIssuedPermit()
{
    string s = bodyIssuedPermit->value();
    ltrim(s);
    return s;
}
double DisplayAccountant::getMaxAmountCompanyIncome()
{
    return maxAmountCompanyIncome->value();
}