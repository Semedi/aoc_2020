#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

typedef std::unordered_map<std::string, int> tbag;
using namespace std;

int main ()
{
    std::string str; 
    std::ifstream file("input/day7.txt");
    regex parent_rgx("^(\\w+ \\w+).*$");
    regex child_rgx("(\\d+) (\\w+ \\w+)");
    unordered_map<string, tbag> bags;

    while (std::getline(file, str)) {

        smatch matches;
        if (regex_search(str, matches, parent_rgx)) {

            auto parent = matches[1].str();

            auto rbegin = sregex_iterator(str.begin(), str.end(), child_rgx);
            auto rend   = sregex_iterator();
            for (auto i = rbegin; i != rend; ++i){
                smatch match = *i;
                cout << match.str() << endl;
            }
        }
        else {
            cout << "match error!" << endl;
            return 1;
        }

        break;
    }

    return 0;
}
