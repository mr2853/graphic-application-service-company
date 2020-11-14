#include "DataOfAccountants.hpp"
#include "../../Class/Accountant.hpp"
#include "../DataOfDepartments.hpp"
#include "../MainWindow.hpp"
#include <sstream>

using namespace std;

/*struct Event
{
    ArrayAccountants *accountants;
    AccountantTable *tabela;
    DisplayAccountant *displayAccountant;
};*/
AccountantTable* DataOfAccountants::getAccountantTable()
{
    return accountantTable;
}
void DataOfAccountants::addAccountant(Accountant* a)
{
    accountants->add(a);
}
int DataOfAccountants::numberOfAccountants()
{
    return accountants->numberOfElement();
}

DataOfAccountants::DataOfAccountants(int x, int y, int w, int h, ArrayAccountants *accountants, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), accountants(accountants)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);
    displayAccountant = new DisplayAccountant(x+50, y, 300, 390, accountants, this, "");
    accountantTable = new AccountantTable(x+200, y+340, 400, 280, accountants);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnRemove = new Fl_Button(x+370, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");

    //btnView->callback(DataOfAccountants::view, ev);
    btnRemove->callback(DataOfAccountants::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfAccountants::goBack, v);
    
    vector<Fl_Widget*> *v1 = new vector<Fl_Widget*>(0);
    v1->push_back(this);
    v1->push_back(displayAccountant);
    v1->push_back(accountantTable);
    btnChange->callback(change, v1);
    this->end();
}
DataOfAccountants::~DataOfAccountants()
{
    delete displayAccountant;
    delete accountantTable;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}
void DataOfAccountants::hideGroup()
{
    this->displayAccountant->hide();
    this->accountantTable->hide();
    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
}
void DataOfAccountants::change(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfAccountants *data = (DataOfAccountants*)v->at(0);
    DisplayAccountant *displayAccountant = (DisplayAccountant*)v->at(1);
    AccountantTable *accountantTable = (AccountantTable*)v->at(2);
    Accountant *a = data->accountants->getRow(displayAccountant->getCurrent());
    a->setName(displayAccountant->getValueName());
    a->setLastname(displayAccountant->getValueLastName());
    a->setSalary(stod(displayAccountant->getValueSalary()));
    a->setDateBirth(displayAccountant->getValueDateBirth());
    a->setBodyIssuedPermit(displayAccountant->getBodyIssuedPermit());
    a->setMaxAmountCompanyIncome(stod(displayAccountant->getMaxAmountCompanyIncome()));
    accountantTable->redraw();
}
void DataOfAccountants::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfAccountants *data = (DataOfAccountants*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

/*void DataOfAccountants::view(Fl_Widget *widget, void *data)
{
    Event *event = (Event *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    event->tabela->get_selection(startRow, colLeft, endRow, colRight);
    event->displayAccountant->displayAccountant(event->accountants->getElement(endRow));
}*/

void DataOfAccountants::removeElem(Fl_Widget *widget, void *data)
{
    DataOfAccountants *e = (DataOfAccountants *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    e->accountantTable->get_selection(startRow, colLeft, endRow, colRight);
    // cout << "Dodje" << endl;
    // cout << "size1:" << e->accountants->numberOfElement() << endl;
    for (int i = endRow; i >= startRow; i--)
    {
        e->accountants->removeRow(i);
        // e->accountantTable->rows(e->accountants->numberOfRows());
        // e->accountantTable->cols(e->accountants->numberOfColumns());
    }
    // cout << "prodje" << endl;
}

// Company& DataOfAccountants::getCompany()
// {
//     return company;
// }
void DataOfAccountants::refreshTable()
{
    accountantTable->refreshTable();
}
