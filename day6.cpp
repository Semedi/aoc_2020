#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;
int main ()
{
    string str; 
    ifstream file("input/day6.txt");
    string input = "";
    set<char> answers;
    unordered_map<char, int> answers_map;
    int part1 = 0;
    int part2 = 0;
    int p = 0;

    while (getline(file, str)) {
        if (str == "")
        {
            part1 += answers.size();
            for_each(answers_map.begin(), answers_map.end() , [&](pair<char, int > e){
                    if (e.second == p){
                        part2++;
                    }
            });

            // reset:
            answers.clear();
            answers_map.clear();
            p = 0;
        }
        else
        {
            p++;
            for (auto it=str.begin(); it != str.end(); it++){
                answers.insert(*it);

                auto e = answers_map.find(*it);
                if (e == answers_map.end())
                    answers_map.insert(pair<char, int>(*it, 1));
                else
                    e->second++;
            }
        }
    }
    part1 += answers.size();
    for_each(answers_map.begin(), answers_map.end() , [&](pair<char, int > e){
            if (e.second == p)
                part2++;
    });

    cout << "different answers: " << part1 << endl;
    cout << "answers (part2): " << part2 << endl;

    return 0;
}
