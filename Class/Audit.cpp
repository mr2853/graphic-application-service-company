#include "Audit.hpp"
#include "../Util.hpp"

Audit::Audit(){}
Audit::~Audit(){}
Audit::Audit(string in)
{
    vector<string> parts = tokenization(in, ":", ",", "Audit");
    if(parts.size() == 2){
        this->auditor = new Auditor(parts.at(0));
	    this->date = new Date(parts.at(1));
    }
}
Audit::Audit(Auditor* auditor, Date* date) : auditor(auditor), date(date){}

Auditor* Audit::getAuditor() {
	return auditor;
}
void Audit::setAuditor(Auditor *auditor) {
	this->auditor = auditor;
}
Date* Audit::getDate() {
	return date;
}
void Audit::setDate(Date *date) {
	this->date = date;
}
vector<Audit*> Audit::readArray(string in)
{
    vector<Audit*> array = vector<Audit*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("]#Audit") != std::string::npos){
            index = in.find("]#Audit");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else if(in.find("Audit[") != std::string::npos){
            index = in.find_last_of(">");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        index = s.find("[");
        type1 = s.substr(0, index);
        Audit *d = new Audit(s);
        array.push_back(d);
    }
    return array;
};
//vector<Audit*> Audit::readData(string in)
