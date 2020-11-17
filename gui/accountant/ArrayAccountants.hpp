#ifndef ARRAY_ACCOUNTANT_HPP
#define ARRAY_ACCOUNTANT_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Accountant.hpp"

#include "../ArrayWorkers.hpp"

class ArrayAccountants : public ArrayWorkers<Accountant>{
public:
    ArrayAccountants();
    ArrayAccountants(vector<Accountant*> *array);
    virtual ~ArrayAccountants();
    int numberOfColumns();
    string getText(int red, int kolona);
    string horizontalHeader(int column);
};


#endif