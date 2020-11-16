#ifndef DATA_OF_WORKER_HPP
#define DATA_OF_WORKER_HPP
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/fl_message.H>
#include <FL/Fl_Button.H>
#include "ArrayWorkers.hpp"
#include "WorkerTable.hpp"
#include "AbstractDisplay.hpp"
#include "../Util.hpp"
#include "MainWindow.hpp"
#include "Department/DataOfDepartments.hpp"

template<typename T>
class DataOfWorker : public Fl_Group, protected AbstractDisplay<T*>{
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
    static void change(Fl_Widget *widget, void *data);
    static void nextElement(Fl_Widget *widget, void *data);
    static void previousElement(Fl_Widget *widget, void *data);
    static void add(Fl_Widget *widget, void *data);
    void elementPushed(int indeks, T *element);
    void elementRemoved(int indeks);
    void isArrayEmpty();

    void updateLabel();
    void checkButtons();
public:
    DataOfWorker(int x, int y, int w, int h, ArrayWorkers<T> *array, void *mainWindow, const char *l=0);
    virtual ~DataOfWorker();
    virtual void setDisplay(int indeks);
    void addElement(Fl_Widget *widget, void *data);
    void refreshTable();
    WorkerTable<T>* getTable();
    void addElement(T* a);
    int getCurrent();
    int sizeOfArray();
    void hideGroup();
    T* getElement(int index);
};
template<typename T>
void DataOfWorker<T>::setDisplay(int index){}

template<typename T>
T* DataOfWorker<T>::getElement(int index)
{
    return array->getElement(index);
}

template<typename T>
WorkerTable<T>* DataOfWorker<T>::getTable()
{
    return table;
}

template<typename T>
void DataOfWorker<T>::addElement(T* a)
{
    array->add(a);
}

template<typename T>
int DataOfWorker<T>::sizeOfArray()
{
    return array->numberOfElement();
}

template<typename T>
DataOfWorker<T>::DataOfWorker(int x, int y, int w, int h, ArrayWorkers<T> *array, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), array(array)
 {
    vector<Fl_Widget*> *data = (vector<Fl_Widget*>*)d;
    MainWindow *main = (MainWindow*)data->at(0);
    DataOfDepartments *parent = (DataOfDepartments*)data->at(1);

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
    //btnView->callback(DataOfWorker<T>::view, ev);
    btnRemove->callback(DataOfWorker<T>::removeElem, this);

    vector<Fl_Widget*> *v = new vector<Fl_Widget*>(0);
    v->push_back(parent);
    v->push_back(this);
    v->push_back(main);
    btnGoBack->callback(DataOfWorker<T>::goBack, v);
    
    btnChange->callback(change, this);

    if(array->numberOfElement() != 0){
        this->setDisplay(current);
    }
    
    array->subscribeListener(this);
    this->isArrayEmpty();
    this->checkButtons();
}

template<typename T>
void DataOfWorker<T>::add(Fl_Widget *widget, void *data){}

template<typename T>
void DataOfWorker<T>::change(Fl_Widget *widget, void *d){}

template<typename T>
void DataOfWorker<T>::updateLabel()
{
    stringstream sstream;
    sstream << typeid(T).name() <<" " << current + 1 << "/" << array->numberOfElement();
    this->copy_label(sstream.str().c_str());
}

template<typename T>
void DataOfWorker<T>::checkButtons()
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
void DataOfWorker<T>::nextElement(Fl_Widget *widget, void *d){
    DataOfWorker<T> *data = (DataOfWorker<T> *) d;
    if (data->current + 1 < data->array->numberOfElement())
    {
        data->current++;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

template<typename T>
void DataOfWorker<T>::previousElement(Fl_Widget *widget, void *d)
{
    DataOfWorker<T> *data = (DataOfWorker<T> *) d;
    if (data->current - 1 >= 0)
    {
        data->current--;
        data->setDisplay(data->current);
    }

    data->checkButtons();
}

template<typename T>
void DataOfWorker<T>::elementPushed(int indeks, T *element) {
    if(current == -1) {
        current = 0;
        setDisplay(current);
    }
    checkButtons();
    updateLabel();
}

template<typename T>
void DataOfWorker<T>::elementRemoved(int indeks) {
    checkButtons();
    updateLabel();
}

template<typename T>
int DataOfWorker<T>::getCurrent()
{
    return current;
}

template<typename T>
DataOfWorker<T>::~DataOfWorker<T>()
{
    delete table;
    delete btnChange;
    delete btnRemove;
    delete btnGoBack;
}

template<typename T>
void DataOfWorker<T>::isArrayEmpty()
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
void DataOfWorker<T>::hideGroup()
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
void DataOfWorker<T>::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfWorker<T> *data = (DataOfWorker<T>*)v->at(1);
    MainWindow *main = (MainWindow*)v->at(2);
    data->hideGroup();
    data->hide();
    main->remove(data);
    parent->unhide();
}

template<typename T>
void DataOfWorker<T>::removeElem(Fl_Widget *widget, void *data)
{
    DataOfWorker<T> *e = (DataOfWorker<T> *)data;
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
void DataOfWorker<T>::refreshTable()
{
    table->refreshTable();
}

#endif