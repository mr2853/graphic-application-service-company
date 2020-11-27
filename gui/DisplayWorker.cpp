#include "DisplayWorker.hpp"
#include "../Util.hpp"
#include <FL/fl_message.H>

DisplayWorker::DisplayWorker(int x, int y, int w, int h, const char *l=0) : Fl_Group(x,y,w,h,l){

    name = new Fl_Input(x, y, 100, 40, "Name:");
    lastName = new Fl_Input(x, y+50, 100, 40, "Last name:");
    dateBirth = new Fl_Input(x, y+100, 100, 40, "Date birth:");
    salary = new Fl_Value_Input(x, y+150, 100, 40, "Salary:");
    salary->precision(2);
    this->end();
}
bool DisplayWorker::isInputsEmpty()
{
    string a = name->value();
    string b = lastName->value();
    try{
        if(a.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Name of worker"));
        return false;
    }
    try{
        if(b.empty()){
            throw EmptyInput();
        }
    }
    catch(EmptyInput e)
    {
        fl_message(e.what("Lastname of worker"));
        return false;
    }
    return true;
}

string DisplayWorker::getType()
{
    return "DisplayWorker";
}
DisplayWorker::~DisplayWorker()
{
    delete name;
    delete lastName;
    delete dateBirth;
    delete salary;
}
void DisplayWorker::hide()
{
    this->label("");
    this->name->hide();
    this->lastName->hide();
    this->dateBirth->hide();
    this->salary->hide();
}
void DisplayWorker::unhide()
{
    this->name->show();
    this->lastName->show();
    this->dateBirth->show();
    this->salary->show();
}
void DisplayWorker::displayWorker(AbstractWorker *worker)
{
    name->value(worker->getName().c_str());
    lastName->value(worker->getLastname().c_str());
    dateBirth->value(worker->getDateBirth()->getDateWithTime().c_str());
    salary->value(worker->getSalary());
}

string DisplayWorker::getValueName()
{
    string s = name->value();
    ltrim(s);
    return s;
}
string DisplayWorker::getValueLastName()
{
    string s = lastName->value();
    ltrim(s);
    return s;
}
Date* DisplayWorker::getValueDateBirth()
{
    string t = dateBirth->value();
    ltrim(t);
    int index = 0;
    int counter = 0;
    string check = t;
    while(index != string::npos)
    {
        index = check.find("-");
        check.erase(0, index+1);
        counter++;
    }
    
    if(counter == 3)
    {
        if(!correctDate(t)){
            throw WrongDate();
        }
    }
    else
    {
        if(!correctDate(t,1)){
            throw WrongDate();
        }
    }
    
    index = t.find("-");
    int a = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    index = t.find("-");
    int b = stoi(t.substr(0, index));
    t.erase(0, index+1);
    int c = -1;
    int d = -1;
    if(t.find("-") != string::npos){
        index = t.find("-");
        c = stoi(t.substr(0, index));
        t.erase(0, index+1);
        
        index = t.find("-");
        d = stoi(t.substr(0, index));
        t.erase(0, index+1);
    }
    
    int e = stoi(t);
    
    Date *date = new Date(a,b,e);
    if(c != -1)
    {
        date = new Date(a,b,c,d,e);
    }
    
    return date;
}
double DisplayWorker::getValueSalary()
{
    return salary->value();
}