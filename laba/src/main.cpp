#define _CRTDBG_MAP_ALLOC

#include <map>
#include <iostream>

using namespace std;

class Base {
public:
    virtual ~Base() = default;

    virtual bool Get() const = 0;
};

class DerivedA : public Base {
public:
    [[nodiscard]] bool Get() const override {
        return true;
    }
};

class DerivedB : public Base {
public:
    [[nodiscard]] bool Get() const override {
        return false;
    }
};

template<class T>
class Creator {
public:
    virtual ~Creator() = default;

    virtual T &&Create() = 0;
};

template<class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType> {
public:
    BaseType &&Create() override {
        auto res = DerivedType();
        return move(res);
    }
};

template<class T, typename Key>
class Factory {
public:
    void Register(Key Id, Creator<T> *Fn) {
        FunctionMap[Id] = Fn;
    }

    T &Create(Key Id) {
        return (T &) FunctionMap[Id]->Create();
    }

    ~Factory() {
        auto i = FunctionMap.begin();
        while (i != FunctionMap.end()) {
            delete (*i).second;
            ++i;
        }
    }

private:
    std::map<Key, Creator<T> *> FunctionMap;
};

template<class DerivedType>
class DerivedBaseCreator : public DerivedCreator<DerivedType, Base> {
};

int main() {

    Factory<Base, int> temp;
    temp.Register(1, new DerivedBaseCreator<DerivedA>);
//    temp.Register(2, new DerivedBaseCreator<DerivedB>);
    Base &one = temp.Create(1);
//    auto two = temp.Create(2);
    cout << one.Get() << endl;
//    cout << two->Get() << endl;
    DerivedA a;
    DerivedB b;
    return 0;
}