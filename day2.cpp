#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>

/*
 --- Day 2: Report Repair ---
Part 1:
  For example, suppose you have the following list:

  1-3 a: abcde
  1-3 b: cdefg
  2-9 c: ccccccccc

  Each line gives the password policy and then the password. The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.

Part 2:
  Given the same example list from above:

      1-3 a: abcde is valid: position 1 contains a and position 3 does not.
      1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
      2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.

*/

#define FIRST 1
#define SECOND 2
#define LETTER 3
#define WORD 4

struct Passwd {
  int first;
  int second;
  char letter;
  std::string word;

  Passwd(const std::smatch matches):
    first(std::stoi(matches[FIRST].str())),
    second(std::stoi(matches[SECOND].str())),
    letter(matches[LETTER].str()[0]),
    word(matches[WORD])
  {}

  bool check_part1()
  {
    int n = std::count(word.begin(), word.end(), letter);

    return (n >= first && n <= second);
  }

  bool check_part2()
  {
      int n = 0;
      int dfirst  = first - 1;
      int dsecond = second - 1;

      if (dfirst < 0 || dsecond >= word.length() )
          return false;

      n += (word[dfirst] == letter);
      n += (word[dsecond] == letter);

      return (n == 1);
  }


};

void part1(const std::vector<std::unique_ptr<Passwd>> &v)
{
      int count = 0;

      for (const auto& p : v) {
          count += p->check_part1();
      }

      std::cout << "part1, correct passwords: " << count << std::endl;
}

void part2(const std::vector<std::unique_ptr<Passwd>> &v)
{
      int count = 0;

      for (const auto& p : v) {
        count += p->check_part2();
      }

      std::cout << "part2, correct passwords: " << count << std::endl;
}

int main ()
{
    std::string str; 
    std::vector<std::unique_ptr<Passwd>> v;
    std::ifstream file("input/day2.txt");

    std::regex rgx("(\\d+)-(\\d+) ([a-z]): (\\w+)$");
    while (std::getline(file, str)) {

      std::smatch matches;
      if (std::regex_search(str, matches, rgx)) {
          v.push_back(std::unique_ptr<Passwd>(new Passwd(matches)));
      }
      else {
          std::cout << "Something unexpected happened!" << std::endl;

          return 1;
      }
    }

    part1(v);
    part2(v);

    return 0;
}
