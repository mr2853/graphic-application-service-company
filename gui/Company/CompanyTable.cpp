#include "CompanyTable.hpp"

CompanyTable::CompanyTable(int x, int y, int w, int h, ArrayWorkers<Company> *original, ArrayWorkers<Company> *changed, const char* l)
 : WorkerTable(x, y, w, h, original, changed, l){}
CompanyTable::~CompanyTable(){}