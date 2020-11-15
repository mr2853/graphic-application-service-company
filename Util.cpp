#include "Util.hpp"
#include "Class/Company.hpp"

vector<string> tokenization(string &line, string delimiter1, string delimiter2)
{
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
vector<string> tokenization(string &line, string delimiter1, string delimiter2, string del3){
    vector<string> parts = vector<string>();
    int pos;
    pos = line.find(delimiter1);
    if(pos == string::npos){ return parts; }

    line.erase(0,pos+delimiter1.length());
    pos = line.find(delimiter2);
    if(pos == string::npos){ return parts; }

    string part = line.substr(0, pos);
    line.erase(0,pos+delimiter2.length());
    if(part == "true"){ return parts; }

    while(true){
        if(del3 == "Audit")
        {
            pos = line.find("Auditor[");
            if(pos == string::npos){
                break;
            }
            line.erase(0,pos);

            pos = line.find(",date:Date[");
            if(pos == string::npos){
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
        if(parts.size() == 2 && del3 == "Commercialist")
        { //salary:300,businessContact<contact:contact 1$contact:contact 2$contact:contact 3>]#Auditor[d
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
            
            string part = line.substr(0, pos);
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
    vector<int> date = vector<int>();

    int index = t.find("-");
    if(index == string::npos){return date;} // exception
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
std::string trim(const std::string &s)
{
	auto start = s.begin();
	while (start != s.end() && std::isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (std::distance(start, end) > 0 && std::isspace(*end));

	return std::string(start, end + 1);
}
bool correctDate(string t)
{
    int index = t.find("-");
    if(index == string::npos){return false;}
    string hour = t.substr(0, index);
    t.erase(0, index+1);
    if(!std::all_of(hour.begin(), hour.end(), ::isdigit)){
        return false;
    }
    
    index = t.find("-");
    if(index == string::npos){return false;}
    string minute = t.substr(0, index);
    t.erase(0, index+1);
    if(!std::all_of(minute.begin(), minute.end(), ::isdigit)){
        return false;
    }

    if(t.find("-") != string::npos){
        index = t.find("-");
        if(index == string::npos){return false;}
        string day = t.substr(0, index);
        t.erase(0, index+1);
        if(!std::all_of(day.begin(), day.end(), ::isdigit)){
            return false;
        }

        index = t.find("-");
        if(index == string::npos){return false;}
        string month = t.substr(0, index);
        t.erase(0, index+1);
        if(!std::all_of(month.begin(), month.end(), ::isdigit)){
            return false;
        }
    }

    string year = t.substr(0, t.length());
    t.erase(0, t.length());
    if(!std::all_of(year.begin(), year.end(), ::isdigit)){
        return false;
    }
    return true;
}
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
