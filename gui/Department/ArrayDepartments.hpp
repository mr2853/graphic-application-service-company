#ifndef ARRAY_DEPARTMENTS_HPP
#define ARRAY_DEPARTMENTS_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Department.hpp"
#include "../ArrayWorkers.hpp"

class ArrayDepartments : public ArrayWorkers<Department>{
public:
    ArrayDepartments();
    ArrayDepartments(vector<Department*> *array);
    virtual ~ArrayDepartments();
    string getText(int row, int column);
    string horizontalHeader(int column);
};
#endif