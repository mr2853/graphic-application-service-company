#include "DisplaySalary.hpp"
#include <sstream>
#include <FL/Fl_Text_Buffer.H>
using namespace std;
DisplaySalary::DisplaySalary(int x, int y, int w, int h, const char* l) : Fl_Group(x, y, w, h, l)
{
    boxDep1 = new Fl_Box(x, y, 300, 50);
    boxDep2 = new Fl_Box(x, y, 300, 50);
    boxDep3 = new Fl_Box(x, y, 300, 50);
    boxDep4 = new Fl_Box(x, y, 300, 50);

    boxComp1 = new Fl_Box(x, y+80, 300, 50);
    boxComp2 = new Fl_Box(x, y+80, 300, 50);
    boxComp3 = new Fl_Box(x, y+80, 300, 50);
    boxComp4 = new Fl_Box(x, y+80, 300, 50);

    boxDep1->align(FL_ALIGN_LEFT);
    boxDep2->align(FL_ALIGN_RIGHT);
    boxDep3->align(FL_ALIGN_TOP_RIGHT);
    boxDep4->align(FL_ALIGN_BOTTOM_RIGHT);

    boxComp1->align(FL_ALIGN_LEFT);
    boxComp2->align(FL_ALIGN_RIGHT);
    boxComp3->align(FL_ALIGN_TOP_RIGHT);
    boxComp4->align(FL_ALIGN_BOTTOM_RIGHT);
    
    boxDep1->box(FL_UP_BOX);
    boxDep2->box(FL_UP_BOX);
    boxDep3->box(FL_UP_BOX);
    boxDep4->box(FL_UP_BOX);

    boxComp1->box(FL_UP_BOX);
    boxComp2->box(FL_UP_BOX);
    boxComp3->box(FL_UP_BOX);
    boxComp4->box(FL_UP_BOX);
    
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
    
    sstream.str("");
    sstream << min1;
    boxDep1->resize(boxDep1->x(), boxDep1->y(), boxDep1->w(), boxDep1->h());
    boxDep1->copy_label(sstream.str().c_str());
    
    sstream.str("");
    sstream << max1;
    boxDep2->resize(boxDep2->x(), boxDep2->y(), boxDep2->w(), boxDep2->h());
    boxDep2->copy_label(sstream.str().c_str());

    sstream.str("");
    sstream << current;
    boxDep3->resize(boxDep3->x(), boxDep3->y(), boxDep2->w() * (current / max1), boxDep3->h());
    boxDep3->copy_label(sstream.str().c_str());


    sstream.str("");
    sstream << average1;
    boxDep4->resize(boxDep4->x(), boxDep4->y(), boxDep2->w() * (average1 / max1), boxDep4->h());
    boxDep4->copy_label(sstream.str().c_str());

    

    sstream.str("");
    sstream << min2;
    boxComp1->resize(boxComp1->x(), boxComp1->y(), boxComp1->w(), boxComp1->h());
    boxComp1->copy_label(sstream.str().c_str());
    
    sstream.str("");
    sstream << max2;
    boxComp2->resize(boxComp2->x(), boxComp2->y(), boxComp2->w(), boxComp2->h());
    boxComp2->copy_label(sstream.str().c_str());

    sstream.str("");
    sstream << current;
    boxComp3->resize(boxComp3->x(), boxComp3->y(), boxComp2->w() * (current / max2), boxComp3->h());
    boxComp3->copy_label(sstream.str().c_str());


    sstream.str("");
    sstream << average2;
    boxComp4->resize(boxComp4->x(), boxComp4->y(), boxComp2->w() * (average2 / max2), boxComp4->h());
    boxComp4->copy_label(sstream.str().c_str());
}
double DisplaySalary::getAverage1() const
{
    return min1;
}
void DisplaySalary::setAverage1(double average1)
{
    if(average1<0){return;}
    this->average1 = average1;
    this->refresh();
}
double DisplaySalary::getAverage2() const
{
    return min1;
}
void DisplaySalary::setAverage2(double average2)
{
    if(average2<0){return;}
    this->average2 = average2;
    this->refresh();
}
double DisplaySalary::getMin1() const
{
    return min1;
}
void DisplaySalary::setMin1(double min1)
{
    if(min1<0){return;}
    this->min1 = min1;
    this->refresh();
}
double DisplaySalary::getMin2() const
{
    return min2;
}
void DisplaySalary::setMin2(double min2)
{
    if(min2<0){return;}
    this->min2 = min2;
    this->refresh();
}
double DisplaySalary::getCurrent() const
{
    return current;
}
void DisplaySalary::setCurrent(double current)
{
    if(current<0){return;}
    this->current = current;
    this->refresh();
}
double DisplaySalary::getMax1() const
{
    return max1;
}
void DisplaySalary::setMax1(double max1)
{
    if(max1<0){return;}
    this->max1 = max1;
    this->refresh();
}
double DisplaySalary::getMax2() const
{
    return max2;
}
void DisplaySalary::setMax2(double max2)
{
    if(max2<0){return;}
    this->max2 = max2;
    this->refresh();
}