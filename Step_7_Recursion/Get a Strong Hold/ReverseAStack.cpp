// Reverse a stack using recursion
/*
Problem Statement: 
You are given a stack of integers. Your task is to reverse the stack using recursion. 
You may only use standard stack operations (push, pop, top/peek, isEmpty). 
You are not allowed to use any loop constructs or additional data structures like arrays or queues.
*/

// GFG - Reverse a Stack : Medium
/*
GFG - Reverse a Stack : Medium

You are given a stack st[]. You have to reverse the stack.

Note: The input array represents the stack from bottom to top (last element is the top). 
The output is displayed by printing elements from top to bottom after reversal.

Examples :-

Input: st[] = [1, 2, 3, 4]
Output: [1, 2, 3, 4]
Explanation: After reversing, the elements of stack are in opposite order.

Input: st[] = [3, 2, 1]
Output: [3, 2, 1]
Explanation: After reversing, the elements of stack are in opposite order.

Constraints :-
• 1 ≤ st.size() ≤ 100
• 0 ≤ stack element ≤ 100
*/

#include <bits/stdc++.h>
using namespace std;

/*
4
3
2
1

->

1
2
3
4
*/

void displayStack(stack<int> st) {
    cout << "Stack : ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}


// Iterative approach
void reverseStack1(stack<int> &st) {
    stack<int> temp;

    while(!st.empty()) {
        temp.push(st.top());

        st.pop();
    }

    st = temp;
}

// Recursive approach
void helper(stack<int>& st, stack<int>& temp) {
    if (st.empty()) return;

    temp.push(st.top());
    st.pop();

    helper(st, temp);
}

void reverseStack(stack<int>& st) {
    stack<int> temp;

    helper(st, temp);

    st = temp;
}

int main() {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);

    displayStack(st);

    reverseStack(st);

    displayStack(st);

    return 0;
}