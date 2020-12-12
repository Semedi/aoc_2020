#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;


unordered_map<int, int> DP;
vector<int> xs;

int dp(int i)
{
    if (i == xs.size()-1)
        return 1;

    if (DP.find(i) != DP.end())
        return DP.at(i);

    auto ans = 0;
    for (int j = i + 1; j < xs.size(); ++j){
        if (xs[j] - xs[i] <= 3)
            ans += dp(j);
    }
    DP[i] = ans;

    return ans;
}

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

        if (diff == 1) n1++;
        if (diff == 3) n3++;
    }

    v.insert(*(--v.end())+3);
    cout << "part1: " << n1*n3 << endl;
    cout << "n3: " << n1 << " n3:" << n3 << endl;

    copy(v.begin(), v.end(), back_inserter(xs));
    cout << "part2: " << dp(0) << endl;


    return 0;

}
