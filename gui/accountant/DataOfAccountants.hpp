#ifndef DATA_OF_ACCOUNTANT_HPP
#define DATA_OF_ACCOUNTANT_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "AccountantTable.hpp"
#include "../../Class/Accountant.hpp"
#include "../DisplayWorker.hpp"
#include "DisplayAccountant.hpp"
#include "ArrayAccountants.hpp"
#include "../MainWindow.hpp"

class DataOfAccountants : public Fl_Group{
protected:
    ArrayAccountants *accountants;
    DisplayAccountant *displayAccountant;
    AccountantTable *accountantTable;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    //Company &company;

public:
    DataOfAccountants(int x, int y, int w, int h, ArrayAccountants *accountants, void *mainWindow, const char *l=0);
    virtual ~DataOfAccountants();
    
    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);

    void addAccountant(Fl_Widget *widget, void *data);
    //Company& getCompany();
    void refreshTable();
    AccountantTable* getAccountantTable();
    void addAccountant(Accountant* a);
    int numberOfAccountants();
    void hideGroup();
};


#endif