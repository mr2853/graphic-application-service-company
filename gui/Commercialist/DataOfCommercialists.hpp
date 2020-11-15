#ifndef DATA_OF_COMMERCIALISTS_HPP
#define DATA_OF_COMMERCIALISTS_HPP
#include <iostream>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Group.H>

#include "CommercialistTable.hpp"
#include "../../Class/Commercialist.hpp"
#include "../DisplayWorker.hpp"
#include "DisplayCommercialist.hpp"
#include "ArrayCommercialists.hpp"
#include "../MainWindow.hpp"

class DataOfCommercialists : public Fl_Group, protected AbstractDisplay<Commercialist *>{
protected:
    ArrayCommercialists *commercialists;
    DisplayCommercialist *displayCommercialist;
    CommercialistTable *commercialistTable;
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
    void elementPushed(int indeks, Commercialist *element);
    void elementRemoved(int indeks);

    void updateLabel();
    void checkButtons();

public:
    DataOfCommercialists(int x, int y, int w, int h, ArrayCommercialists *commercialists, void *mainWindow, const char *l=0);
    virtual ~DataOfCommercialists();
    virtual void setDisplay(int indeks);
    void addCommercialist(Fl_Widget *widget, void *data);
    //Company& getCompany();
    void refreshTable();
    CommercialistTable* getCommercialistTable();
    void addCommercialist(Commercialist* a);
    int getCurrent();
    int numberOfCommercialists();
    void hideGroup();
};


#endif