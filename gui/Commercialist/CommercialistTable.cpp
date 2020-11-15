#include "CommercialistTable.hpp"

CommercialistTable::CommercialistTable(int x, int y, int w, int h, ArrayCommercialists *commercialists) : Fl_Table_Row(x, y, w, h),
    commercialists(commercialists)
{
    this->end();
    /*commercialists = new ArrayCommercialists(company.getCompanyAuditors());
    vector<Commercialist*> *a = company.getCompanyAuditors();
    for(Commercialist *aud : *a){
        commercialists->add(aud);
        cout << "name: " << commercialists->getElement(0)->getName() << endl;
    }*/
    //cout << "tableName: " << commercialists->getElement(0)->getName() << endl;
    col_resize_min(10);
    col_resize(1);
    col_header(1);
    row_header(1);
    commercialists->subscribeListener(this);
    this->refreshTable();
}
void CommercialistTable::draw_cell(TableContext context, int red, int kolona, int x, int y, int w, int h)
{
    // for(int i=0; i<commercialists->numberOfElement(); i++){
    //     cout << "lastname:" << commercialists->getCommercialist(i)->getLastname() << endl;
    //     cout << "Salary:" << commercialists->getCommercialist(i)->getSalary() << endl;
    //     cout << "DateBirth:" << commercialists->getCommercialist(i)->getDateBirth().getDateWithTime() << endl;
    //     cout << "DateVisiting:" << commercialists->getCommercialist(i)->getDateVisiting(0)->getDateWithTime() << endl;
    //     cout << "\n\n\n\n" << endl;
    // }
    switch (context)
    {
    case CONTEXT_COL_HEADER:
    {
        fl_push_clip(x, y, w, h);
        {
            fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, col_header_color());
            fl_color(FL_BLACK);
            fl_draw(commercialists->horizontalHeader(kolona).c_str(), x, y, w, h, FL_ALIGN_CENTER);
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
            fl_draw(commercialists->verticalHeader(red).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
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
            fl_draw(commercialists->getText(red, kolona).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
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
void CommercialistTable::elementPushed(int red, Commercialist *element)
{
    rows(commercialists->numberOfRows());
    cols(commercialists->numberOfColumns());
}
void CommercialistTable::elementRemoved(int red)
{
    rows(commercialists->numberOfRows());
    cols(commercialists->numberOfColumns());
}
CommercialistTable::~CommercialistTable()
{
}
void CommercialistTable::add(Commercialist *r)
{
    this->commercialists->add(r);
    rows(commercialists->numberOfRows());
    cols(commercialists->numberOfColumns());
}
void CommercialistTable::refreshTable()
{
    rows(commercialists->numberOfRows());
    cols(commercialists->numberOfColumns());
}
/*void CommercialistTable::removeAuditor(Commercialist *r)
{
    this->commercialists->removeAuditorsElem(r);
    rows(commercialists->numberOfRows());
    cols(commercialists->numberOfColumns());
}*/