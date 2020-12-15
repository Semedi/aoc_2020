#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

#define WIDTH 98
#define HEIGHT 97
using namespace std;

int up(int i)
{
    return i - WIDTH;
}

int down(int i)
{
    return i + WIDTH;
}

int left(int i)
{
    return i - 1;
}

int right(int i)
{
    return i + 1;
}

char raycast(vector<char> seats, int origin, int direction)
{
    int i;
    switch (direction) {
        case 1: i = up(left(origin)); break;
        case 2: i = up(origin); break;
        case 3: i = up(right(origin)); break;
        case 4: i = left(origin); break;
        case 5: i = right(origin); break;
        case 6: i = down(left(origin)); break;
        case 7: i = down(origin); break;
        case 8: i = down(right(origin)); break;
    }

    if (i < 0 || i >= seats.size())
        return 'L';

    char tile = seats[i];
    
    if (tile == '.')
        return raycast(seats, i, direction);

    return tile;
}


int tile(int x, int y)
{
    if (x < 0 || x >= WIDTH)
        return -1;

    if (y < 0 || y >= HEIGHT)
        return -1;

    return (y * WIDTH) + x;
}

void print_map(vector<char> seats)
{
    for (int i = 0; i < seats.size(); ++i){
        if (i%WIDTH == 0)
            cout << endl;

        cout << seats[i];

    }
}

void print_map_copy(vector<char> seats)
{
    for (int x = 0; x < WIDTH - 1; ++x){
        cout << endl;
        for (int y = 0; y < HEIGHT - 1; ++y){
            int i = tile(x,y);

            if (i != -1)
                cout << seats[i];
        }
    }
    cout << endl;
}

int count_neighbours(vector<char> seats, int x, int y, char target)
{
    int count = 0;

    for (auto const &dx: {-1 , 0, 1}){
        for (auto const &dy: {-1, 0, 1}){
            if (dx == 0 && dy == 0)
                continue;

            int col = (x + dx); 
            int row = (y + dy);
            int i = tile(col, row);

            if (i != -1){
                count += (seats[i] == target);
            }
        }
    }

    return count;
}

bool apply_raycast(vector<char> &seats)
{
    vector<char> dseats;
    for (int i = 0; i < seats.size(); ++i){
        int count = 0;
        char seat = seats[i];
        char next = seat;
        for (int direction = 1; direction <= 8; ++direction)
            count += raycast(seats, i, direction) == '#';

        if (seat != '.'){
            if (count >= 5)
                next = 'L';
            else if (count == 0)
                next = '#';
        }

        dseats.push_back(next);
    }

    auto changed = seats != dseats;
    seats = dseats;

    return changed;
}

bool tick(vector<char> &seats)
{
    vector<char> dseats;
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            int i = tile(x,y);
            assert(i != -1);
            char seat = seats[i];
            char next = seat;

            if (seat == 'L' and count_neighbours(seats, x, y, '#') == 0)
                next = '#';
            else if (seat == '#' and count_neighbours(seats, x, y, '#') >= 4)
                next = 'L';

            dseats.push_back(next);
        }
    }

    auto changed = (seats != dseats);

    seats = dseats;

    return changed;
}


int main(int argc, char*argv[])
{
    char c;
    vector<char> seats;
    ifstream in("input/day11.txt");

    while (in.get(c)){
        if (c != '\n')
            seats.push_back(c);
    }

    auto pos = tile(97,97);

    //cout << count_neighbours(seats, 8, 1, 'L') << endl;
    //print_map(seats);

    int count = 0;
    int p1 = 0;

    //part 1:
    //while (tick(seats)){
    //    count++;
    //}


    //count

    //print_map(seats);
    
    while (apply_raycast(seats));

    print_map(seats);
    for (const auto &seat: seats){
        p1 += (seat == '#');
    }
    cout << endl << p1 << " occupied seats." << endl;




    return 0;
}
