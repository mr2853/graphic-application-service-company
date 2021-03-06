#include "Util.hpp"
#include "Class/Company.hpp"
#include <FL/fl_message.H>

vector<string> tokenization(string &line, string delimiter1, string delimiter2)
{
    trim(line, 0);
    vector<string> parts = vector<string>();
    int pos;
    while(true)
    {
        pos = line.find(delimiter1);
        if(pos == string::npos){
            break;
        }
        line.erase(0,pos+delimiter1.length());
    
        pos = line.find(delimiter2);
        if(pos == string::npos){
            break;
        }
        string part = line.substr(0, pos);
        line.erase(0,pos+delimiter2.length());
        parts.push_back(part);
    }
    
    if(line.empty())
        return parts;

    parts.push_back(line);
    return parts;
}
vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3, int changed){
    trim(line, 0);
    vector<string> parts = vector<string>();
    int pos;
    pos = line.find(delimiter1);
    if(pos == string::npos){ return parts; }

    line.erase(0,pos+delimiter1.length());
    pos = line.find(delimiter2);
    if(pos == string::npos){ return parts; }

    string part = line.substr(0, pos);
    
    line.erase(0,pos+delimiter2.length());
    if(part == "true")
    {
        if(changed == 1)
        {
            return parts;
        }
        parts.push_back(part);
    }

    while(true){
        if(del3 == "Audit")
        {
            pos = line.find("Auditor[");
            if(pos == string::npos){
                break;
            }
            line.erase(0,pos);

            pos = line.find(",date:");
            if(pos == string::npos){
                break;
            }
            
            string part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,pos+6);

            pos = line.find("]");
            if(pos == string::npos){
                break;
            }
            part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,line.length());
            break;
        }
        if(parts.size() == 2 && del3 == "Commercialist")
        {
            pos = line.find(",salary:");
            if(pos == string::npos){
                break;
            }
            part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,pos+8);
             
            pos = line.find(delimiter2);
            if(pos == string::npos){
                break;
            }
            part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,pos+1);

            part = line.substr(0, line.length());
            parts.push_back(part);
            line.erase(0,line.length());
            break;
        }
        
        if(parts.size() == 2 && del3 != "")
        {
            pos = line.find("],");
            if(pos == string::npos){
                break;
            }
            
            string part = line.substr(0, pos+1);
            parts.push_back(part);
            line.erase(0,pos+2);
            continue;
        }

        pos = line.find(delimiter1);
        if(pos == string::npos){
            break;
        }
        line.erase(0,pos+delimiter1.length());
    
        pos = line.find(delimiter2);
        if(pos == string::npos){
            break;
        }
        string part = line.substr(0, pos);
        line.erase(0,pos+delimiter2.length());
        parts.push_back(part);
    }
    if(line.empty())
        return parts;

    parts.push_back(line);
    return parts;
};
vector<int> getDate(string &t)
{
    trim(t, 0);
    vector<int> date = vector<int>();

    int index = t.find("-");
    if(index == string::npos){return date;}
    int hour = stoi(t.substr(0, index));
    t.erase(0, index+1);
    
    index = t.find("-");
    if(index == string::npos){return date;}
    int minute = stoi(t.substr(0, index));
    t.erase(0, index+1);

    index = t.find("-");
    if(index == string::npos){return date;}
    int day = stoi(t.substr(0, index));
    t.erase(0, index+1);

    index = t.find("-");
    if(index == string::npos){return date;}
    int month = stoi(t.substr(0, index));
    t.erase(0, index+1);

    int year = stoi(t.substr(0, t.length()));
    t.erase(0, t.length());

    date.push_back(hour);
    date.push_back(minute);
    date.push_back(day);
    date.push_back(month);
    date.push_back(year);
    return date;
}
bool checkDate(string &t, int min, int max)
{
    string number = "";
    if(max != -1)
    {
        int index = t.find("-");
        if(index == string::npos){return false;}
        number = t.substr(0, index);
        t.erase(0, index+1);
    }
    else
    {
        number = t;
        t.erase(0, t.size());
    }
    
    if(max == -1)
    {
        if(!std::all_of(number.begin(), number.end(), ::isdigit) || min > stoi(number)){
            return false;
        }
        return true;
    }
    if(!std::all_of(number.begin(), number.end(), ::isdigit) || min > stoi(number) || stoi(number) > max){
        return false;
    }
    return true;
}
bool correctDate(string t, int time)
{
    trim(t, 0);
    if(time == 1){
        
        if(!checkDate(t, 0, 24)) //hour
        {
            return false;
        }
        
        if(!checkDate(t, 0, 59)) //minute
        {
            return false;
        }
    }
    
    if(!checkDate(t, 1, 31)) //day
    {
        return false;
    }

    if(!checkDate(t, 1, 12)) //month
    {
        return false;
    }
    if(!checkDate(t, 1)) //year
    {
        return false;
    }
    
    return true;
}