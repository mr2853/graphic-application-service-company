#include "AccountantTable.hpp"

AccountantTable::AccountantTable(int x, int y, int w, int h, ArrayAccountants *original, ArrayAccountants *changed, const char* l)
 : WorkerTable(x, y, w, h, original, changed, l){}

AccountantTable::~AccountantTable(){}