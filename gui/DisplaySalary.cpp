#include "DisplaySalary.hpp"
#include <sstream>
#include <FL/Fl_Text_Buffer.H>
using namespace std;
DisplaySalary::DisplaySalary(int x, int y, int w, int h, const char* l) : Fl_Group(x, y, w, h, l)
{
    boxDep2 = new Fl_Box(x, y, 300, 50);
    boxDep1 = new Fl_Box(x, y, 300, 50);
    boxComp2 = new Fl_Box(x, y+80, 300, 50);
    boxComp1 = new Fl_Box(x, y+80, 300, 50);

    boxDep1->align(FL_ALIGN_LEFT);
    boxDep2->align(FL_ALIGN_TOP);
    boxComp1->align(FL_ALIGN_LEFT);
    boxComp2->align(FL_ALIGN_TOP);
    
    boxDep1->box(FL_UP_BOX);
    boxDep2->box(FL_DOWN_BOX);
    boxComp1->box(FL_UP_BOX);
    boxComp2->box(FL_DOWN_BOX);
    
    // boxDep1->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    // boxDep2->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    // boxComp1->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    // boxComp2->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);

    //refresh();
    this->end();
}
DisplaySalary::~DisplaySalary(){}

void DisplaySalary::refresh()
{
    if(min1 == -1 || min2 == -1 || current == -1 || max1 == -1 || max2 == -1)
    {
        return;
    }
    boxDep1->copy_label(to_string(min1).c_str());
    boxComp1->copy_label(to_string(min2).c_str());

    stringstream sstream;
    sstream << max1;
    boxDep2->resize(boxDep2->x(), boxDep2->y(), boxDep2->w(), boxDep2->h());
    boxDep2->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << min1;
    boxDep1->resize(boxDep1->x(), boxDep1->y(), boxDep2->w() * (current / max1), boxDep1->h());
    boxDep1->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << current << "/" << max1;
    boxDep2->copy_label(sstream.str().c_str());
    

    sstream.str("");
    sstream << max2;
    boxComp2->resize(boxComp2->x(), boxComp2->y(), boxComp2->w(), boxComp2->h());
    boxComp2->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << min2;
    boxComp1->resize(boxComp1->x(), boxComp1->y(), boxComp2->w() * (current / max2), boxComp1->h());
    boxComp1->copy_label(sstream.str().c_str());
    sstream.str("");
    sstream << current << "/" << max2;
    boxComp2->copy_label(sstream.str().c_str());
}
double DisplaySalary::getMin1()
{
    return min1;
}
void DisplaySalary::setMin1(double min1)
{
    if(min1<0){return;}
    this->min1 = min1;
    this->refresh();
}
double DisplaySalary::getMin2()
{
    return min2;
}
void DisplaySalary::setMin2(double min2)
{
    if(min2<0){return;}
    this->min2 = min2;
    this->refresh();
}
double DisplaySalary::getCurrent()
{
    return current;
}
void DisplaySalary::setCurrent(double current)
{
    if(current<0){return;}
    this->current = current;
    this->refresh();
}
double DisplaySalary::getMax1()
{
    return max1;
}
void DisplaySalary::setMax1(double max1)
{
    if(max1<0){return;}
    this->max1 = max1;
    this->refresh();
}
double DisplaySalary::getMax2()
{
    return max2;
}
void DisplaySalary::setMax2(double max2)
{
    if(max2<0){return;}
    this->max2 = max2;
    this->refresh();
}