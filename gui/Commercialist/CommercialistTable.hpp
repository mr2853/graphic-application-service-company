#ifndef COMMERCIALIST_TABLE_HPP
#define COMMERCIALIST_TABLE_HPP

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

#include "../../Class/Commercialist.hpp"
#include "ArrayCommercialists.hpp"
#include "../AbstractDisplay.hpp"
#include "../../Class/Company.hpp"
#include "../WorkerTable.hpp"

class CommercialistTable : public WorkerTable<Commercialist>
{
public:
    CommercialistTable(int x, int y, int w, int h, ArrayCommercialists *array);
    virtual ~CommercialistTable();
};

#endif