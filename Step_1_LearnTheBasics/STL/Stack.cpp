#include <iostream>
#include <stack>

using namespace std;

int main() {
    // Stack : works on LIFO principle ... 3 major operations only Push (psuh & emplace), pop and top
    // all the operations are performed in O(1)

    stack<int> st;
    st.push(1);         // {1}
    st.push(2);         // {2, 1}
    st.push(3);         // {3, 2, 1}
    st.push(3);         // {3, 3, 2, 1}
    st.emplace(5);      // {5, 3, 3, 2, 1}

    cout << st.top() << endl;       // prints topmost element of the stack i.e. 5.
    // We can't directly access elements in the stack using index .. for ex - st[0] , st[3] etc are invalid
    st.pop();           // removes topmost element
    cout << st.top() << endl;
    cout << st.size() << endl;
    cout << st.empty() << endl;             // Returns 1 if stack is empty else 0
    cout << st.size() << endl;
    while (!st.empty()) {
        cout << " hii " << st.top() << " ";
        st.pop();
    }
    cout << endl << st.empty(); 
    stack<int> st1, st2;
    st1.swap(st2);
}