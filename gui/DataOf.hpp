#ifndef DATA_OF_HPP
#define DATA_OF_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/fl_message.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <string>
#include "ArrayWorkers.hpp"
#include "WorkerTable.hpp"
#include "AbstractDisplay.hpp"
#include "../Util.hpp"
#include "../Class/Company.hpp"
#include "../Class/Department.hpp"

template<typename T>
class DataOf : public Fl_Group, protected AbstractDisplay<T*>{
protected:
    ArrayWorkers<T> *array;
    WorkerTable<T> *table;
    
    int current = 0;

    Fl_Button *btnChange;
    Fl_Button *btnRemove;
    Fl_Button *btnGoBack;
    Fl_Button *btnNext;
    Fl_Button *btnPrevious;
    Fl_Button *btnAdd;

    static void removeElem(Fl_Widget *widget, void *data);
    static void goBack(Fl_Widget *widget, void *data);
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    static void change(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, T *element);
    void elementRemoved(int indeks);
    void isArrayEmpty();

    void updateLabel();
    void checkButtons();
public:
    DataOf(int x, int y, int w, int h, ArrayWorkers<T> *array, void *mainWindow, const char *l=0);
    virtual ~DataOf();
    virtual void setDisplay(int indeks);
    void addElement(Fl_Widget *widget, void *data);
    void refreshTable();
    WorkerTable<T>* getTable();
    void addElement(T* a);
    int getCurrent();
    int sizeOfArray();
    void hideGroup();
    virtual void unhideGroup();
    T* getElement(int index);
};
template<typename T>
void DataOf<T>::setDisplay(int index){}

template<typename T>
T* DataOf<T>::getElement(int index)
{
    return array->getElement(index);
}

template<typename T>
WorkerTable<T>* DataOf<T>::getTable()
{
    return table;
}

template<typename T>
void DataOf<T>::addElement(T* a)
{
    array->add(a);
}

template<typename T>
int DataOf<T>::sizeOfArray()
{
    return array->numberOfElement();
}

template<typename T>
DataOf<T>::DataOf(int x, int y, int w, int h, ArrayWorkers<T> *array, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), array(array)
 {
    vector<void*> *data = new vector<void*>();
    data->push_back(d);

    table = new WorkerTable<T>(x+200, y+340, 400, 280, array);
    
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+300, y+300, 70, 30, "Add");
    btnRemove = new Fl_Button(x+380, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");
    btnPrevious = new Fl_Button(x+170, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+220, y, 45, 70, "@->");

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);

    btnAdd->callback(add, this);
    btnRemove->callback(removeElem, this);

    data->push_back(this);
    btnGoBack->callback(goBack, data);
    
    btnChange->callback(change, this);

    if(array->numberOfElement() != 0){
        this->setDisplay(current);
    }
    
    array->subscribeListener(this);
    this->isArrayEmpty();
    this->checkButtons();
}

template<typename T>
void DataOf<T>::add(Fl_Widget *widget, void *data){}

template<typename T>
void DataOf<T>::change(Fl_Widget *widget, void *d){}

template<typename T>
void DataOf<T>::updateLabel()
{
    stringstream sstream;
    string type = typeid(T).name();
    type = type.substr(1,type.length());
    sstream << type <<" " << current + 1 << "/" << array->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

template<typename T>
void DataOf<T>::checkButtons()
{
    if (current <= 0)
    {
        btnPrevious->deactivate();
    }
    else
    {
        btnPrevious->activate();
    }
    if (current >= array->numberOfElement() - 1)
    {
        btnNext->deactivate();
    }
    else
    {
        btnNext->activate();
    }
}

template<typename T>
void DataOf<T>::nextElement(Fl_Widget *widget, void *d){
    DataOf<T> *data = (DataOf<T> *) d;
    if (data->current + 1 < data->array->numberOfElement())
    {
        data->current++;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

template<typename T>
void DataOf<T>::previousElement(Fl_Widget *widget, void *d)
{
    DataOf<T> *data = (DataOf<T> *) d;
    if (data->current - 1 >= 0)
    {
        data->current--;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

template<typename T>
void DataOf<T>::elementPushed(int indeks, T *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}

template<typename T>
void DataOf<T>::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}

template<typename T>
int DataOf<T>::getCurrent()
{
    return current;
}

template<typename T>
DataOf<T>::~DataOf<T>()
{
    delete table;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
    delete btnNext;
    delete btnPrevious;
    delete btnAdd;
}

template<typename T>
void DataOf<T>::isArrayEmpty()
{
    if(array->numberOfElement() == 0)
    {
        btnChange->deactivate();
        btnRemove->deactivate();
        btnNext->deactivate();
        btnPrevious->deactivate();
    }
    else
    {
        btnChange->activate();
        btnRemove->activate();
        btnNext->activate();
        btnPrevious->activate();
    }
}

template<typename T>
void DataOf<T>::hideGroup()
{
    this->label("");
    this->table->hide();

    this->btnChange->hide();
    this->btnRemove->hide();
    this->btnGoBack->hide();
    this->btnNext->hide();
    this->btnPrevious->hide();
    this->btnAdd->hide();
}

template<typename T>
void DataOf<T>::unhideGroup()
{
    this->label("");
    this->table->show();

    this->btnChange->show();
    this->btnRemove->show();
    this->btnGoBack->show();
    this->btnNext->show();
    this->btnPrevious->show();
    this->btnAdd->show();
}

template<typename T>
void DataOf<T>::goBack(Fl_Widget *widget, void *d){}

template<typename T>
void DataOf<T>::removeElem(Fl_Widget *widget, void *data)
{
    DataOf<T> *e = (DataOf<T> *)data;
    int startRow;
    int endRow;
    int colLeft;
    int colRight;
    try{
        e->table->get_selection(startRow, colLeft, endRow, colRight);
        if(startRow == -1 || endRow == -1 || colLeft == -1 || colRight == -1)
        {
            throw UnselectedDataToRemove();
        }
    }
    catch(UnselectedDataToRemove e)
    {
        fl_message(e.what());
        return;
    }
    for (int i = endRow; i >= startRow; i--)
    {
        e->array->removeRow(i);
    }
    if(e->array->numberOfElement() == 0){
        e->setDisplay(0);
    }
    else{
        e->setDisplay(e->array->numberOfElement()-1);
    }
    e->updateLabel();
    e->isArrayEmpty();
    e->checkButtons();
}

template<typename T>
void DataOf<T>::refreshTable()
{
    table->refreshTable();
}

#endif