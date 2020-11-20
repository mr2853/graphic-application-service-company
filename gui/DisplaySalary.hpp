#ifndef DISPLAY_SALARY_HPP
#define DISPLAY_SALARY_HPP
#include <iostream>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Line_Dial.H>


class DisplaySalary : protected Fl_Group{
protected:
    double min1 = -1;
    double max1 = -1;
    double current = -1;
    double min2 = -1;
    double max2 = -1;
    Fl_Box *boxDep1;
    Fl_Box *boxDep2;
    
    Fl_Box *boxComp1;
    Fl_Box *boxComp2;
public:
    DisplaySalary(int x, int y, int w, int h, const char* l=0);
    virtual ~DisplaySalary();
    double getMin1();
    void setMin1(double min1);
    double getMin2();
    void setMin2(double min2);
    double getCurrent();
    void setCurrent(double current);
    double getMax1();
    void setMax1(double max1);
    double getMax2();
    void setMax2(double max2);
    void refresh();
};


#endif