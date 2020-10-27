#ifndef ABSTRACT_MODEL_HPP
#define ABSTRACT_MODEL_HPP

#include <vector>
#include <algorithm>

#include "AbstractDisplay.hpp"

using namespace std;

template <typename T>
class AbstractModel
{
private:
    vector<AbstractDisplay<T> *> listeners = vector<AbstractDisplay<T> *>();

public:
    virtual int numberOfElement() = 0;
    virtual T getElement(int indeks) = 0;
    virtual void pushElement(int indeks, T element) = 0;
    virtual void removeElement(int indeks) = 0;
    void subscribeListener(AbstractDisplay<T> *listener);
    void checkOutListener(AbstractDisplay<T> *listener);
    virtual ~AbstractModel();
};

template <typename T>
void AbstractModel<T>::pushElement(int index, T element)
{
    for (AbstractDisplay<T> *ap : listeners)
    {
        ap->elementPushed(index, element);
    }
}

template <typename T>
void AbstractModel<T>::removeElement(int indeks)
{
    for (AbstractDisplay<T> *ap : listeners)
    {
        ap->elementRemoved(indeks);
    }
}

template <typename T>
void AbstractModel<T>::subscribeListener(AbstractDisplay<T> *listener)
{
    listeners.push_back(listener);
}
template <typename T>
void AbstractModel<T>::checkOutListener(AbstractDisplay<T> *listener)
{
    vector<AbstractDisplay<T> *> iterator = find(listeners->begin, listeners->end());
    if (iterator != listeners->end())
    {
        listeners.erase(iterator);
    }
}
template <typename T>
AbstractModel<T>::~AbstractModel()
{
}

#endif