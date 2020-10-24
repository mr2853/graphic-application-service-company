#include <iostream>
#include "Util.hpp"
#include "AbstractPerson.hpp"
#include "Accountant.hpp"
#include "AbstractWorker.hpp"
#include "Audit.hpp"
#include "Auditor.hpp"
#include "Commercialist.hpp"
#include "Department.hpp"
#include "Date.hpp"
#include "Company.hpp"

using namespace std;

ostream& operator<<(ostream& output, const Company& o)
{
    output << o.toString();
    return output; 
};


int main()
{
    Company company;
    company.readData1("podaci.txt");
    cout << company;
    return 0;
}