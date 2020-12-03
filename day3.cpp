#include<fstream>
#include <iostream>
#include <string>

#define WIDTH 31
#define HEIGHT 323

int tile(int x, int y)
{
    return (y * WIDTH) + (x % WIDTH);
}

int main(int argc, char*argv[])
{
  char c;
  std::ifstream in("input/day3.txt");
  bool map[WIDTH * HEIGHT];
  int i = 0;

  while(in.get(c)){
      if (c != '\n')
          map[i++] = (c == '#');
  }

  int trees = 0, x = 0;

  for (int y = 1; y < HEIGHT; y++){
      trees += map[tile(x+=3, y)];
  }
  std::cout << "trees encountered: " << trees << std::endl;


  //for(int i = 0; i < WIDTH*HEIGHT; i++){
  //    if (i % WIDTH == 0)
  //        std::cout << std::endl;

  //    std::cout << map[i];
  //}





  return 0;

}
