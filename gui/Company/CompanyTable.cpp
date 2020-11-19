#include "CompanyTable.hpp"

CompanyTable::CompanyTable(int x, int y, int w, int h, ArrayWorkers<Company> *array, const char* l) : WorkerTable(x, y, w, h, array, l){}
CompanyTable::~CompanyTable(){}