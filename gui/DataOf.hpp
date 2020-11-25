#ifndef DATA_OF_HPP
#define DATA_OF_HPP
#include <iostream>
#include <fstream>
#include <FL/Fl_Group.H>
#include <FL/fl_message.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <string>
#include "ArrayWorkers.hpp"
#include "WorkerTable.hpp"
#include "AbstractDisplay.hpp"
#include "../Util.hpp"
#include "../Class/Company.hpp"
#include "../Class/Department.hpp"


template<typename T>
class DataOf : public Fl_Group, protected AbstractDisplay<T>{
protected:
    ArrayWorkers<T> *original;
    ArrayWorkers<T> *changed;
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
    void elementPushed(int indeks, T element);
    void elementRemoved(int indeks);
    void isArrayEmpty();


    void updateLabel();
    void checkButtons();
public:
    DataOf(int x, int y, int w, int h, ArrayWorkers<T> *original, ArrayWorkers<T> *changed, void *mainWindow, const char *l=0);
    virtual ~DataOf();
    virtual void setDisplay(int indeks);
    virtual void addToOriginal(T a);
    void addElement(Fl_Widget *widget, void *data);
    void refreshTable();
    WorkerTable<T>* getTable();
    void addElement(T a);
    int getCurrent();
    int sizeOfArray();
    void hideGroup();
    virtual void unhideGroup();
    T getElement(int index);
    // static void save(Fl_Widget *widget, void *data);
    ArrayWorkers<T>* getArrayOriginal();
};
template<typename T>
DataOf<T>::DataOf(int x, int y, int w, int h, ArrayWorkers<T> *original, ArrayWorkers<T> *changed, void *d, const char *l)
 : Fl_Group(x , y ,w ,h ,l), original(original), changed(changed)
 {
    // this->original = new ArrayWorkers<T>();
    // for(int i = 0; i < original->numberOfElement(); i++)
    // {
    //     this->original->add(original->getRow(i));
    // }
    // this->changed = new ArrayWorkers<T>();
    // for(int i = 0; i < changed->numberOfElement(); i++)
    // {
    //     this->changed->add(changed->getRow(i));
    // }

    vector<void*> *data = new vector<void*>();
    data->push_back(d);
    if(this->original == original)
    {
        cout << "\n\njednaki su\n\n" << endl;
    }
    else{
        cout << "\n\nnisu jednaki\n\n" << endl;
    }

    table = new WorkerTable<T>(x+200, y+340, 400, 280, changed);
    btnChange = new Fl_Button(x+220, y+300, 70, 30, "Change");
    btnAdd = new Fl_Button(x+300, y+300, 70, 30, "Add");
    btnRemove = new Fl_Button(x+380, y+300, 70, 30, "Remove");
    btnGoBack = new Fl_Button(x+460, y+300, 70, 30, "Go back");
    btnPrevious = new Fl_Button(x+250, y, 45, 70, "@<-");
    btnNext = new Fl_Button(x+300, y, 45, 70, "@->");
    cout << "doso dovde1" << endl;

    btnNext->callback(nextElement, this);
    btnPrevious->callback(previousElement, this);

    btnAdd->callback(add, this);
    btnRemove->callback(removeElem, this);

    data->push_back(this);
    btnGoBack->callback(goBack, data);
    
    btnChange->callback(change, this);
    cout << "doso dovde2" << endl;

    if(changed->numberOfElement() != 0){
        this->setDisplay(current);
    }
    
    // changed->subscribeListener(this);
    this->isArrayEmpty();
    this->checkButtons();
    cout << "doso dovde3" << endl;
}

template<typename T>
void DataOf<T>::setDisplay(int index){}

template<typename T>
T DataOf<T>::getElement(int index)
{
    return changed->getElement(index);
}

template<typename T>
ArrayWorkers<T>* DataOf<T>::getArrayOriginal()
{
    return original;
}

template<typename T>
void DataOf<T>::addToOriginal(T a)
{
    this->original->add(a);
}

template<typename T>
WorkerTable<T>* DataOf<T>::getTable()
{
    return table;
}

template<typename T>
void DataOf<T>::addElement(T a)
{
    original->add(a);
    changed->add(a);
}

template<typename T>
int DataOf<T>::sizeOfArray()
{
    return changed->numberOfElement();
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
    int i = 0;
    int last = 0;
    while (i < type.size())
    {
        if(isdigit(type[i]))
        {
            last = i;      
        }
        i++;
    }
    type = type.substr(last+1, type.length());
    sstream << type <<" " << current + 1 << "/" << changed->numberOfElement();
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
    if (current >= changed->numberOfElement() - 1)
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
    if (data->current + 1 < data->changed->numberOfElement())
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
void DataOf<T>::elementPushed(int indeks, T element) {
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
    if(changed->numberOfElement() == 0)
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
        cout << "ovde" << endl;
        e->table->elementRemoved(i);
        cout << "ovde1" << endl;
        int counter = 0;
        for(int j = 0; j < e->original->numberOfElement(); j++)
        {
            if(!e->original->getElement(j)->isDeleted())
            {
                if(counter == i)
                {
                    cout << "dosao do setDelete" << endl;
                    cout << counter << " - " << i << endl;
                    cout << e->original->getElement(j)->isDeleted() << endl;
                    e->original->getElement(j)->setDeleted();
                    cout << e->original->getElement(j)->isDeleted() << endl;
                }
                counter++;
            }
        }
    }
    cout << "changed/original: " << e->changed->numberOfElement() << "/" << e->original->numberOfElement() << endl;
    if(e->changed->numberOfElement() != 0)
    {
        e->setDisplay(e->changed->numberOfElement()-1);
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

// template<typename T>
// void DataOf<T>::save(Fl_Widget *widget, void *d)
// {
//     int answer = fl_choice("Do you want to save changes and close window?", "Yes", "No", "Go back");
//     if (answer == 0)
//     {
//         ArrayWorkers<T> data = *(ArrayWorkers<T>*)d;
//         for(int j = 0; j < data->original->numberOfElement(); j++)
//         {
//             cout << j+1 << ". " << data->original->getElement(j)->isDeleted() << endl;
//         }
//         ofstream datoteka("podaciTest.txt");
//         data->original->write(datoteka);
//         datoteka.close();
//     }
//     if (answer < 2)
//     {
//         widget->hide();
//     }
// }
#endif