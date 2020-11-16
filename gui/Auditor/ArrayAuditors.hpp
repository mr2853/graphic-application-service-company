#ifndef ARRAY_AUDITORS_HPP
#define ARRAY_AUDITORS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Auditor.hpp"
#include "../ArrayWorkers.hpp"

class ArrayAuditors : public ArrayWorkers<Auditor>{
public:
    ArrayAuditors();
    ArrayAuditors(vector<Auditor*> *array);
    virtual ~ArrayAuditors();
};

#endif