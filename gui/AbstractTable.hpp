#ifndef ABSTRACT_TABLE_HPP
#define ABSTRACT_TABLE_HPP
#include <iostream>
#include <string>

using namespace std;


template<typename T>
class AbstractTable{
public:
    virtual int numberOfElement();
    virtual T getElement(int red);
    virtual void add(T *r);
    virtual void removeElement(int red);
    virtual int numberOfRows() = 0;
    virtual int numberOfColomns() = 0;
    virtual T getRow(int red) = 0;
    virtual string getText(int red, int kolona) = 0;
    virtual string horizontalHeader(int kolona) = 0;
    virtual string verticalHeader(int red) = 0;
    virtual void pushRow(int red, T element) = 0;
    virtual void removeRow(int red) = 0;
    virtual ~AbstractTable() = 0;
};
#endif