#include <iostream>
#include "Board.hpp"
#include "MiniMax.hpp"

using namespace std;


int main() {
    Board b(4);
//    b.Set(1, 0, 'x');
//    b.Set(1, 2, 'x');
//    b.Set(0, 2, 'x');
    size_t x, y;
//
////    cout << b.GetGameState() << endl;
    while (b.GetGameState() == 0) {
        cin >> x >> y;
        b.Set(x, y, 'x');
        auto move = PredictMove(b);
        cout << b << endl << move << endl;
//        if (move != Pair<size_t>{(size_t) -1, (size_t) -1})
        b.Set(move.first, move.second, 'o');
        cout << b << endl;
    }
    cout << b << endl;
    cout << b.GetGameState() << endl;
    return 0;
}