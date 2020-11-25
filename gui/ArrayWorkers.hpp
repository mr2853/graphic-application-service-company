#ifndef ARRAY_WORKERS_HPP
#define ARRAY_WORKERS_HPP
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "AbstractTableModel.hpp"
#include "../Class/AbstractWorker.hpp"

template<typename T>
class ArrayWorkers : public AbstractTableModel<T>{
private:
    vector<T> *array;
    string type = "da";
public:
    virtual int numberOfRows();
    virtual int numberOfColumns();
    virtual void pushElement(int row, T  element);
    virtual T  getRow(int row);
    string getText(int row, int column);
    virtual string horizontalHeader(int column);
    virtual string verticalHeader(int row);
    virtual void pushRow(int row, T  element);
    virtual void removeRow(int row);
    void write(ostream &output);
    void read(istream &input);
    ArrayWorkers();
    ArrayWorkers(vector<T> *array);
    // ArrayWorkers(vector<vector<T>*> *array);
    virtual ~ArrayWorkers();
    void add(T p);
    void setDeleted(int index);
    bool isDeleted(int index);
    T  getElement(int in);
    vector<T>* arrayOfNotDeleted();
    // static void save(Fl_Widget *widget, void *data);
};

template<typename T>
string ArrayWorkers<T>::getText(int row, int column)
{
    T o = this->getRow(row);
    return o->getData(column);
}

template<typename T>
ArrayWorkers<T>::ArrayWorkers() : AbstractTableModel<T>()
{
    array = new vector<T>();
}

template<typename T>
ArrayWorkers<T>::ArrayWorkers(vector<T> *array) : AbstractTableModel<T>(), array(array)
{
}

// template<typename T>
// ArrayWorkers<T>::ArrayWorkers(vector<vector<T>*> *array) : AbstractTableModel<T>()
// {
//     this->array = new vector<T>();
//     cout << "usao vector<<Audit*>*>*" << endl;
//     cout << array->size() << endl;
//     cout << this->array->size() << endl;
//     for(int i = 0; i < array->size(); i++)
//     {
//         cout << "i " << i << endl;
//         for(int j = 0; j < array->at(i)->size(); j++)
//         {
//             cout << "j" << j << endl;
//             this->array->push_back(array->at(i)->at(j));
//         }
//     }
//     cout << "prosao vector<<Audit*>*>*" << endl;
// }

template<typename T>
void ArrayWorkers<T>::setDeleted(int index)
{
    array->at(index)->setDeleted();
}
template<typename T>
bool ArrayWorkers<T>::isDeleted(int index)
{
    return array->at(index)->isDeleted();
}



template<typename T>
int ArrayWorkers<T>::numberOfRows()
{
    return array->size();
}

template<typename T>
int ArrayWorkers<T>::numberOfColumns()
{
    string type = typeid(T).name();
    type = type.substr(1,type.length());
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
T ArrayWorkers<T>::getRow(int indeks)
{
    return array->at(indeks);
}

template<typename T>
void ArrayWorkers<T>::pushRow(int row, T  elem){
    array->insert(array->begin() + row, elem);
    AbstractTableModel<T>::pushRow(row, elem);
};

template<typename T>
void ArrayWorkers<T>::removeRow(int index)
{
    array->erase(array->begin() + index);
    AbstractTableModel<T>::removeRow(index);
}

template<typename T>
void ArrayWorkers<T>::write(ostream &output)
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
void ArrayWorkers<T>::read(istream &input)
{
    int brojOsoba;
    input >> brojOsoba;
    string tip;
    for (int i = 0; i < brojOsoba; i++)
    {
        T novaOsoba;
        input >> tip;
        string type = typeid(T).name();
        type = type.substr(1,type.length());
        if (tip == type)
        {
            novaOsoba = new T();
        }
        pushElement(array->size(), novaOsoba);
    }
}

template<typename T>
string ArrayWorkers<T>::horizontalHeader(int column)
{
    string type = typeid(T).name();
    type = type.substr(1,type.length());
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
string ArrayWorkers<T>::verticalHeader(int row){  
    return to_string(row+1);
};
template<typename T>
void ArrayWorkers<T>::pushElement(int row, T a)
{
    this->pushRow(row, a);
}
template<typename T>
ArrayWorkers<T>::~ArrayWorkers(){}

template<typename T>
void ArrayWorkers<T>::add(T p)
{
    array->push_back(p);
}
template<typename T>
T  ArrayWorkers<T>::getElement(int in)
{
    return array->at(in);
}
// template<typename T>
// void ArrayWorkers<T>::save(Fl_Widget *widget, void *data)
// {
//     int answer = fl_choice("Do you want to save changes and close window?", "Yes", "No", "Go back");
//     if (answer == 0)
//     {
//         ArrayWorkers<T> original = *(ArrayWorkers<T>*)data;
//         for(int j = 0; j < original.numberOfElement(); j++)
//         {
//             cout << j+1 << ". " << original.getElement(j)->isDeleted() << endl;
//         }
//         ofstream datoteka("podaciTest.txt");
//         original.write(datoteka);
//         datoteka.close();
//     }
//     if (answer < 2)
//     {
//         widget->hide();
//     }
// }
#endif