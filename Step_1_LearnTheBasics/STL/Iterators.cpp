#include <iostream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

int main() {

    vector<int> x = {1,2,3,4,5};
    
    // Iterators : Iterators allow traversal through STL containers (like vector, map, set).
    vector<int>::iterator start_it = x.begin();
    vector<int>::iterator end_it = x.end();
    
    cout << *(end_it) << endl;      // output : garbage value stored in the memory location just after the last element 
    start_it++;   // now it points at one address ahead of previous value , so now at second element
    cout << *(start_it) << endl;
    start_it += 3;        // will now point at the 5th element
    cout << *(start_it) << endl;
    end_it--;       // now end_it will point at the last element
    cout << *(end_it) << endl;      // output : 5

    vector<int> v = {10, 20, 30, 40};
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    // v.begin() → Points to first element.
    // v.end() → Points past the last element.
    // *it → Dereferences the iterator to access value.
    

    // Reverse Iterators : Reverse iterators iterate backward from the end.
    // v.rbegin() → Points to last element.
    // v.rend() → Points before first element.
    vector<int>::reverse_iterator rit;
    for (rit = v.rbegin(); rit != v.rend(); rit++) {
        cout << *rit << " ";
    }
    // Iterators declaring using auto
    cout << endl << "Iterators declaring using auto" << endl;
    for (auto x_it = v.begin(); x_it != v.end(); x_it++) {
        cout << *x_it << " ";
    }
    cout << endl;
    for (auto y_rit = v.rbegin(); y_rit != v.rend(); y_rit++) {
        cout << *y_rit << " ";
    }
    cout << endl;

    // Advamcing Bidirectional iterators 
    set<int> s = {1, 2, 3, 4, 5};
    set<int>::iterator iter = s.begin();
    cout << *iter << endl;              // Output : 1
    // move iter 3 positions ahead
    advance(iter, 3);
    cout << *iter << endl;              // Output : 4
    // move iter 2 positions behind
    advance(iter, -2);
    cout << *iter << endl;              // Output : 2

    set<int>::iterator s_it = s.begin();
    
    // Get an iterator 3 positions ahead of 'it'
    auto next_it = next(s_it, 3);
    cout << *next_it << endl;  // Output: 4

    // Get an iterator 2 positions behind 'next_it'
    auto prev_it = next(next_it, -2);
    cout << *prev_it << endl;  // Output: 2
    
    return 0;
}