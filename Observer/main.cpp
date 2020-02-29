#include <iostream>
#include <string>
#include <list>

using namespace std;

class SupervisedString;

class IObserver {
public:
    virtual void handleEvent(const SupervisedString &) = 0;
};

class SupervisedString // Observable class
{
    string _str;
    list<IObserver *> _observers;

    void _Notify() {
        for (auto &observer: _observers) {
            observer->handleEvent(*this);
        }
    }

public:
    void add(IObserver &ref) {
        _observers.push_back(&ref);
    }

    void remove(IObserver &ref) {
        _observers.remove(&ref);
    }

    const string &get() const {
        return _str;
    }

    void reset(string str) {
        _str = str;
        _Notify();
    }
};

class Reflector : public IObserver // Prints the observed string into cout
{
public:
    virtual void handleEvent(const SupervisedString &ref) {
        cout << ref.get() << endl;
    }
};

class Counter : public IObserver // Prints the length of observed string into cout
{
public:
    virtual void handleEvent(const SupervisedString &ref) {
        cout << "length = " << ref.get().length() << endl;
    }
};

int main() {
    SupervisedString str;
    Reflector refl1, refl2;
    Counter cnt1, cnt2;

    str.add(refl1);
    str.add(refl2);

    str.add(cnt1);
    str.add(cnt2);

    str.reset("Add 1,2,3,4");
    cout << endl;

    str.remove(cnt1);
    str.reset("Remove 3");
    cout << endl;

    return 0;
}