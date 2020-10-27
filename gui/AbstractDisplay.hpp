#ifndef ABSTRACT_DISPLAY_HPP
#define ABSTRACT_DISPLAY_HPP

template <typename T>
class AbstractDisplay
{
public:
    virtual void elementPushed(int index, T element) = 0;
    virtual void elementRemoved(int index) = 0;
    virtual ~AbstractDisplay(){};
};

#endif