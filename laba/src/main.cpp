#define _CRTDBG_MAP_ALLOC

#include <map>
#include <iostream>
#include "Utils.hpp"
#include "ArraySequence.hpp"

using namespace std;


int main() {
    ArraySequence<int> a{5, 4, 3, 2, 1};
    cout << Sort(a) << endl;
    return 0;
}