#include <iostream>
#include <vector>
#include "Skiplist.h"

using std::cout;
using std::endl;
using std::string;

void test_insert(Skiplist<int, string> &test) {
    cout << "INSERTION TEST STARTS." << endl;

    cout << test.insert(1, "abc") << " ";
    cout << test.insert(35, "abd") << " ";
    cout << test.insert(11, "ahd") << " ";
    cout << test.insert(66, "acd") << " ";
    cout << test.insert(44, "hff") << " ";
    cout << test.insert(11, "ahd") << " ";

    cout << endl;
    cout << "INSERTION TEST ENDS." << endl;
}

void test_erase(Skiplist<int, string> &test) {
    cout << "ERASE TEST STARTS." << endl;

    cout << test.erase(1) << " ";
    cout << test.erase(7) << " ";
    cout << test.erase(66) << " ";
    cout << test.erase(44) << " ";

    cout << endl;

    test.display();

    cout << test.erase(35) << " ";
    cout << endl;

    test.display();

    cout << test.erase(11) << " ";
    cout << test.erase(99) << " ";
    cout << endl;

    test.display();

    cout << endl;
    cout << "ERASE TEST ENDS." << endl;
}

void test_find(Skiplist<int, string> &test) {
    cout << "SEARCHING TEST STARTS." << endl;

    cout << test.find(1) << " ";

    cout << test.insert(34, "abd") << " ";
    cout << test.insert(18, "ahd") << " ";
    cout << test.insert(62, "acd") << " ";
    cout << test.insert(48, "hff") << " ";

    cout << test.find(62) << " ";

    cout << endl;
    cout << "SEARCHING TEST ENDS." << endl;
}


int main() {
    Skiplist<int, string> test(10);
    test_insert(test);
    test.display();

    test_erase(test);

    test_find(test);

    cout << "size of skiplist: " << test.size() << endl;
    cout << "is empty: " << test.empty() << endl;

    test.clear();

    cout << test.empty() << endl;

}
