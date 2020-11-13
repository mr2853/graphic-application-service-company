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
    Auditor(string text);
    Auditor(string name, string lastname, Date *dateBirth, double salary, vector<Date*> *datesVisiting);

    virtual string getType();
    void pushDateVisiting(Date *date);
    Date* getDateVisiting(int indeks);
    void setDatesVisiting(vector<Date*> *datesVisiting);
    vector<Date*>* getDatesVisiting();
    virtual string verticalHeader(int row);
    virtual string horizontalHeader(int kolona);
    int getNumberOfVisits();
    
    //virtual void zapisi(ostream &output);
    //virtual void procitaj(istream &input);
    /*void write(ostream &output);
    void read(istream &input);

    friend ostream &operator<<(ostream &output, Auditor &auditor);
    friend istream &operator>>(istream &input, Auditor &auditor);
    friend ostream &operator<<(ostream &output, Auditor *auditor);
    friend istream &operator>>(istream &input, Auditor *auditor);*/
};

#endif