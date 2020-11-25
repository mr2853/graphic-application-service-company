#include "../Util.hpp"
#include "Department.hpp"
#include "Auditor.hpp"
#include "Audit.hpp"
#include "AbstractWorker.hpp"

Department::Department(){}
Department::~Department()
{
    
};
double Department::getMaxSalary()
{
    double max = -1;
    for(int j = 0; j < this->getAccountants()->size(); j++)
    {
        if(max < this->getAccountants()->at(j)->getSalary() || max == -1)
        {
            max = this->getAccountants()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCommercialists()->size(); j++)
    {
        if(max < this->getCommercialists()->at(j)->getSalary() || max == -1)
        {
            max = this->getCommercialists()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getAuditors()->size(); j++)
    {
        if(max < this->getAuditors()->at(j)->getSalary() || max == -1)
        {
            max = this->getAuditors()->at(j)->getSalary();
        }
    }
    if(max < this->headOfDepartment->getSalary() || max == -1)
    {
        max = this->headOfDepartment->getSalary();
    }
    return max;
}
double Department::getMinSalary()
{
    double min = -1;
    for(int j = 0; j < this->getAccountants()->size(); j++)
    {
        if(min > this->getAccountants()->at(j)->getSalary() || min == -1)
        {
            min = this->getAccountants()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getCommercialists()->size(); j++)
    {
        if(min > this->getCommercialists()->at(j)->getSalary() || min == -1)
        {
            min = this->getCommercialists()->at(j)->getSalary();
        }
    }

    for(int j = 0; j < this->getAuditors()->size(); j++)
    {
        if(min > this->getAuditors()->at(j)->getSalary() || min == -1)
        {
            min = this->getAuditors()->at(j)->getSalary();
        }
    }
    if(min > this->headOfDepartment->getSalary() || min == -1)
    {
        min = this->headOfDepartment->getSalary();
    }
    return min;
}
Department::Department(string &in, int changed)
{
    string twoDots = ":";
    string comma = ",";

    int index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find(comma);
    string deleted = in.substr(0, index);

    index = in.find(twoDots);
    in.erase(0,index+1);
    index = in.find(comma);
    name = in.substr(0, index);

    index = in.find(twoDots);
    in.erase(0,index+1);
    
    index = in.find("],arrayOfWorker:<");
    string text = in.substr(0, index);
    in.erase(0,index+17);
    index = text.find("[");
    string type = text.substr(0, index);
    if(type == "Accountant")
    {
        headOfDepartment = new Accountant(text, changed);
    }
    else if(type == "Auditor")
    {
        headOfDepartment = new Auditor(text, changed);
    }
    else if(type == "Commercialist")
    {
        headOfDepartment = new Commercialist(text, changed);
    }
    else
    {
        return;
    }
    
    

    index = in.find("audits:<");
    string workers = in.substr(0, index);
    cout << "\n\nworkers size: " << workers.size() << endl;
    cout << workers << endl;
    in.erase(0,index+8);
    
    vector<string> textArray;
    string type1;
    cout << "dep1" << endl;
    while(true)
    {
        if(workers.find("]#") != std::string::npos){
            index = workers.find("]#");
            textArray.push_back(workers.substr(0, index));
            workers.erase(0, index + 2);
        }
        else if(workers.find("]>") != std::string::npos){
            index = workers.find("]>");
            if(index == string::npos)
            {
                index = workers.find("]");
            }
            textArray.push_back(workers.substr(0, index));
            break;
        }
        else
        {
            break;
        }
    }
    
    for(string &s : textArray)
    {
        index = s.find("[");
        type1 = s.substr(0, index);
        cout << "dep2" << endl;
        if(changed == 1)
        {
            string someText = s;
            index = someText.find(":");
            someText.erase(0,index+1);
            index = someText.find(",");
            string deleted = someText.substr(0, index);
            if(deleted == "true")
            {
                continue;
            }
        }
        cout << "dep3" << endl;
        if(type1 == "Commercialist"){
            cout << "dep3.1" << endl;
            commercialists->push_back(new Commercialist(s, changed));
            cout << "dep3.2" << endl;
        }
        else if(type1 == "Auditor"){
            cout << "dep3.3" << endl;
            auditors->push_back(new Auditor(s, changed));
            cout << "dep3.4" << endl;
        }
        else if(type1 == "Accountant"){
            cout << "dep3.5" << endl;
            accountants->push_back(new Accountant(s, changed));
            cout << "dep3.6" << endl;
        }
        cout << "dep4" << endl;
    }
    
    audits = Audit::readArray(in, changed);
    
    if(deleted == "true")
    {
        cout << "ov1" << endl;
        this->setDeleted();
        cout << "ov2" << endl;
    }
}
string Department::getData(int column)
{
    if (column == 0)
    {
        return this->getName();
    }
    else if (column == 1)
    {
        return this->getHeadOfDepartment()->getName();
    }
    else if (column == 2)
    {
        return this->getHeadOfDepartment()->getLastname();
    }
    else if (column == 3)
    {
        return this->getHeadOfDepartment()->getType();
    }
    return "";
}
Department::Department(vector<Commercialist*>* commercialists, vector<Auditor*>* auditors,
    vector<Accountant*>* accountants, AbstractWorker *headOfDepartment, string name, vector<Audit*>* audits)
    : commercialists(commercialists), auditors(auditors), accountants(accountants),
     headOfDepartment(headOfDepartment), name(name), audits(audits){}


Department::Department(AbstractWorker *headOfDepartment, string name) : headOfDepartment(headOfDepartment), name(name){}
    
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

vector<Audit*>* Department::getAudits() {
    return audits;
}

void Department::setAudits(vector<Audit*>* audits) {
    this->audits = audits;
}
vector<Commercialist*>* Department::getCommercialists() {
    return commercialists;
}

void Department::setCommercialists(vector<Commercialist*>* commercialists) {
    this->commercialists = commercialists;
}

vector<Auditor*>* Department::getAuditors() {
    return auditors;
}

void Department::setDeleted() {
    for(int i = 0; i < commercialists->size(); i++)
    {
        commercialists->at(i)->setDeleted();
    }
    for(int i = 0; i < auditors->size(); i++)
    {
        auditors->at(i)->setDeleted();
    }
    for(int i = 0; i < accountants->size(); i++)
    {
        accountants->at(i)->setDeleted();
    }
    for(int i = 0; i < audits->size(); i++)
    {
        audits->at(i)->setDeleted();
    }
    headOfDepartment->setDeleted();
	deleted = true;
}
void Department::setAuditors(vector<Auditor*>* auditors) {
    this->auditors = auditors;
}

bool Department::isDeleted() {
	return deleted;
}
vector<Accountant*>* Department::getAccountants() {
    return accountants;
}

void Department::setAccountants(vector<Accountant*>* accountants) {
    this->accountants = accountants;
}

vector<Department*>* Department::readArray(string in, int changed)
{
    vector<Department*>* array = new vector<Department*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("]$Department") != std::string::npos){
            index = in.find("]$Department");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else if(in.find("Department[") != std::string::npos){
            index = in.find_last_of(">");
            text.push_back(in.substr(0, index));
            cout << "erase department" << endl;
            in.erase(0, index + 2);
            cout << "erase department 1" << endl;
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        index = s.find("[");
        type1 = s.substr(0, index);
        if(changed == 1)
        {
            string someText = s;
            index = someText.find(":");
            someText.erase(0,index+1);
            index = someText.find(",");
            string type = someText.substr(0, index);
            if(type == "true")
            {
                cout << "ovde" << endl;
                continue;
            }
        }
        // cout << "ovde1" << endl;
        Department *d = new Department(s, changed);
        array->push_back(d);
    }
    return array;
};
void Department::write(ostream &output, Department *d)
{
    output << "Department[deleted:";
    if(d->deleted)
    {
        output << "true";
    }
    else
    {
        output << "false";
    }
    output << ",name:" << d->name << ",headOfDepartment:";
    d->headOfDepartment->write(output, d->headOfDepartment);
    output << ",arrayOfWorker:<";

    for(int i = 0; i < d->accountants->size(); i++)
    {
        d->accountants->at(i)->write(output, d->accountants->at(i));
        if(i < d->accountants->size()-1 || d->auditors->size() != 0 || d->commercialists->size() != 0)
        {
            output << "#";
        }
    }
    for(int i = 0; i < d->auditors->size(); i++)
    {
        d->auditors->at(i)->write(output, d->auditors->at(i));
        if(i < d->auditors->size()-1 || d->commercialists->size() != 0)
        {
            output << "#";
        }
    }
    for(int i = 0; i < d->commercialists->size(); i++)
    {
        d->commercialists->at(i)->write(output, d->commercialists->at(i));
        if(i < d->commercialists->size()-1)
        {
            output << "#";
        }
    }
    output << ">,audits:<";
    for(int i = 0; i < d->audits->size(); i++)
    {
        d->audits->at(i)->write(output, d->audits->at(i));
        if(i < d->audits->size()-1)
        {
            output << "$";
        }
    }

    output << ">]";
}