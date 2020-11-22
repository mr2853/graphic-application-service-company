#include "AbstractWorker.hpp"
AbstractWorker::AbstractWorker(){};
AbstractWorker::~AbstractWorker()
{
};
AbstractWorker::AbstractWorker(string name, string lastname, Date *dateBirth, double salary) : AbstractPerson(name, lastname, dateBirth), salary(salary){};

void AbstractWorker::setSalary(double salary) 
{
    this->salary = salary;
}
double AbstractWorker::getSalary()
{
    return salary;
}
string AbstractWorker::getType()
{
	return type;
}
void AbstractWorker::write(ostream &output, void *data)
{
    AbstractWorker *d = (AbstractWorker*)data;
    AbstractPerson::write(output, d);
    output << ",salary:" << d->salary;
}

void AbstractWorker::setDeleted() {
	AbstractPerson::setDeleted();
}