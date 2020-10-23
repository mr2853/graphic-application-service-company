#include "Department.hpp"

Department::Department(){}
Department::~Department(){}
Department::Department(vector<AbstractWorker*> worker, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits)
    : worker(worker), headOfDepartment(headOfDepartment), name(name), audits(audits){}