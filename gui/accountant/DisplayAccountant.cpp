#include "DisplayAccountant.hpp"
#include "DataOfAccountants.hpp"
#include "../../Util.hpp"

DisplayAccountant::DisplayAccountant(int x, int y, int w, int h, const char *l)
: DisplayWorker(x, y, 200, 190, "")
{
    bodyIssuedPermit = new Fl_Input(x, y+200, 100, 40, "Issued Permit:");
    maxAmountCompanyIncome = new Fl_Value_Input(x, y+280, 100, 40, "Max company Income:");
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
/*void DisplayAccountant::displayAccountant(Accountant *auditor)
{
    cout << "displayAccountant ovde" <<endl;
    //this->auditor = auditor;
    cout << "displayAccountant ovde1" <<endl;
    displayWorker->displayWorker(auditor);
    cout << "displayAccountant ovde2" <<endl;
    datesVisiting->value("");
    for(int i = 0; i < auditor->getNumberOfVisits(); i++)
    {
        datesVisiting->insert(auditor->getDateVisiting(i)->getDateWithTime().c_str());
    }
    cout << "displayAccountant ovde3" <<endl;
}*/


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

// void DisplayAccountant::displayWorker(Accountant *worker)
// {
//     //this->worker = worker;
//     DisplayWorker::displayWorker(worker);
//     // datesVisiting = new Fl_Multiline_Input(x, y+200, 200, 70, "Dates visiting:");
//     datesVisiting->value("");
//     for(int i = 0; i < worker->getNumberOfVisits(); i++){
//         datesVisiting->insert(worker->getDateVisiting(i)->getDateWithTime().c_str());
//         datesVisiting->insert(",\n");
//     }
// }