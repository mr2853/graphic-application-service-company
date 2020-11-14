#include "DisplayAuditor.hpp"
#include "DataOfAuditors.hpp"
#include "../../Util.hpp"

DisplayAuditor::DisplayAuditor(int x, int y, int w, int h, const char *l)
: DisplayWorker(x, y, 200, 190, "")
{
    datesVisiting = new Fl_Multiline_Input(x, y+200, 200, 70, "Dates visiting:");
    
    this->end();
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
vector<Date*>* DisplayAuditor::getDatesVisiting(){
    string t = this->datesVisiting->value();
    vector<Date*> *dates = new vector<Date*>();
    if(t.empty()){
        return dates;
    }
    int index;
    while(t.find(",") != string::npos){
        index = t.find(",");
        string subs = t.substr(0, index);
        vector<int> d = getDate(subs);
        t.erase(0, index + 1);
        dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
    }
    if(t.find(",") == string::npos){
        vector<int> d = getDate(t);
        t.erase(0, index + 1);
        dates->push_back(new Date(d.at(0), d.at(1), d.at(2), d.at(3), d.at(4)));
        return dates;
    }
    return dates;
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