#include "Audit.hpp"
#include "../Util.hpp"

Audit::Audit(){}
Audit::~Audit()
{
};
Audit::Audit(string in, int changed)
{
    vector<string> parts = tokenization(in, ":", ",", "Audit", changed);
    if(parts.size() == 2){
        this->auditor = new Auditor(parts.at(0), changed);
	    this->date = new Date(parts.at(1), changed);
    }
    else if(parts.size() == 3){
        this->auditor = new Auditor(parts.at(1), changed);
	    this->date = new Date(parts.at(2), changed);
        this->setDeleted();
    }
}

void Audit::write(ostream &output, Audit *d)
{
    output << "Audit[deleted:";
    if(d->deleted)
    {
        output << "true";
    }
    else
    {
        output << "false";
    }
    
    output << ",auditor:";
    d->auditor->write(output, d->auditor);
    output << ",date:";
    d->date->write(output, d->date);
    output << "]";
}

Audit::Audit(Auditor* auditor, Date* date) : auditor(auditor), date(date){}

Auditor* Audit::getAuditor() {
	return auditor;
}
void Audit::setAuditor(Auditor *auditor) {
	this->auditor = auditor;
}
bool Audit::isDeleted() {
	return deleted;
}
void Audit::setDeleted() {
    auditor->setDeleted();
    date->setDeleted();
	deleted = true;
}
Date* Audit::getDate() {
	return date;
}
void Audit::setDate(Date *date) {
	this->date = date;
}
string Audit::getData(int column)
{
    if (column == 0)
    {
        return this->getDate()->getDateWithTime();
    }
    else if (column == 1)
    {
        return this->getAuditor()->getName();
    }
    else if (column == 2)
    {
        return this->getAuditor()->getLastname();
    }
    else if (column == 3)
    {
        return this->getAuditor()->getDateBirth()->getDate();
    }
    return "";
}
vector<Audit*>* Audit::readArray(string in, int changed)
{
    vector<Audit*> *array = new vector<Audit*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("]$Audit") != std::string::npos){
            index = in.find("]$Audit");
            text.push_back(in.substr(0, index+1));
            in.erase(0, index + 2);
        }
        else if(in.find("Audit[") != std::string::npos){
            index = in.find("]]>]");
            text.push_back(in.substr(0, index+2));
            in.erase(0, index + 3);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        if(changed == 1)
        {
            string someText = s;
            index = someText.find(":");
            someText.erase(0,index+1);
            index = someText.find(",");
            string type = someText.substr(0, index);
            if(type == "true")
            {
                continue;
            }
        }
        index = s.find("[");
        s = s.substr(index, s.length());
        array->push_back(new Audit(s, changed));
    }
    return array;
};
