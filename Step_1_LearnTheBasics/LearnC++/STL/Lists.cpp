#include <iostream>
#include <list>

using namespace std;

int main() {
    // List is similar to vector. Vectors support only end insertions but list also support front operations.
    // A singly linked list is maintained for vectors whereas for lists a doubly linked list is maintained.

    list<int> ls;
    ls.push_back(3);
    ls.emplace_back(4);
    ls.push_front(2);
    ls.emplace_front(1);
    for(auto it: ls) cout << it << " ";
    ls.pop_back();
    ls.pop_front();
    cout << endl ;
    for(auto it: ls) cout << it << " ";

    // Rest functions are same as in vectors --> size, swap, clear, insert, begin, end, rbegin, rend

}