#include "DisplayWorker.hpp"
DisplayWorker::DisplayWorker(int x, int y, int w, int h, const char *l=0)
 : Fl_Group(x,y,w,h,l){

    name = new Fl_Input(x, y, 100, 40, "Name:");
    lastName = new Fl_Input(x, y+50, 100, 40, "Last name:");
    dateBirth = new Fl_Input(x, y+100, 100, 40, "Date birth:");
    salary = new Fl_Input(x, y+150, 100, 40, "Salary:");

    this->end();
}
DisplayWorker::~DisplayWorker(){}
void DisplayWorker::displayWorker(AbstractWorker *worker)
{
    //this->worker = worker;
    name->value(worker->getName().c_str());
    lastName->value(worker->getLastname().c_str());
    dateBirth->value(worker->getDateBirth().getDateWithTime().c_str());
    salary->value(to_string(worker->getSalary()).c_str());
}

string DisplayWorker::getValueName()
{
    return name->value();
}
string DisplayWorker::getValueLastName()
{
    return lastName->value();
}
Date* DisplayWorker::getValueDateBirth()
{
    string t = dateBirth->value();
    int index = t.find("-");
    int hour = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    index = t.find("-");
    int minute = stoi(t.substr(0, index));
    t.erase(0, index+1);

    index = t.find("-");
    int day = stoi(t.substr(0, index));
    t.erase(0, index+1);

    index = t.find("-");
    int month = stoi(t.substr(0, index));
    t.erase(0, index+1);

    index = t.find("-");
    int year = stoi(t.substr(0, index));
    t.erase(0, index);

    Date *d = new Date(hour, minute, day, month, year);
    return d;
}
string DisplayWorker::getValueSalary()
{
    return salary->value();
}