#ifndef WORKER_TABLE_HPP
#define WORKER_TABLE_HPP
#include <iostream>
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
#include "ArrayWorkers.hpp"

template<typename T>
class WorkerTable : public Fl_Table_Row, protected AbstractDisplay<T>{
protected:
    ArrayWorkers<T>* changed;
    virtual void draw_cell(TableContext context, int row = 0, int column = 0, int x = 0, int y = 0, int w = 0, int h = 0);

public:
    WorkerTable(int x, int y, int w, int h, ArrayWorkers<T>* changed, const char* l=0);
    virtual ~WorkerTable();
    WorkerTable();
    void add(T p);
    void refreshTable();
    virtual void elementPushed(int row, T element);
    virtual void elementRemoved(int row);
};

template<typename T>
WorkerTable<T>::WorkerTable(int x, int y, int w, int h, ArrayWorkers<T>* changed, const char* l) : Fl_Table_Row(x, y, w, h, l),
    changed(changed)
{
    this->end();
    col_resize_min(10);
    col_resize(1);
    col_header(1);
    row_header(1);
    // changed->subscribeListener(this);
    this->refreshTable();
}

template<typename T>
void WorkerTable<T>::draw_cell(TableContext context, int row, int column, int x, int y, int w, int h)
{
    
    switch (context)
    {
    case CONTEXT_COL_HEADER:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
            fl_color(FL_BLACK);
            fl_draw(changed->horizontalHeader(column).c_str(), x, y, w, h, FL_ALIGN_CENTER);
        }
        fl_pop_clip();
        return;
    }
    case CONTEXT_ROW_HEADER:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
            fl_color(FL_BLACK);
            fl_draw(changed->verticalHeader(row).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
        }
        fl_pop_clip();
        return;
    }
    case CONTEXT_CELL:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_color(row_selected(row) ? FL_SELECTION_COLOR : FL_WHITE);
            fl_rectf(x, y, w, h);
            fl_color(row_selected(row) ? FL_WHITE : FL_BLACK);
            fl_draw(changed->getText(row, column).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
            fl_color(color());
            fl_rect(x, y, w, h);
        }
        fl_pop_clip();
        return;
    }
    case CONTEXT_STARTPAGE:
    case CONTEXT_TABLE:
    case CONTEXT_ENDPAGE:
    case CONTEXT_RC_RESIZE:
    case CONTEXT_NONE:
        return;
    }
}

template<typename T>
void WorkerTable<T>::elementPushed(int row, T element)
{
    rows(changed->numberOfRows());
    cols(changed->numberOfColumns());
}

template<typename T>
void WorkerTable<T>::elementRemoved(int row)
{
    changed->removeRow(row);
    rows(changed->numberOfRows());
    cols(changed->numberOfColumns());
}

template<typename T>
WorkerTable<T>::~WorkerTable<T>()
{
}

template<typename T>
void WorkerTable<T>::add(T r)
{
    this->changed->add(r);
    rows(changed->numberOfRows());
    cols(changed->numberOfColumns());
}

template<typename T>
void WorkerTable<T>::refreshTable()
{
    rows(changed->numberOfRows());
    cols(changed->numberOfColumns());
}
#endif