#include "AbstractWorker.hpp"
AbstractWorker::AbstractWorker(){};
AbstractWorker::~AbstractWorker(){};
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

/*vector<AbstractWorker*> AbstractWorker::readData(string in)
{
    return readDataVirtual(in);
}
vector<AbstractWorker*> AbstractWorker::readDataVirtual(string in)
{

}*/