#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "AbstractTableModel.hpp"
#include "../Class/AbstractWorker.hpp"

template<typename T>
class Array : public AbstractTableModel<T>{
private:
    vector<T> *array;
    string type = "da";
public:
    virtual int numberOfRows() const;
    virtual int numberOfColumns() const;
    virtual void pushElement(int row, T  element);
    virtual T  getRow(int row) const;
    string getText(int row, int column) const;
    virtual string horizontalHeader(int column) const;
    virtual string verticalHeader(int row) const;
    virtual void pushRow(int row, T  element);
    virtual void removeRow(int row);
    void write(ostream &output);
    void read(istream &input) const;
    Array();
    Array(vector<T> *array);
    virtual ~Array();
    void add(T p);
    void setDeleted(int index);
    bool isDeleted(int index) const;
    T  getElement(int in) const;
    vector<T>* arrayOfNotDeleted() const;
};
template<typename T>
string Array<T>::getText(int row, int column) const
{
    T o = this->getRow(row);
    return o->getData(column);
}

template<typename T>
Array<T>::Array() : AbstractTableModel<T>()
{
    array = new vector<T>();
}

template<typename T>
Array<T>::Array(vector<T> *array) : AbstractTableModel<T>(), array(array){}

template<typename T>
void Array<T>::setDeleted(int index)
{
    array->at(index)->setDeleted();
}
template<typename T>
bool Array<T>::isDeleted(int index) const
{
    return array->at(index)->isDeleted();
}



template<typename T>
int Array<T>::numberOfRows() const
{
    return array->size();
}

template<typename T>
int Array<T>::numberOfColumns() const
{
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
    if(type == "Company")
    {
        return 3;
    }
    else if(type == "Accountant")
    {
        return 6;
    }
    
    return 4;
}

template<typename T>
T Array<T>::getRow(int indeks) const
{
    return array->at(indeks);
}

template<typename T>
void Array<T>::pushRow(int row, T  elem){
    array->insert(array->begin() + row, elem);
    AbstractTableModel<T>::pushRow(row, elem);
};

template<typename T>
void Array<T>::removeRow(int index)
{
    array->erase(array->begin() + index);
    AbstractTableModel<T>::removeRow(index);
}

template<typename T>
void Array<T>::write(ostream &output)
{
    for (int i = 0; i < array->size(); i++)
    {
        array->at(i)->write(output, array->at(i));
        if(i < array->size()-1)
        {
            output << "$";
        }
    }
}

template<typename T>
void Array<T>::read(istream &input) const
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        T novaOsoba;
        input >> tip;
        string type = typeid(T).name();
        int z = 0;
        int last = 0;
        while (z < type.size())
        {
            if(isdigit(type[z]))
            {
                last = z;      
            }
            z++;
        }
        type = type.substr(last+1, type.length());
        if (tip == type)
        {
            novaOsoba = new T();
        }
        pushElement(array->size(), novaOsoba);
    }
}

template<typename T>
string Array<T>::horizontalHeader(int column) const
{
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
    
    if(type == "Commercialist" || type == "Auditor" || type == "Accountant")
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
    }
    else if(type == "Company")
    {
        if (column == 0)
        {
            return "Name";
        }
        else if (column == 1)
        {
            return "Tax ID:";
        }
        else if (column == 2)
        {
            return "ID";
        }
    }
    else if(type == "Department")
    {
        if (column == 0)
        {
            return "Name";
        }
        else if (column == 1)
        {
            return "CEO name:";
        }
        else if (column == 2)
        {
            return "CEO lastname";
        }
        else if (column == 3)
        {
            return "CEO worker type";
        }
    }
    else if(type == "Audit")
    {
        if (column == 0)
        {
            return "Date:";
        }
        else if (column == 1)
        {
            return "Name of Auditor:";
        }
        else if (column == 2)
        {
            return "Lastname of Auditor:";
        }
        else if (column == 3)
        {
            return "Date birth of Auditor:";
        }
    }
    return "";
}
template<typename T>
string Array<T>::verticalHeader(int row) const{  
    return to_string(row+1);
};
template<typename T>
void Array<T>::pushElement(int row, T a)
{
    this->pushRow(row, a);
}
template<typename T>
Array<T>::~Array()
{
    delete array;
}

template<typename T>
void Array<T>::add(T p)
{
    array->push_back(p);
}
template<typename T>
T  Array<T>::getElement(int in) const
{
    return array->at(in);
}

#endif