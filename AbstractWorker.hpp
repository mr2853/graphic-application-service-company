#ifndef ABSTRACT_WORKER_HPP
#define ABSTRACT_WORKER_HPP
#include <iostream>

#include "AbstractPerson.hpp"

class AbstractWorker : public AbstractPerson{
private:
    double salary;
public:
    AbstractWorker();
    AbstractWorker(string name, string lastname, Date *dateBirth, double salary);

    virtual void setSalary(double salary) = 0;
    virtual double getSalary() = 0;
    
};


#endif