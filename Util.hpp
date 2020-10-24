#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Department.hpp"
#include "Date.hpp"
#include "Commercialist.hpp"
#include "Auditor.hpp"
#include "Audit.hpp"
#include "Accountant.hpp"
#include "AbstractWorker.hpp"

using namespace std;


vector<string> tokenization(string &line, string delimiter1, string delimiter2);

template<class T>
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
};

template<class T>
vector<T*> readArray(string in)
{
    vector<T*> array = vector<T*>();
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
        T *d = new T(s);
        array.push_back(d);
    }
    return array;
};
//template<class T>

#endif