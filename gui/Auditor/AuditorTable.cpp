#include "AuditorTable.hpp"

AuditorTable::AuditorTable(int x, int y, int w, int h, ArrayAuditors *original, ArrayAuditors *changed, const char* l)
 : WorkerTable(x, y, w, h, original, changed, l){}

AuditorTable::~AuditorTable(){}