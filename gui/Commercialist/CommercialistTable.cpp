#include "CommercialistTable.hpp"

CommercialistTable::CommercialistTable(int x, int y, int w, int h, ArrayCommercialists *original, ArrayCommercialists *changed, const char* l)
         : WorkerTable(x, y, w, h, original, changed, l){}
CommercialistTable::~CommercialistTable(){}