#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
int main ()
{
    std::string str; 
    std::ifstream file("input/day7.txt");

    //regex rgx("([a-z]+ [a-z]+) bags  contain \\d [a-z]+ [a-z]+ bags?[.|,]");
    regex rgx("^([a-z]+ [a-z]+) bags contain((?: \\d [a-z]+ [a-z]+ bags?,?)*)\\.$");
    while (std::getline(file, str)) {
        cout << str << endl;

        std::smatch matches;
        if (regex_search(str, matches, rgx)) {

            cout << "entro" << endl; 
            cout << matches[0].str() << endl; 

        }
        else {
            cout << "match error!" << endl;

            return 1;
        }

        break;
    }

    return 0;
}
