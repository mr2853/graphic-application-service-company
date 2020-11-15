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

class DataOfAccountants : public Fl_Group, protected AbstractDisplay<Accountant *>{
protected:
    ArrayAccountants *accountants;
    DisplayAccountant *displayAccountant;
    AccountantTable *accountantTable;
    int current = 0;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;
    //Company &company;
    void updateLabel();
    void checkButtons();
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);

    void elementPushed(int indeks, Accountant *element);
    void elementRemoved(int indeks);

public:
    DataOfAccountants(int x, int y, int w, int h, ArrayAccountants *accountants, void *mainWindow, const char *l=0);
    virtual ~DataOfAccountants();
    
    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);

    void addAccountant(Fl_Widget *widget, void *data);
    virtual void setDisplay(int indeks);
    //Company& getCompany();
    void refreshTable();
    AccountantTable* getAccountantTable();
    void addAccountant(Accountant* a);
    int numberOfAccountants();
    void hideGroup();
    int getCurrent();
};


#endif