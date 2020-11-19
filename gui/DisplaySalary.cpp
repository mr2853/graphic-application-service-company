#include "DisplaySalary.hpp"
#include <sstream>
#include <FL/Fl_Text_Buffer.H>
using namespace std;
DisplaySalary::DisplaySalary(int x, int y, int w, int h, const char* l) : Fl_Group(x, y, w, h, l)
{
    boxDep = new Fl_Box(x, y, 300, 50);
    boxComp = new Fl_Box(x, y+80, 300, 50);

    boxDep->box(FL_UP_BOX);
    boxComp->box(FL_UP_BOX);
    
    boxDep->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    boxComp->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);

    refresh();
    this->end();
}
DisplaySalary::~DisplaySalary(){}

void DisplaySalary::refresh()
{
    stringstream sstream;
    // sstream << max1;
    // boxDep->copy_label(sstream.str().c_str());
    // sstream.str("");
    // sstream << min1;
    // fl_color(FL_BLACK);
    // fl_line_style(0,2,0);
    fl_line(this->x()+this->x()/2, this->y(), this->x()+this->x()/2, this->y()+this->h());
    // boxDep->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << current;
    boxDep->copy_label("prvo");
    

    // sstream << max2;
    // boxComp->copy_label(sstream.str().c_str());
    // sstream.str("");
    // sstream << min2;
    // fl_line(boxComp->x() + this->w() * (min2 / max2), boxComp->y() + boxComp->h(), boxComp->x() + this->w() * (min2 / max2), boxComp->y());
    // boxComp->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << current;
    boxComp->copy_label("drugo");
}
double DisplaySalary::getMin1()
{
    return min1;
}
void DisplaySalary::setMin1(double min1)
{
    this->min1 = min1;
    this->refresh();
}
double DisplaySalary::getMin2()
{
    return min2;
}
void DisplaySalary::setMin2(double min2)
{
    this->min2 = min2;
    this->refresh();
}
double DisplaySalary::getCurrent()
{
    return current;
}
void DisplaySalary::setCurrent(double current)
{
    this->current = current;
    this->refresh();
}
double DisplaySalary::getMax1()
{
    return max1;
}
void DisplaySalary::setMax1(double max1)
{
    this->max1 = max1;
    this->refresh();
}
double DisplaySalary::getMax2()
{
    return max2;
}
void DisplaySalary::setMax2(double max2)
{
    this->max2 = max2;
    this->refresh();
}