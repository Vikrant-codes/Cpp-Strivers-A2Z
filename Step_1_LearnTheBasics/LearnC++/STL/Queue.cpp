#include <iostream>
#include <queue>

using namespace std;

int main() {
    // Queue : works on FIFO principle .. all the operations are performed in O(1) 

    queue<int> q;
    q.push(1);  // {1}
    q.push(2);  // {1,2}
    q.emplace(3); // {1,2,3}

    cout << "First Element : " << q.front() << "\t Last Element : " << q.back() << endl;
    q.back() = 5;       // {1,2,5}
    q.pop();    // {2,5}
    q.front() *= 2;   // {4,5}
    cout << "First Element : " << q.front() << "\t Last Element : " << q.back() << endl;

    // size swap empty same as stack
}