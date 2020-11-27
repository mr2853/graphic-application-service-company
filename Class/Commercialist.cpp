#include "Commercialist.hpp"
#include "../Util.hpp"
#include <string>
using namespace std;

Commercialist::Commercialist(){};
Commercialist::~Commercialist(){};
void Commercialist::setDeleted() {
	AbstractWorker::setDeleted();
}
Commercialist::Commercialist(string in, int changed)
{
    vector<string> parts = tokenization(in, ":", ",", "Commercialist", changed);
    if(parts.size() == 5){
       this->setName(parts.at(0));
       this->setLastname(parts.at(1));
       this->setDateBirth(new Date(parts.at(2), changed));
       this->setSalary(stod(parts.at(3)));

       vector<string*>* businessContact = new vector<string*>(0);

       int index1 = parts.at(4).find("<");
       string part = parts.at(4).substr(index1+1, parts.at(4).length());
       vector<string> a = tokenization(part, ":", "$");
       
       for(int i = 0; i < a.size(); i++){
           if(i == a.size()-1)
           {
               a.at(i) = a.at(i).substr(0, a.at(i).length()-2);
           }
           
           businessContact->push_back(new string(a.at(i)));
       }
       this->setBusinessContact(businessContact);
    }
    else if(parts.size() == 6){
        this->setName(parts.at(1));
        this->setLastname(parts.at(2));
        this->setDateBirth(new Date(parts.at(3), changed));
        this->setSalary(stod(parts.at(4)));

        vector<string*>* businessContact = new vector<string*>(0);
        string part = parts.at(5).substr(0, parts.at(5).length()-1);
        vector<string> a = tokenization(part, ":", "$");
        
        for(int i = 0; i < a.size(); i++){
            if(a.at(i).find(">") != string::npos)
            {
                int index = a.at(i).find(">");
                string left = a.at(i).substr(0, index);
                businessContact->push_back(new string(a.at(i).substr(0, index)));
                continue;
            }
            businessContact->push_back(new string(a.at(i)));
        }
        this->setBusinessContact(businessContact);
        this->setDeleted();
    }
}
Commercialist::Commercialist(string name, string lastname, Date *dateBirth, double salary) : AbstractWorker(name, lastname, dateBirth, salary){}

string* Commercialist::getContact(int indeks)
{
    return businessContact->at(indeks);
}
void Commercialist::pushContact(string* contact)
{
    businessContact->push_back(contact);
}
int Commercialist::getNumberOfBusinessContact()
{
    return businessContact->size();
}
void Commercialist::setBusinessContact(vector<string*> *businessContact)
{
    this->businessContact = businessContact;
}
string Commercialist::getType()
{
	return type;
}
void Commercialist::write(ostream &output, void *data)
{
    Commercialist *d = (Commercialist*)data;
    output << "Commercialist[";
    AbstractWorker::write(output, d);
    output << ",businessContact:<";
    for(int i = 0; i < d->businessContact->size(); i++)
    {
        output << "contact:" << *d->businessContact->at(i);
        if(i < d->businessContact->size()-1)
        {
            output << "$";
        }
    }
    output << ">]";
}