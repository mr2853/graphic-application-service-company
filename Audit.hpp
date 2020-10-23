#ifndef AUDIT_HPP
#define AUDIT_HPP
#include <iostream>

#include "Auditor.hpp"
#include "Date.hpp"

class Audit
{
private:
    Auditor *auditor;
    Date *date;
public:
    Audit();
    ~Audit();
    Audit(Auditor* auditor, Date* date);

    Auditor* getAuditor();

	void setAuditor(Auditor *auditor);

	Date* getDate();

	void setDate(Date *date);
};


#endif