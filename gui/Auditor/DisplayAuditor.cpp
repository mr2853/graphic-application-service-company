#include "DisplayAuditor.hpp"
#include "DataOfAuditors.hpp"
#include "../../Util.hpp"

DisplayAuditor::DisplayAuditor(int x, int y, int w, int h, const char *l)
: DisplayWorker(x, y, 200, 190, "")
{
    datesVisiting = new Fl_Multiline_Input(x, y+200, 100, 70, "Dates visiting:");
    datesVisiting->deactivate();
    this->end();
}
void DisplayAuditor::deactivate()
{
    DisplayWorker::deactivate();
    datesVisiting->deactivate();
}
bool DisplayAuditor::isInputsEmpty()
{
    if(!DisplayWorker::isInputsEmpty())
    {
        return false;
    }
    return true;
}
string DisplayAuditor::getType()
{
    return "DisplayAuditor";
}
DisplayAuditor::~DisplayAuditor()
{
    delete datesVisiting;
}
void DisplayAuditor::hide()
{
    this->label("");
    DisplayWorker::hide();
    this->datesVisiting->hide();
}
void DisplayAuditor::unhide()
{
    DisplayWorker::unhide();
    this->datesVisiting->show();
}
void DisplayAuditor::setDatesVisiting(string t)
{
    datesVisiting->value(t.c_str());
}

void DisplayAuditor::displayWorker(Auditor *worker)
{
    DisplayWorker::displayWorker(worker);
    datesVisiting->value("");
    for(int i = 0; i < worker->getNumberOfVisits(); i++){
        datesVisiting->insert(worker->getDateVisiting(i)->getDateWithTime().c_str());
        datesVisiting->insert(",\n");
    }
}