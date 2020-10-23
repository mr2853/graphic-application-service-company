#include "Audit.hpp"

Audit::Audit(){}
Audit::~Audit(){}
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