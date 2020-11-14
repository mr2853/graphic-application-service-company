#include "AccountantTable.hpp"

AccountantTable::AccountantTable(int x, int y, int w, int h, ArrayAccountants *accountants) : Fl_Table_Row(x, y, w, h),
    accountants(accountants)
{
    this->end();
    /*accountants = new ArrayAccountants(company.getCompanyAuditors());
    vector<Accountant*> *a = company.getCompanyAuditors();
    for(Accountant *aud : *a){
        accountants->add(aud);
        cout << "name: " << accountants->getElement(0)->getName() << endl;
    }*/
    //cout << "tableName: " << accountants->getElement(0)->getName() << endl;
    col_resize_min(10);
    col_resize(1);
    col_header(1);
    row_header(1);
    accountants->subscribeListener(this);
    this->refreshTable();
}
void AccountantTable::draw_cell(TableContext context, int red, int kolona, int x, int y, int w, int h)
{
    // for(int i=0; i<accountants->numberOfElement(); i++){
    //     cout << "lastname:" << accountants->getAccountant(i)->getLastname() << endl;
    //     cout << "Salary:" << accountants->getAccountant(i)->getSalary() << endl;
    //     cout << "DateBirth:" << accountants->getAccountant(i)->getDateBirth().getDateWithTime() << endl;
    //     cout << "DateVisiting:" << accountants->getAccountant(i)->getDateVisiting(0)->getDateWithTime() << endl;
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
            fl_draw(accountants->horizontalHeader(kolona).c_str(), x, y, w, h, FL_ALIGN_CENTER);
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
            fl_draw(accountants->verticalHeader(red).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
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
            fl_draw(accountants->getText(red, kolona).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
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
void AccountantTable::elementPushed(int red, Accountant *element)
{
    rows(accountants->numberOfRows());
    cols(accountants->numberOfColumns());
}
void AccountantTable::elementRemoved(int red)
{
    rows(accountants->numberOfRows());
    cols(accountants->numberOfColumns());
}
AccountantTable::~AccountantTable()
{
}
void AccountantTable::add(Accountant *r)
{
    this->accountants->add(r);
    rows(accountants->numberOfRows());
    cols(accountants->numberOfColumns());
}
void AccountantTable::refreshTable()
{
    rows(accountants->numberOfRows());
    cols(accountants->numberOfColumns());
}
/*void AccountantTable::removeAuditor(Accountant *r)
{
    this->accountants->removeAuditorsElem(r);
    rows(accountants->numberOfRows());
    cols(accountants->numberOfColumns());
}*/