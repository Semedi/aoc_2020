#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <vector>
using namespace std;

std::vector<std::string> split(std::string str, std::string sep){
    char* cstr = const_cast<char*>(str.c_str());
    char* current;

    std::vector<std::string> arr;

    current=strtok(cstr, sep.c_str());

    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }

    return arr;
}


unordered_map<string, string> get_passport(string line)
{
    unordered_map<string, string> map;
    auto chunks = split(line, " ");

    for (const auto& word: chunks){
        vector<string> p = split(word, ":");
        map.insert(pair<string, string>(p[0], p[1]));
    }

    return map;
}

int main ()
{
    string str; 
    vector<unordered_map<string,string>> passports;
    ifstream file("input/day4.txt");
    string input = "";

    while (getline(file, str)) {
        input+=str;
        if (str == "")
        {
            string p = input;
            passports.push_back(get_passport(p));
            input = "";
        }
        else 
        {
            input+=" ";
        }
    }

    int count = 0;
    for (const auto& passport: passports){
        
        count += (passport.size() == 8) || (passport.size() == 7 && passport.find("cid") == passport.end());
        std::for_each(passport.begin(), passport.end() , [](pair<string, string > p){
            cout << p.first << "->" << p.second << " ";
        });
        cout << "size: " << passport.size() << " count:" << count;
        cout << endl;
    }

    cout << "valid passports: " << count << endl;

    return 0;
}

