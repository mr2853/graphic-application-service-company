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
    Audit(string in);
    Audit(Auditor* auditor, Date* date);

    Auditor* getAuditor();
	void setAuditor(Auditor *auditor);
	Date* getDate();
	void setDate(Date *date);
    void write(ostream &output);
    static vector<Audit *> readArray(string in);
    //static vector<Audit*> readData(string in);
};


#endif