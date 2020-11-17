#ifndef ARRAY_AUDITS_HPP
#define ARRAY_AUDITS_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Audit.hpp"
#include "../ArrayWorkers.hpp"

class ArrayAudits : public ArrayWorkers<Audit>{
public:
    ArrayAudits();
    ArrayAudits(vector<Audit*> *array);
    virtual ~ArrayAudits();
    string getText(int row, int column);
    string horizontalHeader(int column);
};
#endif