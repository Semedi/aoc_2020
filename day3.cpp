#include<fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

#define WIDTH 31
#define HEIGHT 323
#define X 0
#define Y 1
#define T 2

int tile(int x, int y)
{
    return (y * WIDTH) + (x % WIDTH);
}

int main(int argc, char*argv[])
{
  char c;
  ifstream in("input/day3.txt");
  bool map[WIDTH * HEIGHT];
  int i = 0, checked = 0;
  long m = 1;

  while(in.get(c)){
      if (c != '\n')
          map[i++] = (c == '#');
  }

  // X Y T
  vector<tuple<int,int, bool>> dir{{1,1,0},{3,1,0},{5,1,0},{7,1,0},{1,2,0}}; 
  vector<tuple<int,int,int>> slope{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

  while (checked != slope.size()){
      for (int s = 0; s < slope.size(); s++){
        if (get<T>(dir[s])) continue;

        int x = get<X>(slope[s]) += get<X>(dir[s]);
        int y = get<Y>(slope[s]) += get<Y>(dir[s]);
        get<T>(dir[s]) = (y >= HEIGHT);
        if (y >= HEIGHT){
            checked++;
            cout << "slope:" << s << " trees encountered: " << get<T>(slope[s]) << endl;
            m *= get<T>(slope[s]);
        }

        get<T>(slope[s]) += map[tile(x,y)];

      }
  }

  cout << "result: " << m << endl;

  return 0;

}
  //x = 0;
  //for (int y = 1; y < HEIGHT; y++)
  //    trees += map[tile(x+=3, y)];
  //
  //cout << "trees encountered: " << trees << endl;


  //for(int i = 0; i < WIDTH*HEIGHT; i++){
  //    if (i % WIDTH == 0)
  //        std::cout << std::endl;

  //    std::cout << map[i];
  //}
