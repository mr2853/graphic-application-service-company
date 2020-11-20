#include "DepartmentTable.hpp"

DepartmentTable::DepartmentTable(int x, int y, int w, int h, ArrayDepartments *original, ArrayDepartments *changed, const char* l)
 : WorkerTable(x, y, w, h, original, changed, l){}
DepartmentTable::~DepartmentTable(){}