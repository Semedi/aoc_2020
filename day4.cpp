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

    // read input
    while (getline(file, str)) {
        input+=str;
        if (str == "")
        {
            passports.push_back(get_passport(input));
            input = "";
        }
        else 
        {
            input+=" ";
        }
    }
    passports.push_back(get_passport(input));

    // part 1
    int count = 0;
    for (const auto& passport: passports){
        count += (passport.size() == 8);
        count += (passport.size() == 7 && passport.find("cid") == passport.end());
    }

    cout << "part 1 valid passports: " << count << endl;

    // part 2
    count = 0;
    for (auto& passport: passports){
        if (!((passport.size() == 8) ||
            (passport.size() == 7 && passport.find("cid") == passport.end())))
            continue;

        bool byr = stoi(passport["byr"]) >= 1920 && stoi(passport["byr"]) <= 2002;
        bool iyr = stoi(passport["iyr"]) >= 2010 && stoi(passport["iyr"]) <= 2020;
        bool eyr = stoi(passport["eyr"]) >= 2020 && stoi(passport["eyr"]) <= 2030;

        if (!(byr && iyr && eyr))
            continue;

        string hgt = passport["hgt"];
        string cmin = hgt.substr(hgt.length()-2);

        if (!(cmin == "cm" || cmin == "in"))
            continue;

        int h = stoi(hgt.substr(0, hgt.length()-2));

        if (!((cmin == "cm" && h >= 150 && h <= 193) || 
                    (cmin == "in" && h >= 59 && h <= 76)))
            continue;

        regex hair_rgx("#[a-f0-9]{6}$");
        if (!regex_match(passport["hcl"], hair_rgx))
            continue;

        regex eye_rgx("amb|blu|brn|gry|grn|hzl|oth");
        if (!regex_match(passport["ecl"], eye_rgx))
            continue;

        regex pid_rgx("[0-9]{9}");
        if (!regex_match(passport["pid"], pid_rgx))
            continue;

        count++;
}
cout << "part 2 valid passports: " << count << endl;

return 0;
}

