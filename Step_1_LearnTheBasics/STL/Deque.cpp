#include <iostream>
#include <deque>

using namespace std;

int main() {
    // Deque is adqo similar to lists and vectors
    deque<int> dq;
    dq.push_back(3);
    dq.emplace_back(4);
    dq.push_front(2);
    dq.emplace_front(1);
    for(auto it: dq) cout << it << " ";
    dq.pop_back();
    dq.pop_front();
    cout << endl ;
    for(auto it: dq) cout << it << " ";
    // dq.back() : returns last element ... dq.front() : returns first element
    cout << endl << dq.back();
    cout << endl << dq.front();
    
    // Rest functions are same as in vectors --> size, swap, clear, insert, begin, end, rbegin, rend
}