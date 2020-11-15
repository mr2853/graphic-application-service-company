#ifndef ARRAY_DEPARTMENTS_HPP
#define ARRAY_DEPARTMENTS_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../AbstractTableModel.hpp"
#include "../../Class/Department.hpp"

class ArrayDepartments : public AbstractTableModel<Department *>{
private:
    vector<Department *> *departments;
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int red, Department* element);
    virtual Department* getRow(int red);
    virtual string getText(int red, int kolona);
    virtual string horizontalHeader(int kolona);
    virtual string verticalHeader(int red);
    virtual void pushRow(int red, Department* element);
    virtual void removeRow(int red);
    void write(ostream &output);
    void read(istream &input);
    ArrayDepartments();
    ArrayDepartments(vector<Department*> *departments);
    virtual ~ArrayDepartments();
    void add(Department *p);
    Department* getDepartment(int in);
};
#endif