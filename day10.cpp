#include <iostream>
#include <fstream>
#include <set>

using namespace std;
int main () {
    std::ifstream file("input/day10.txt");
    std::string str; 

    std::set<int> v;
    v.insert(0);

    while (std::getline(file, str))
        v.insert(stoi(str));

    int n1 = 1, n3 = 1;
    for (auto it = ++(next(v.begin())); it != v.end(); ++it){
        int diff = *(it) - *prev(it);
        cout << *it << endl;

        if (diff == 1) n1++;
        if (diff == 3) n3++;
    }

    v.insert(*(--v.end())+3);
    cout << "part1: " << n1*n3 << endl;
    cout << "n3: " << n1 << " n3:" << n3 << endl;


    return 0;

}
