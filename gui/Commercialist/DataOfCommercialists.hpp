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
#include "../DataOfWorker.hpp"

class DataOfCommercialists : public DataOfWorker<Commercialist>{
protected:
    DisplayCommercialist *displayCommercialist;

    static void add(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *d);
public:
    DataOfCommercialists(int x, int y, int w, int h, ArrayCommercialists *original, ArrayCommercialists *changed, Company *company, void *mainWindow, const char *l=0);
    virtual ~DataOfCommercialists();
    virtual void setDisplay(int indeks);
    void hideGroup();
};


#endif