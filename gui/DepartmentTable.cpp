#include "DepartmentTable.hpp"

DepartmentTable::DepartmentTable(int x, int y, int w, int h, ArrayDepartments *departments) : Fl_Table_Row(x, y, w, h),
    departments(departments)
{
    this->end();
    /*departments = new ArrayAuditors(company.getCompanyAuditors());
    vector<Department*> *a = company.getCompanyAuditors();
    for(Department *aud : *a){
        departments->add(aud);
        cout << "name: " << departments->getElement(0)->getName() << endl;
    }*/
    //cout << "tableName: " << departments->getElement(0)->getName() << endl;
    col_resize_min(10);
    col_resize(1);
    col_header(1);
    row_header(1);
    
    departments->subscribeListener(this);
    this->refreshTable();
}
void DepartmentTable::draw_cell(TableContext context, int red, int kolona, int x, int y, int w, int h)
{
    // for(int i=0; i<departments->numberOfElement(); i++){
    //     cout << "lastname:" << departments->getAuditor(i)->getLastname() << endl;
    //     cout << "Salary:" << departments->getAuditor(i)->getSalary() << endl;
    //     cout << "DateBirth:" << departments->getAuditor(i)->getDateBirth().getDateWithTime() << endl;
    //     cout << "DateVisiting:" << departments->getAuditor(i)->getDateVisiting(0)->getDateWithTime() << endl;
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
            fl_draw(departments->horizontalHeader(kolona).c_str(), x, y, w, h, FL_ALIGN_CENTER);
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
            fl_draw(departments->verticalHeader(red).c_str(), x - 2, y, w, h, FL_ALIGN_RIGHT);
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
            fl_draw(departments->getText(red, kolona).c_str(), x + 2, y, w, h, FL_ALIGN_LEFT);
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
void DepartmentTable::elementPushed(int red, Department *element)
{
    rows(departments->numberOfRows());
    cols(departments->numberOfColumns());
}
void DepartmentTable::elementRemoved(int red)
{
    rows(departments->numberOfRows());
    cols(departments->numberOfColumns());
}
DepartmentTable::~DepartmentTable()
{
}
void DepartmentTable::add(Department *r)
{
    this->departments->add(r);
    rows(departments->numberOfRows());
    cols(departments->numberOfColumns());
}
void DepartmentTable::refreshTable()
{
    rows(departments->numberOfRows());
    cols(departments->numberOfColumns());
}
/*void DepartmentTable::removeAuditor(Department *r)
{
    this->departments->removeAuditorsElem(r);
    rows(departments->numberOfRows());
    cols(departments->numberOfColumns());
}*/