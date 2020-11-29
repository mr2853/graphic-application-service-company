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
double AbstractWorker::getSalary() const
{
    return salary;
}
string AbstractWorker::getType() const
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

string AbstractWorker::getData(int column) const
{
    if (column == 0)
    {
        return this->getName();
    }
    else if (column == 1)
    {
        return this->getLastname();
    }
    else if (column == 2)
    {
        return this->getDateBirth()->getDateWithTime();
    }
    else if (column == 3)
    {
        return to_string(this->getSalary());
    }
    return "";
}