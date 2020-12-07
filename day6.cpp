#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main ()
{
    string str; 
    ifstream file("input/day6.txt");
    string input ="";
    set<char> answers;
    int n = 0;
    while (getline(file, str)) {
        //cout << str << endl;
        if (str == "")
        {
            n += answers.size();
            answers.clear();
        }
        else
        {
            for (auto it=str.begin(); it != str.end(); it++)
                answers.insert(*it);
        }
    }
    n += answers.size();

    cout << "different answers: " << n << endl;

    return 0;
}
