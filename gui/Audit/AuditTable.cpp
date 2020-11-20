#include "AuditTable.hpp"

AuditTable::AuditTable(int x, int y, int w, int h, ArrayAudits *original, ArrayAudits *changed, const char* l)
 : WorkerTable(x, y, w, h, original, changed, l){}
AuditTable::~AuditTable(){}