#include <iostream>
#include <fstream>
#include <regex>

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

int contained(string phrase)
{

    auto bags_vec = split(phrase, ",");

    regex rgx("^ (\\d) ([a-z]+ [a-z]+) bags?$");
    for (auto& b: bags_vec){
        std::smatch matches;
        if (regex_search(b, matches, rgx)) {
            cout << b << endl;
        }
        else {
            cout << "match error asdsad" << endl;
        }
    }

    return 0;
}

int main ()
{
    std::string str; 
    std::ifstream file("input/day7.txt");
    regex rgx("^([a-z]+ [a-z]+) bags contain((?: \\d [a-z]+ [a-z]+ bags?,?)*)\\.$");

    while (std::getline(file, str)) {

        std::smatch matches;
        if (regex_search(str, matches, rgx)) {

            cout << matches[1].str() << endl; 
            contained(matches[2].str());

        }
        else {
            cout << "match error!" << endl;

            return 1;
        }

        break;
    }

    return 0;
}
