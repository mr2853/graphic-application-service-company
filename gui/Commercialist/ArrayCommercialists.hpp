#ifndef ARRAY_COMMERCIALISTS_HPP
#define ARRAY_COMMERCIALISTS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Commercialist.hpp"

class ArrayCommercialists : public AbstractTableModel<Commercialist *>{
private:
    vector<Commercialist *> *commercialists;
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int red, Commercialist* element);
    virtual Commercialist* getRow(int red);
    virtual string getText(int red, int kolona);
    virtual string horizontalHeader(int kolona);
    virtual string verticalHeader(int red);
    virtual void pushRow(int red, Commercialist* element);
    virtual void removeRow(int red);
    void write(ostream &output);
    void read(istream &input);
    ArrayCommercialists();
    ArrayCommercialists(vector<Commercialist*> *commercialists);
    virtual ~ArrayCommercialists();
    void add(Commercialist *p);
    Commercialist* getCommercialist(int in);
};


#endif