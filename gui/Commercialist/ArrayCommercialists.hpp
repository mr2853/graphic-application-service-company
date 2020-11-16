#ifndef ARRAY_COMMERCIALISTS_HPP
#define ARRAY_COMMERCIALISTS_HPP

#include <iostream>
#include <vector>

#include "../../Class/Commercialist.hpp"
#include "../ArrayWorkers.hpp"

class ArrayCommercialists : public ArrayWorkers<Commercialist>{
public:
    ArrayCommercialists();
    ArrayCommercialists(vector<Commercialist*> *array);
    virtual ~ArrayCommercialists();
};


#endif