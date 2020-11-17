#ifndef ARRAY_COMPANIES_HPP
#define ARRAY_COMPANIES_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Company.hpp"
#include "../ArrayWorkers.hpp"

class ArrayCompanies : public ArrayWorkers<Company>{
public:
    ArrayCompanies();
    ArrayCompanies(vector<Company*> *array);
    virtual ~ArrayCompanies();
    string getText(int row, int column);
    string horizontalHeader(int column);
    int numberOfColumns();
};
#endif