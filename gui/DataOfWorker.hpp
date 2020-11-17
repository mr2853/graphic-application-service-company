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
#include "../Class/Company.hpp"
#include "../Class/Department.hpp"
#include "Department/DataOfDepartments.hpp"
#include "DataOf.hpp"

template<typename T>
class DataOfWorker : public DataOf<T>{
protected:
    static void goBack(Fl_Widget *widget, void *data);
public:
    DataOfWorker(int x, int y, int w, int h, ArrayWorkers<T> *array, void *mainWindow, const char *l=0);
    virtual ~DataOfWorker();
};

template<typename T>
DataOfWorker<T>::DataOfWorker(int x, int y, int w, int h, ArrayWorkers<T> *array, void *d, const char *l) 
: DataOf<T>(x, y, w, h, array, d, l)
{
    vector<void*> *v = new vector<void*>();
    v->push_back(d);
    v->push_back(this);
    this->btnGoBack->callback(DataOfWorker<T>::goBack, v);
}

template<typename T>
DataOfWorker<T>::~DataOfWorker<T>(){}

template<typename T>
void DataOfWorker<T>::goBack(Fl_Widget *widget, void *d)
{
    vector<Fl_Widget*> *v = (vector<Fl_Widget*>*)d;
    DataOfDepartments *parent = (DataOfDepartments*)v->at(0);
    DataOfWorker<T> *data = (DataOfWorker<T>*)v->at(1);
    
    data->hideGroup();
    data->hide();
    parent->remove(data);
    parent->unhideGroup();
}

#endif