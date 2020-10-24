#include "Audit.hpp"
#include "Util.hpp"

Audit::Audit(){}
Audit::~Audit(){}
Audit::Audit(string in)
{
    vector<string> parts = tokenization(in, ":", ",");
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

//vector<Audit*> Audit::readData(string in)
