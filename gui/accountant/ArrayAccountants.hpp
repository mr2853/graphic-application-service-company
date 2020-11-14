#ifndef ARRAY_ACCOUNTANT_HPP
#define ARRAY_ACCOUNTANT_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Accountant.hpp"

class ArrayAccountants : public AbstractTableModel<Accountant *>{
private:
    vector<Accountant *> *accountants;
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int red, Accountant* element);
    virtual Accountant* getRow(int red);
    virtual string getText(int red, int kolona);
    virtual string horizontalHeader(int kolona);
    virtual string verticalHeader(int red);
    virtual void pushRow(int red, Accountant* element);
    virtual void removeRow(int red);
    void write(ostream &output);
    void read(istream &input);
    ArrayAccountants();
    ArrayAccountants(vector<Accountant*> *accountants);
    virtual ~ArrayAccountants();
    void add(Accountant *p);
    Accountant* getAccountant(int in);
};


#endif