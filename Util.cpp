#include "Util.hpp"
#include "Company.hpp"

vector<string> tokenization(string &line, string delimiter1, string delimiter2){
    vector<string> parts = vector<string>();
    int pos;
    pos = line.find(delimiter1);
    if(pos == -1){ return parts; }
    line.erase(0,pos+delimiter1.length());
    pos = line.find(delimiter2);
    string part = line.substr(0, pos);
    line.erase(0,pos+delimiter2.length());
    if(part == "true"){ return parts; }

    while(true){
        pos = line.find(delimiter1);
        if(pos == -1){
            break;
        }
        line.erase(0,pos+delimiter1.length());
        pos = line.find(delimiter2);
        if(pos == -1){
            break;
        }
        string part = line.substr(0, pos);
        line.erase(0,pos+delimiter2.length());
        parts.push_back(part);
    }
    parts.push_back(line);
    return parts;
};

/*void inputStrings(string &in, int &index, vector<string> &text)
{
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
};*/
