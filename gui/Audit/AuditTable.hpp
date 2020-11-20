#ifndef AUDIT_TABLE_HPP
#define AUDIT_TABLE_HPP

#include <vector>
#include <string>
#include <sstream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Spinner.H>

#include "../../Class/Audit.hpp"
#include "ArrayAudits.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"
#include "../WorkerTable.hpp"

class AuditTable : public WorkerTable<Audit>
{
public:
    AuditTable(int x, int y, int w, int h, ArrayAudits *original, ArrayAudits *changed, const char* l=0);
    virtual ~AuditTable();
};

#endif