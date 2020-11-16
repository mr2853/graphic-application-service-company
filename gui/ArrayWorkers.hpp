#ifndef ARRAY_WORKERS
#define ARRAY_WORKERS
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "AbstractTableModel.hpp"

template<typename T>
class ArrayWorkers : public AbstractTableModel<T *>{
private:
    vector<T*> *array;
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int red, T* element);
    virtual T* getRow(int red);
    virtual string getText(int red, int kolona);
    virtual string horizontalHeader(int kolona);
    virtual string verticalHeader(int red);
    virtual void pushRow(int red, T* element);
    virtual void removeRow(int red);
    void write(ostream &output);
    void read(istream &input);
    ArrayWorkers();
    ArrayWorkers(vector<T*> *array);
    virtual ~ArrayWorkers();
    void add(T *p);
    T* getElement(int in);
};
template<typename T>
ArrayWorkers<T>::ArrayWorkers() : AbstractTableModel<T*>()
{
    array = new vector<T*>();
}

template<typename T>
ArrayWorkers<T>::ArrayWorkers(vector<T*> *array) : AbstractTableModel<T*>(), array(array)
{
}

template<typename T>
int ArrayWorkers<T>::numberOfRows()
{
    return array->size();
}

template<typename T>
int ArrayWorkers<T>::numberOfColumns()
{
    return 4;
}

template<typename T>
T *ArrayWorkers<T>::getRow(int indeks)
{
    return array->at(indeks);
}

template<typename T>
void ArrayWorkers<T>::pushRow(int row, T* elem){
    array->insert(array->begin() + row, elem);
    AbstractTableModel<T *>::pushRow(row, elem);
};

template<typename T>
void ArrayWorkers<T>::removeRow(int index)
{
    array->erase(array->begin() + index);
    AbstractTableModel<T*>::removeRow(index);
}

template<typename T>
void ArrayWorkers<T>::write(ostream &output)
{
    output << array->size() << endl;
    for (int i = 0; i < array->size(); i++)
    {
        output << array->at(i) << endl;
    }
}

template<typename T>
void ArrayWorkers<T>::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        T *novaOsoba;
        input >> tip;
        if (tip == typeid(T).name())
        {
            novaOsoba = new T();
        }
        pushElement(array->size(), novaOsoba);
    }
}

template<typename T>
string ArrayWorkers<T>::getText(int row, int column)
{
    T *o = array->at(row);
    if (column == 0)
    {
        return o->getName();
    }
    else if (column == 1)
    {
        return o->getLastname();
    }
    else if (column == 2)
    {
        return o->getDateBirth()->getDateWithTime();
    }
    else if (column == 3)
    {
        return to_string(o->getSalary());
    }
    return "";
}

template<typename T>
string ArrayWorkers<T>::horizontalHeader(int column)
{
    if (column == 0)
    {
        return "Name";
    }
    else if (column == 1)
    {
        return "Lastname";
    }
    else if (column == 2)
    {
        return "Date birth";
    }
    else if (column == 3)
    {
        return "Salary";
    }
    return "";
}
template<typename T>
string ArrayWorkers<T>::verticalHeader(int row){  
    return to_string(row+1);
};
template<typename T>
void ArrayWorkers<T>::pushElement(int row, T *a)
{
    this->pushRow(row, a);
}
template<typename T>
ArrayWorkers<T>::~ArrayWorkers(){}

template<typename T>
void ArrayWorkers<T>::add(T *p)
{
    array->push_back(p);
}
template<typename T>
T* ArrayWorkers<T>::getElement(int in)
{
    return array->at(in);
}
#endif