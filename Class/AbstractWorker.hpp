#ifndef ABSTRACT_WORKER_HPP
#define ABSTRACT_WORKER_HPP
#include <iostream>
#include <vector>
#include <string>

#include "AbstractPerson.hpp"

class AbstractWorker : public AbstractPerson{
private:
    double salary;
    const string type = "AbstractWorker";
public:
    AbstractWorker();
    AbstractWorker(string name, string lastname, Date *dateBirth, double salary);
    virtual ~AbstractWorker() = 0;

    virtual string getType() const;
    virtual void setSalary(double salary);
    virtual double getSalary() const;
    virtual void setDeleted();
    virtual void write(ostream &output, void *d);
    string getData(int column) const;
};


#endif