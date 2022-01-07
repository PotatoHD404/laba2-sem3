#include <iostream>
#include "Board.hpp"
#include "MiniMax.hpp"
#include "WebAssembly.hpp"

using namespace std;
const char *MSGS1[] = {"0. Quit",
                       "1. Start game"};

template<int N>
int Dialog(const char *(&msgs)[N]) {
    string error;
    int choice = -1;
    do {
        cout << error;
        error = "You're wrong. Try again!\n";
        for (int i = 0; i < N; ++i) {
            cout << msgs[i] << endl;
        }
        cout << "Make your choice: \n";
        stringstream ss(readline());
        ss >> choice;
    } while (choice < 0 || choice >= N);
    return choice;
}

int DialogValue(const string &msg) {
    string error;
    int choice = -2;
    do {
        cout << error;
        error = "You're wrong. Try again!\n";
        cout << msg << endl;
        cout << "Make your choice: " << endl;
        stringstream ss(readline());
        ss >> choice;
    } while (choice < -1);
    return choice;
}

void StartUI() {
    int choice = 1;
    auto b = new Board(3);
//    Pair<size_t> move{};
    stringstream ss;
//    ss >> choice;
    while (choice) {
        try {
            choice = Dialog(MSGS1);

            switch (choice) {
                case 0: {
                    break;
                }
                case 1: {
                    delete b;
                    b = new Board(DialogValue("Input field size"));
                    while (b->GetGameState() == 0) {
                        long x = -1, y = -1;
                        try {
                            cout << "Enter your move, enter to quit:" << endl;
                            cout << "Input (x y)" << endl;
                            ss = stringstream(readline());
                            ss >> x >> y;
                            if (x == y && y == -1) {
                                break;
                            }
                            b->Set(x, y, 'x', true);
//                            move = PredictMove(*b);
//                            cout << "aaaaaaaaaaaaaaaaaaaaaaa" << endl;
                            cout << *b << endl;
                            cout << "AI move: " << Pair(0, 1) << endl;
//        if (move != Pair<size_t>{(size_t) -1, (size_t) -1})
//                            b->Set(move.first, move.second, 'o', true);
//                            cout << *b << endl;
                        }
                        catch (exception &e) {
                            cout << "An error has occurred: " << e.what() << "\nTry again!\n";
                        }
                    }
                    cout << *b << endl;
                    if (b->GetGameState() == '_')
                        cout << "Draw..." << endl;
                    else if (b->GetGameState() == 'o')
                        cout << "Os won!" << endl;
                    else if (b->GetGameState() == 'x')
                        cout << "Xs won!" << endl;
                    else
                        cout << "Game didn't finish" << endl;

                    break;
                }
                default: {
                    cout << "How did you end up here?" << endl;
                    break;
                }
            }
        }
        catch (exception &e) {
            cout << "An error has occurred: " << e.what() << "\nTry again!\n";
        }
    }
    delete b;
}


int main() {
    Board b(10);
    stringstream ss;


//    cout << b.GetGameState() << endl;

    while (b.GetGameState() == 0) {
        long x = -1, y = -1;
        cout << "Enter your move, enter to quit:" << endl;
        ss = stringstream(readline());
        ss >> x >> y;
        if (x == y && y == -1) {
            break;
        }
        b.Set(x, y, 'x', true);
        auto move = PredictMove(b);
        cout << b << endl << move << endl;
//        if (move != Pair<size_t>{(size_t) -1, (size_t) -1})
        b.Set(move.first, move.second, 'o', true);
        cout << b << endl;
    }
    cout << b << endl;
    Utils::PPrint(cout, b.GetGameState());


//    StartUI();
    return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &StartUI, emscripten::allow_raw_pointers());
}
#endif