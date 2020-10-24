#include "Util.hpp"
#include "Department.hpp"
#include "Auditor.hpp"
#include "Audit.hpp"
#include "AbstractWorker.hpp"

Department::Department(){}
Department::~Department(){}
Department::Department(string &in)
{
    string twoDots = ":";
    string comma = ",";
    int index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find(comma);
    string name = in.substr(0, index);

    index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find("arrayOfWorker:<");
    string text = in.substr(0, index);
    AbstractWorker* headOfDepartment = new Auditor(text);
    in.erase(0,index+15);
    index = in.find("audits:<[");
    vector<AbstractWorker*> workers = vector<AbstractWorker*>();
    workers = readAbstractArray<AbstractWorker>(in.substr(0, index));
    in.erase(0,index+9);
    vector<Audit*> audits = vector<Audit*>();
    audits = readArray<Audit>(in);
    this->setName(name);
    this->setHeadOfDepartment(headOfDepartment);
    this->setWorker(workers);
    this->setAudits(audits);
}
Department::Department(vector<AbstractWorker*> worker, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits)
    : worker(worker), headOfDepartment(headOfDepartment), name(name), audits(audits){}

vector<AbstractWorker*> Department::getWorker() {
    return worker;
}

void Department::setWorker(vector<AbstractWorker*> worker) {
    this->worker = worker;
}

AbstractWorker* Department::getHeadOfDepartment() {
    return headOfDepartment;
}

void Department::setHeadOfDepartment(AbstractWorker *headOfDepartment) {
    this->headOfDepartment = headOfDepartment;
}

string Department::getName() {
    return name;
}

void Department::setName(string name) {
    this->name = name;
}

vector<Audit*> Department::getAudits() {
    return audits;
}

void Department::setAudits(vector<Audit*> audits) {
    this->audits = audits;
}


/*vector<Department*> Department::readData1(string in)
{
    vector<Department*> departments;
    string twoDots = ":";
    string comma = ",";

    while(in.find("Department[deleted:"))
    {
        int index = in.find(twoDots);
        in.erase(0,index);
        index = in.find(comma);
        string deleted = in.substr(0, index);
        if(deleted == "true")
            continue;
        
        Department *d = new Department();
        
    }

    return departments;
}*/