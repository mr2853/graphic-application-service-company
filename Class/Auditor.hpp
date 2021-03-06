#ifndef AUDITOR_HPP
#define AUDITOR_HPP
#include <iostream>
#include <vector>

#include "Date.hpp"
#include "AbstractWorker.hpp"

using namespace std;

class Auditor : public AbstractWorker{
private:
    vector<Date*> *datesVisiting;
    const string type = "Auditor";

public:
    Auditor();
    ~Auditor();
    Auditor(string text, int changed);
    Auditor(string name, string lastname, Date *dateBirth, double salary);
    Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date*> *datesVisiting);

    virtual string getType() const;
    void pushDateVisiting(Date *date);
    Date* getDateVisiting(int indeks);
    void setDatesVisiting(vector<Date*> *datesVisiting);
    vector<Date*>* getDatesVisiting();
    virtual string verticalHeader(int row);
    virtual string horizontalHeader(int kolona);
    int getNumberOfVisits() const;
    bool isAvailabe(Date* date);
    void addDateVisiting(Date* date);
    void removeDateVisiting(Date* date, int original=0);
    virtual void write(ostream &output, void *d);
    virtual void setDeleted();
};

#endif