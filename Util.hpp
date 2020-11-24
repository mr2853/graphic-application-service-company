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
#include "gui/auditor/DisplayAuditor.hpp"
#include <exception>


using namespace std;


vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3, int changed);
vector<string> tokenization(string &line, string delimiter1, string delimiter2);
vector<int> getDate(string &line);

bool correctDate(string t, int time = 0);
static bool checkDate(string &t, int min, int max = -1);

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
struct UnselectedDataToRemove : public exception {
   const char * what () const throw () {
        return "No data is selected for removing in table!";
   }
};
struct EmptyInput : public exception {
   const char * what (string name) const throw () {
        name += " input is empty!";
        return name.c_str();
   }
};

#endif