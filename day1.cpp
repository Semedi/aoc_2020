// function template
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define SUM 2020

/*
 --- Day 1: Report Repair ---
Part 1:
    Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.

    For example, suppose your expense report contained the following:

    1721
    979
    366
    299
    675
    1456

    In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.

    Of course, your expense report is much larger. Find the two entries that sum to 2020; what do you get if you multiply them together?

Part 2:
    They offer you a second one if you can find three numbers in your expense report that meet the same criteria.
*/

int part1(std::vector<int> v) {
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        for(std::vector<int>::iterator jt = v.begin(); jt != v.end(); jt++) {
            if (*it + *jt == SUM){

                std::cout << "n1:" << *it << " n2:" << *jt << std::endl;
                std::cout << "result:" << *it * *jt << std::endl;

                return 0;
            }
        }
    }

  return 1;
}

int part2(std::vector<int> v) {
    std::unordered_map<int, int> m;

    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        m.insert(std::pair<int, int>(*it, SUM - *it));
    }

    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        int found = 0;

        std::for_each(m.begin(), m.end() , [&](std::pair<int, int > e){
                int res = e.second - *it;

                if (res > 0 && m.find(res) != m.end()){
                    std::cout << "n1:" << *it << " n2:" << res << " n3:" << e.first << std::endl;
                    std::cout << "result:" << *it * res * e.first << std::endl;
                    found = *it * res * e.first;

                    return;
                }

        });

        if (found > 0)
            return 0;
    }

    return 1;
}

int main () {
    std::ifstream file("input/day1.txt");
    std::string str; 
    std::vector<int> v;

    while (std::getline(file, str)) {
        v.push_back(stoi(str));
    }

    part1(v);
    part2(v);

    return 0;
}
