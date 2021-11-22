//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
//#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include "ISequence.hpp"
#include "ListSequence.hpp"
#include "ArraySequence.hpp"
#include "Complex.hpp"
#include <vector>
#include "WebAssembly.hpp"

using namespace std;


int main() {
    cout << typeid(DynamicArray<int>) << endl;
    return 0;
}


#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &MainStartUI, emscripten::allow_raw_pointers());
}
#endif
//#pragma clang diagnostic pop