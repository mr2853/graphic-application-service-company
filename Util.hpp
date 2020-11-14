#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Class/Department.hpp"
#include "Class/Date.hpp"
#include "Class/Commercialist.hpp"
#include "Class/Auditor.hpp"
#include "Class/Audit.hpp"
#include "Class/Accountant.hpp"
#include "Class/AbstractWorker.hpp"
#include "gui/auditor/ArrayAuditors.hpp"
#include "gui/auditor/AuditorTable.hpp"
#include "gui/auditor/DisplayAuditor.hpp"

using namespace std;


vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3);
vector<int> getDate(string &line);

/*template<class T>
vector<T*> readAbstractArray(string in)
{
    vector<T*> array = vector<T*>();
    int index;
    vector<string> text;
    string type1;
    while(true)
    {
        if(in.find("#") != std::string::npos){
            index = in.find("]#");
            text.push_back(in.substr(0, index));
            in.erase(0, index + 2);
        }
        else{
            break;
        }
    }
    for(string &s : text)
    {
        index = s.find("[");
        type1 = s.substr(0, index);
        if(type1 == "Commercialist"){
            array.push_back(new Commercialist(s));
        }
        else if(type1 == "Auditor"){
            array.push_back(new Auditor(s));
        }
        else if(type1 == "Accountant"){
            array.push_back(new Accountant(s));
        }
    }
    return array;
};*/


//template<class T>

#endif