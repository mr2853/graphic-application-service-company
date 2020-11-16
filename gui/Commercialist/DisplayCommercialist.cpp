#include "DisplayCommercialist.hpp"
#include "DataOfCommercialists.hpp"
#include "../../Util.hpp"

DisplayCommercialist::DisplayCommercialist(int x, int y, int w, int h, const char *l)
: DisplayWorker(x, y, 200, 190, "")
{
    businessContact = new Fl_Multiline_Input(x, y+200, 200, 70, "Business contact:");
    
    this->end();
}
string DisplayCommercialist::getType()
{
    return "DisplayCommercialist";
}
DisplayCommercialist::~DisplayCommercialist()
{
    delete businessContact;
}
void DisplayCommercialist::hide()
{
    this->label("");
    DisplayWorker::hide();
    this->businessContact->hide();
}
void DisplayCommercialist::unhide()
{
    DisplayWorker::unhide();
    this->businessContact->show();
}
void DisplayCommercialist::setBusinessContact(string t)
{
    businessContact->value(t.c_str());
}
vector<string*>* DisplayCommercialist::getBusinessContacts(){
    string t = this->businessContact->value();
    ltrim(t);
    vector<string*> *contacts = new vector<string*>(0);
    if(t.empty()){
        return contacts;
    }
    int index;
    while(t.find(",") != string::npos){
        index = t.find(",");
        string t1 = t.substr(0, index);
        string s = ltrim(t1);
        contacts->push_back(new string(s));
        t.erase(0, index + 1);
    } 
    if(t.find(",") == string::npos){
        string t1 = t.substr(0, t.length());
        string s = ltrim(t1);
        contacts->push_back(new string(s));
        t.erase(0, t.length());
        return contacts;
    }
    return contacts;
}

void DisplayCommercialist::displayWorker(Commercialist *worker)
{
    DisplayWorker::displayWorker(worker);
    businessContact->value("");
    for(int i = 0; i < worker->getNumberOfBusinessContact(); i++){
        businessContact->insert((*worker->getContact(i)).c_str());
        businessContact->insert(",\n");
    }
}