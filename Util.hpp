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
#include <algorithm> 
#include <cctype>
#include <locale>
#include <FL/fl_message.H>


using namespace std;

struct InputContainsForbiddenCharacter : public exception {
   const char * what () const throw () {
        return "Input contains some of forbidden characters!\n , : - # $ [ ] < > ";
   }
};

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s, int dontCheck=1) {
    if(dontCheck == 1)
    {
        for(int i = 0; i < s.size(); i++)
        {
            if(s.find(",") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find(":") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("-") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("$") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("#") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("<") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find(">") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("[") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
            else if(s.find("]") != string::npos)
            {
                throw InputContainsForbiddenCharacter();
            }
        }
    }
    ltrim(s);
    rtrim(s);
}

vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3, int changed);
vector<string> tokenization(string &line, string delimiter1, string delimiter2);
vector<int> getDate(string &line);

bool correctDate(string t, int time = 0);
static bool checkDate(string &t, int min, int max = -1);

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