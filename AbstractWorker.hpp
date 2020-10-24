#ifndef ABSTRACT_WORKER_HPP
#define ABSTRACT_WORKER_HPP
#include <iostream>
#include <vector>
#include <string>

#include "AbstractPerson.hpp"

class AbstractWorker : public AbstractPerson{
private:
    double salary;
public:
    AbstractWorker();
    AbstractWorker(string name, string lastname, Date *dateBirth, double salary);
    virtual ~AbstractWorker() = 0;

    virtual void setSalary(double salary);
    virtual double getSalary();
    //static vector<AbstractWorker*> readData(string in);
    //virtual vector<AbstractWorker*> readDataVirtual(string in);
    
};


#endif