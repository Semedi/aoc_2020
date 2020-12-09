#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

typedef std::unordered_map<std::string, int> tbag;
typedef std::unique_ptr<tbag> ptr_bag;
using namespace std;

string target_bag = "shiny gold";

const bool holds(const unordered_map<string, ptr_bag> &bags, string outer)
{
    // bag is empty
    if (bags.at(outer)->size() == 0)
        return false;

    auto exists = bags.at(outer)->find(target_bag) != bags.at(outer)->end();

    // target_bag exists exists in child
    if (exists)
        return true;

    for (auto i = bags.at(outer)->begin(); i != bags.at(outer)->end(); ++i){
        exists |= holds(bags, i->first);
    }

    return exists;
}

int size(const unordered_map<string, ptr_bag> &bags, string outer)
{
    int n = outer != target_bag;
    if (bags.at(outer)->size() == 0)
        return n;

    for (auto i = bags.at(outer)->begin(); i != bags.at(outer)->end(); ++i){
        n += (i->second * size(bags, i->first));
    }

    return n;
}

int main ()
{
    std::string str; 
    std::ifstream file("input/day7.txt");
    regex parent_rgx("^(\\w+ \\w+).*$");
    regex child_rgx("(\\d+) (\\w+ \\w+)");
    unordered_map<string, ptr_bag> bags;

    while (std::getline(file, str)) {

        smatch matches;
        if (regex_search(str, matches, parent_rgx)) {

            auto parent = matches[1].str();

            ptr_bag child(new tbag());
            auto rbegin = sregex_iterator(str.begin(), str.end(), child_rgx);
            auto rend   = sregex_iterator();
            for (auto i = rbegin; i != rend; ++i){
                smatch match = *i;
                child->insert(pair<string, int>(match[2].str(), stoi(match[1].str())));
            }

            bags.insert(pair<string, ptr_bag>(parent, move(child)));
        }
        else {
            cout << "Pa tu CASA!" << endl;
            return 1;
        }
    }

    // part 1
    int count = 0;
    for (const auto& b: bags){
        count += holds(bags, b.first);
    }

    cout << count << " bags can hold shiny gold" << endl;

    //part 2
    cout << size(bags, target_bag) << " bags inside shiny gold" << endl;

    return 0;
}
