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
#include <exception>


using namespace std;


vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3);
vector<string> tokenization(string &line, string delimiter1, string delimiter2);
vector<int> getDate(string &line);
// std::string trim(const std::string &s);
bool correctDate(string t, int time=0);

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;
}

struct WrongDate : public exception {
   const char * what (string name) const throw () {
        name += " is not correct.\nInsert in format day-month-year or hour-minute-day-month-year!";
        return name.c_str();
   }
};
struct WrongDateWithTime : public exception {
   const char * what (string name) const throw () {
        name += " is not correct.\nInsert in format hour-minute-day-month-year!";
        return name.c_str();
   }
};
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