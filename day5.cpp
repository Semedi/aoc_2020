#include <iostream>
#include <fstream>

using namespace std;
int row(string seat, int b, int u){
    if (b == u)
        return b;

    char letter = seat.front();

    if (letter == 'F')
        u = (u-b)/2 + b;

    if (letter == 'B')
        b = (u-b)/2 + 1 + b;

    return row(seat.substr(1, seat.length()), b, u);
}

int column(string seat, int b, int u){
    if (b == u)
        return b;

    char letter = seat.front();

    if (letter == 'L')
        u = (u-b)/2 + b;

    if (letter == 'R')
        b = (u-b)/2 + 1 + b;

    return column(seat.substr(1, seat.length()), b, u);
}

int main ()
{
    string str; 
    ifstream file("input/day5.txt");
    // read input
    while (getline(file, str)) {
        cout << str << endl;
        string str = "FBFBBFFRLR";
        //cout << str.substr(0, 7) << endl;
        //cout << 127/2 << endl;
        cout << row(str.substr(0,str.length()-3), 0, 127) << endl; 
        cout << column(str.substr(str.length()-3), 0, 7) << endl;

        break;
    }


}
