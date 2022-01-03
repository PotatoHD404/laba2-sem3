#include <iostream>
#include "Board.hpp"
#include "MiniMax.hpp"

using namespace std;


int main() {
    Board b(10);
//    b.Set(0, 4, 'x');
//    b.Set(1, 3, 'x');
//    b.Set(2, 2, 'x');
//    b.Set(3, 1, 'x');
//    b.Set(4, 0, 'x');
//    b.Set(0, 5, 'x');
//    b.Set(3, 3, 'x');
//    b.Set(0, 3, 'x');
//    b.Set(1, 2, 'x');
//    b.Set(2, 1, 'x');
//    b.Set(3, 0, 'x');
    size_t x, y;

//    cout << b.GetGameState() << endl;
    while (b.GetGameState() == 0) {
        cin >> x >> y;
        b.Set(x, y, 'x', true);
        auto move = PredictMove(b);
        cout << b << endl << move << endl;
//        if (move != Pair<size_t>{(size_t) -1, (size_t) -1})
        b.Set(move.first, move.second, 'o', true);
        cout << b << endl;
    }
    cout << b << endl;
    cout << b.GetGameState() << endl;
    return 0;
}