#include "AuditorTable.hpp"

AuditorTable::AuditorTable(int x, int y, int w, int h, ArrayAuditors *auditors) : Fl_Table_Row(x, y, w, h), auditors(auditors)
{
    this->auditors = new ArrayAuditors();
    this->end();
    col_resize_min(10);
    col_resize(1);
    col_header(1);
    row_header(1);
    auditors->subscribeListener(this);
}
void AuditorTable::draw_cell(TableContext context, int red, int kolona, int x, int y, int w, int h)
{
    cout << context << endl;
    switch (context)
    {
    case CONTEXT_COL_HEADER:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
            fl_color(FL_BLACK);
            fl_draw(auditors->horizontalHeader(kolona).c_str(), x, y, w, h, FL_ALIGN_CENTER);
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
            fl_draw(auditors->verticalHeader(red).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
        }
        fl_pop_clip();
        return;
    }
    case CONTEXT_CELL:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_color(row_selected(red) ? FL_SELECTION_COLOR : FL_WHITE);
            fl_rectf(x, y, w, h);
            fl_color(row_selected(red) ? FL_WHITE : FL_BLACK);
            fl_draw(auditors->getText(red, kolona).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
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
void AuditorTable::elementPushed(int red, Auditor *element)
{
    rows(auditors->numberOfRows());
    cols(auditors->numberOfColumns());
}
void AuditorTable::elementRemoved(int red)
{
    rows(auditors->numberOfRows());
    cols(auditors->numberOfColumns());
}
AuditorTable::~AuditorTable()
{
}
void AuditorTable::add(Auditor *r)
{
    this->auditors->add(r);
    rows(auditors->numberOfRows());
    cols(auditors->numberOfColumns());
}
/*void AuditorTable::removeAuditor(Auditor *r)
{
    this->auditors->removeAuditorsElem(r);
    rows(auditors->numberOfRows());
    cols(auditors->numberOfColumns());
}*/