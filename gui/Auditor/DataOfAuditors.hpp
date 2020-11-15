#ifndef DATA_OF_AUDITORS_HPP
#define DATA_OF_AUDITORS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "AuditorTable.hpp"
#include "../../Class/Auditor.hpp"
#include "../DisplayWorker.hpp"
#include "DisplayAuditor.hpp"
#include "ArrayAuditors.hpp"
#include "../MainWindow.hpp"

class DataOfAuditors : public Fl_Group, protected AbstractDisplay<Auditor *>{
protected:
    ArrayAuditors *auditors;
    DisplayAuditor *displayAuditor;
    AuditorTable *auditorTable;
    int current = 0;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;
    //Company &company;
    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, Auditor *element);
    void elementRemoved(int indeks);
    void isArrayEmpty();

    void updateLabel();
    void checkButtons();

public:
    DataOfAuditors(int x, int y, int w, int h, ArrayAuditors *auditors, void *mainWindow, const char *l=0);
    virtual ~DataOfAuditors();
    virtual void setDisplay(int indeks);
    void addAuditor(Fl_Widget *widget, void *data);
    //Company& getCompany();
    void refreshTable();
    AuditorTable* getAuditorTable();
    void addAuditor(Auditor* a);
    int getCurrent();
    int numberOfAuditors();
    void hideGroup();
};


#endif