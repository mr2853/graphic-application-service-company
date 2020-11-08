#ifndef ARRAY_AUDITORS_HPP
#define ARRAY_AUDITORS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "AbstractTableModel.hpp"
#include "../Class/Auditor.hpp"

class ArrayAuditors : public AbstractTableModel<Auditor *>{
private:
    vector<Auditor *> *auditors;
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int red, Auditor* element);
    virtual Auditor* getRow(int red);
    virtual string getText(int red, int kolona);
    virtual string horizontalHeader(int kolona);
    virtual string verticalHeader(int red);
    virtual void pushRow(int red, Auditor* element);
    virtual void removeRow(int red);
    void write(ostream &output);
    void read(istream &input);
    ArrayAuditors();
    ArrayAuditors(vector<Auditor*> *auditors);
    virtual ~ArrayAuditors();
    void add(Auditor *p);
    Auditor* getAuditor(int in);
};


#endif