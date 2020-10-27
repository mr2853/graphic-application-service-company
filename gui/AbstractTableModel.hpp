#ifndef ABSTRACT_TABLE_MODEL_HPP
#define ABSTRACT_TABLE_MODEL_HPP

#include <string>

#include "AbstractModel.hpp"

using namespace std;

template <typename T>
class AbstractTableModel : public AbstractModel<T>
{
public:
    virtual int numberOfElement();
    virtual T getElement(int red);
    virtual void pushElement(int red, T element);
    virtual void removeElement(int red);
    virtual int numberOfRows() = 0;
    virtual int numberOfColumns() = 0;
    virtual T getRow(int red) = 0;
    virtual string getText(int red, int kolona) = 0;
    virtual string horizontalHeader(int kolona) = 0;
    virtual string verticalHeader(int red) = 0;
    virtual void pushRow(int red, T element) = 0;
    virtual void removeRow(int red) = 0;
    virtual ~AbstractTableModel();
};

template <typename T>
int AbstractTableModel<T>::numberOfElement()
{
    return numberOfRows();
}

template <typename T>
T AbstractTableModel<T>::getElement(int red)
{
    return getRow(red);
}

template <typename T>
void AbstractTableModel<T>::pushElement(int red, T element)
{
    pushRow(red, element);
}

template <typename T>
void AbstractTableModel<T>::removeElement(int red)
{
    removeRow(red);
}

template <typename T>
void AbstractTableModel<T>::pushRow(int red, T element)
{
    AbstractModel<T>::pushElement(red, element);
}

template <typename T>
void AbstractTableModel<T>::removeRow(int red)
{
    AbstractModel<T>::removeElement(red);
}

template <typename T>
AbstractTableModel<T>::~AbstractTableModel()
{
}

#endif