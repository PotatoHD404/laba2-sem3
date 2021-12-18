#include <iostream>
#include "Board.hpp"
#include "MiniMax.hpp"

using namespace std;


int main() {
    Board b(3);
//    b.Get(0, 0) = 'x';
//    b.Get(1, 0) = 'x';
//    b.Get(2, 0) = 'x';
    size_t x, y;

//    cout << b.GetGameState() << endl;
    while (b.GetGameState() == 0) {
        cin >> x >> y;
        b.Get(x, y) = 'x';
        auto move = PredictMove(b);
        cout << b << endl << move << endl;
        b.Get(move.first, move.second) = 'o';
        cout << b << endl;

    }
    cout << b << endl;
    return 0;
}