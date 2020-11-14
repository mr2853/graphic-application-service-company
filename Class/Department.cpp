#include "../Util.hpp"
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
    string type = in.substr(0, index);
    if(type == "true")
        return;

    index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find(comma);
    string name = in.substr(0, index);

    index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find("],arrayOfWorker:<");
    string text = in.substr(0, index);

    AbstractWorker* headOfDepartment = new Accountant(text);
    in.erase(0,index+17);
    index = in.find("audits:<[");
    string workers = in.substr(0, index);
    in.erase(0,index+9);
    
    vector<string> textArray;
    string type1;
    while(true)
    {
        if(workers.find("]#") != std::string::npos){
            index = workers.find("]#");
            textArray.push_back(workers.substr(0, index));
            workers.erase(0, index + 2);
        }
        else{
            index = workers.find("]>");
            textArray.push_back(workers.substr(0, index));
            break;
        }
    }
    
    for(string &s : textArray)
    {
        index = s.find("[");
        type1 = s.substr(0, index);
        if(type1 == "Commercialist"){
            commercialists.push_back(new Commercialist(s));
        }
        else if(type1 == "Auditor"){
            auditors.push_back(new Auditor(s));
        }
        else if(type1 == "Accountant"){
            accountants.push_back(new Accountant(s));
        }
    }
    
    vector<Audit*> audits = vector<Audit*>();
    audits = Audit::readArray(in);
    
    this->setName(name);
    this->setHeadOfDepartment(headOfDepartment);
    this->setAudits(audits);
}

Department::Department(vector<Commercialist*> commercialists, vector<Auditor*> auditors,
    vector<Accountant*> accountants, AbstractWorker *headOfDepartment, string name, vector<Audit*> audits)
    : commercialists(commercialists), auditors(auditors), accountants(accountants),
     headOfDepartment(headOfDepartment), name(name), audits(audits){}


Department::Department(AbstractWorker *headOfDepartment, string name) : headOfDepartment(headOfDepartment), name(name),
    commercialists(vector<Commercialist*>()), auditors(vector<Auditor*>()), accountants(vector<Accountant*>()), 
    audits(vector<Audit*>()){}
    
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
vector<Commercialist*>* Department::getCommercialists() {
    return &commercialists;
}

void Department::setCommercialists(vector<Commercialist*> commercialists) {
    this->commercialists = commercialists;
}

vector<Auditor*>* Department::getAuditors() {
    return &auditors;
}

void Department::setAuditors(vector<Auditor*> auditors) {
    this->auditors = auditors;
}

vector<Accountant*>* Department::getAccountants() {
    return &accountants;
}

void Department::setAccountants(vector<Accountant*> accountants) {
    this->accountants = accountants;
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
vector<Department*>* Department::readArray(string in)
{
    vector<Department*>* array = new vector<Department*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("]#Department") != std::string::npos){
            index = in.find("]#Department");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else if(in.find("Department[") != std::string::npos){
            index = in.find_last_of(">");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        //cout << "\n\n" << s << "\n\n" << endl;
        index = s.find("[");
        type1 = s.substr(0, index);
        Department *d = new Department(s);
        array->push_back(d);
    }
    return array;
};