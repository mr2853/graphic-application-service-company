#include "Util.hpp"
#include "Class/Company.hpp"

vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3){
    vector<string> parts = vector<string>();
    //cout << "all: " << line << "\n\n" << endl;
    int pos;
    pos = line.find(delimiter1);
    if(pos == -1){ return parts; }

    line.erase(0,pos+delimiter1.length());
    pos = line.find(delimiter2);
    if(pos == -1){ return parts; }

    string part = line.substr(0, pos);
    line.erase(0,pos+delimiter2.length());
    if(part == "true"){ return parts; }

    while(true){
        if(parts.size() == 2 && del3 != "")
        {
            pos = line.find("],");
            if(pos == -1){
                break;
            }
            
            string part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,pos+2);
            continue;
        }
        if(del3 == "Audit")
        {
            pos = line.find("Auditor[");
            if(pos == -1){
                break;
            }
            line.erase(0,pos);

            pos = line.find(",date:Date[");
            if(pos == -1){
                break;
            }
            
            string part = line.substr(0, pos);
            parts.push_back(part);
            line.erase(0,pos+7);

            part = line.substr(0, line.length());
            parts.push_back(part);
            line.erase(0,line.length());
            break;
        }

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
    if(line.empty())
        return parts;

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
