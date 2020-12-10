#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
int main () {
    std::ifstream file("input/day9.txt");
    std::string str; 

    std::vector<long> v;
    while (std::getline(file, str)) {
        v.push_back(atol(str.c_str()));
    }

    //part 1
    int i;
    for (i = 25; i < v.size(); ++i){
        auto valid = false;
        for (int a = 0; a < 25; ++a){
            for (int b = 0; b < 25; ++b){
                valid |= (*(v.begin()+(i-25)+a) + *(v.begin()+(i-25)+b) == v[i]);
            }
        }

        if (!valid){
            cout << v[i] << endl;
            break;
        }
    }

    //part 2
    for (int a = 0; a < i; ++a){
        for (int b = a+2; b < i; ++b){
            auto init = v.begin() + a;
            auto end = v.begin() + b;
            if (accumulate(init, end, 0) == v[i]){
                cout << "weakness: " << *max_element(init, end) + *min_element(init, end) << endl;
            }
        }
    }

    return 0;

}
