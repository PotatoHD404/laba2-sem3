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
using namespace Sorts;
using namespace std::chrono;

const char *MSGS[] = {"0. Quit",
                      "1. Int",
                      "2. Float",
                      "3. String",
                      "4. Complex"};


const char *MSGS1[] = {"0. Quit",
                       "1. Init sequence",
                       "2. Add value to sequence",
                       "3. Remove value from sequence",
                       "4. Print sequence",
                       "5. Fill with random values",
                       "6. Sort"};

const char *MSGS2[] = {"0. Quit",
                       "1. ListSequence",
                       "2. ArraySequence"};

const char *MSGS3[] = {"0. Quit",
                       "1. QuickSort",
                       "2. ShellSort",
                       "3. InsertionSort"};


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

template<typename T>
T InputValue() {

    bool success = false;
    T value;
    while (!success) {
        cout << "Input value:\n";
        stringstream ss(readline());
        try {
            ss >> value;
            success = true;
        }
        catch (exception &e) {
            cout << "An error has occurred: " << e.what() << "\nTry again!\n";
        }
    }
    return value;
}

template<typename T>
T GenRandom(mt19937 &rng) {
    if constexpr(std::is_same<T, string>::value) {
        static string alphanum = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
        uniform_int_distribution<unsigned> distribution(0, alphanum.length() - 1);
        string res;
        for (int i = 0; i < 5; ++i) {
            res += alphanum[distribution(rng)];
        }
        return res;
    } else if constexpr(std::is_same<T, Complex>::value) {
        uniform_real_distribution<float> distribution(-1, 1);
        return Complex((float) distribution(rng), (float) distribution(rng));
    } else if constexpr(std::is_same<T, int>::value) {
        uniform_int_distribution<int> distribution(-1000, 1000);
        return (int) distribution(rng);
    } else if constexpr(std::is_same<T, float>::value) {
        uniform_real_distribution<float> distribution(-10, 10);
        return (float) distribution(rng);
    } else {
        throw NotImplemented("", "");
    }
}

int DialogValue(const string &msg) {
    string error;
    int choice = -1;
    do {
        cout << error;
        error = "You're wrong. Try again!\n";
        cout << msg << endl;
        cout << "Make your choice: " << endl;
        stringstream ss(readline());
        ss >> choice;
    } while (choice < 0);
    return choice;
}

template<typename T>
void StartUI() {
    random_device rd;
    mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
                    chrono::duration_cast<std::chrono::seconds>(
                            chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (mt19937::result_type)
                    chrono::duration_cast<chrono::microseconds>(
                            chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    mt19937 rng(seed);
    int choice = 1;
    string tmp;
    unique_ptr<Enumerable<T>> seq = make_unique<ArraySequence<T>>();
    while (choice) {
        try {
            choice = Dialog(MSGS1);
            T value1, value2;
            int count;
            switch (choice) {
                case 0:
                    break;
                case 1: {
                    choice = Dialog(MSGS2);
                    if (choice == 1)
                        seq = make_unique<ListSequence<T>>();
                    else if (choice == 2)
                        seq = make_unique<ArraySequence<T>>();
                    choice = 1;
                    break;
                }

                case 2: {
                    seq->Add(InputValue<T>());
                    break;
                }

                case 3:
                    seq->Remove(InputValue<T>());
                    break;

                case 4:
                    cout << "ISequence: " << *seq << endl;
                    break;
                case 5:
                    count = DialogValue("Input items count");
                    for (int i = 0; i < count; ++i) {
                        seq->Add(GenRandom<T>(rng));
                    }
                    break;
                case 6:
                    choice = Dialog(MSGS3);
                    if (choice) {
                        ISort<T> *sort = &QuickSort<T>;
                        if (choice == 2)
                            sort = &ShellSort<T>;
                        else if (choice == 3)
                            sort = &InsertionSort<T>;
                        auto t1 = high_resolution_clock::now();
                        seq->Sort(*sort);
                        auto t2 = high_resolution_clock::now();
                        duration<double, milli> ms_double = t2 - t1;
                        cout << "Result: " << ms_double.count() << "ms" << endl;
                    }
                    choice = 1;
                    break;
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
}

void MainStartUI() {
//    int && res1 = move(1);
    int choice = 1;

    while (choice) {
        cout << "Enter data type:" << endl;
        choice = Dialog(MSGS);
        switch (choice) {
            case 0:
                break;
            case 1:
                StartUI<int>();
                break;
            case 2:
                StartUI<float>();
                break;
            case 3:
                StartUI<string>();
                break;
            case 4:
                StartUI<Complex>();
                break;
            default: {
                cout << "How did you end up here?" << endl;
                break;
            }
        }
    }
}

template<typename T, int N = 1000>
auto const &test_data1() {
    static random_device rd;
    static mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
                    chrono::duration_cast<chrono::seconds>(
                            chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (mt19937::result_type)
                    chrono::duration_cast<chrono::microseconds>(
                            chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    static mt19937 rng = mt19937(seed);
    static array<T, N> data;
    static bool called;
    if (!called) {
        generate(
                data.begin(), data.end(), []() { return GenRandom<T>(rng); });
        called = true;
    }
    return data;
}


int main() {
//    using Seq = ListSequence<int>;
//    using T = typename Seq::type;
//    Enumerable<T> &&seq = Seq();
//    auto test_data = test_data1<T, 3>();
//    vector<T> data(test_data.begin(), test_data.end());
//    for (const T &el: test_data) {
//        seq.Add(el);
//    }
//    auto beg = data.begin();
//    sort(data.begin(), data.end());
//    for (T el: test_data) {
//        cout << el << " " << *beg++ << endl;
//    }
//    cout << endl;
//    seq.Sort(Sorts::QuickSort<T>);
//
//    auto begin = seq.begin();
//    for (const T &el: data) {
//        cout << *(begin++) << " " << el << endl;
//    }
//    ListSequence<int> a;
//    Implementation<RandomAccessIterator<int>> sas(new RandomAccessIterator<int>(a));
//    using Seq = ListSequence<int>;
//    using T = typename Seq::type;
//    Enumerable<T> &&seq = Seq();
//    array<T, 1000> test_data = ::test_data<T>();
//    vector<T> data(test_data.begin(), test_data.end());
//    for (T el: test_data) {
//        seq.Add(el);
//    }
//    seq.Sort(Sorts::QuickSort<T>);
////    sort(data.begin(), data.end());
//    auto begin = seq.begin();
//    auto begin1 = test_data.begin();
//    for (T el: data) {
//        cout << *(begin1++) << " " << *(begin++) << " " << el << endl;
//    }
    MainStartUI();
    return 0;
}


#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &MainStartUI, emscripten::allow_raw_pointers());
}
#endif
//#pragma clang diagnostic pop