#include <iostream>
#include <fstream>

using namespace std;
int get_seat(string seat, int b, int u){
    if (b == u)
        return b;

    char letter = seat.front();

    if (letter == 'F' || letter == 'L')
        u = (u-b)/2 + b;

    if (letter == 'B' || letter == 'R')
        b = (u-b)/2 + 1 + b;

    return get_seat(seat.substr(1, seat.length()), b, u);
}

int main ()
{
    string str; 
    ifstream file("input/day5.txt");


    int maxid = 0;
    while (getline(file, str)) {
        int row    = get_seat(str.substr(0,str.length()-3), 0, 127); 
        int column = get_seat(str.substr(str.length()-3), 0, 7);

        int id = row * 8 + column; 

        maxid = (id > maxid) ? id: maxid;
    }

    cout << "max id: " << maxid << endl;


}
