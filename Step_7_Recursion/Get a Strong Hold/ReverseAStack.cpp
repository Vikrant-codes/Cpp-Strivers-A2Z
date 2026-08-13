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

// helper method: prints the element of stack from top to bottom order
void printStack(stack<int> st) {
    cout << "Stack : ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

/*
Stack can't be reversed in place directly like how we reverse arrays, 
since in a stack we can operate only on the top element.
So, 
the basic and most efficient way to reverse a stack is to 
use an auxiliary space to store the elements popped from the stack.
Then, we can simply push these elements back to the stack to reverse the stack.
*/

// Iterative approach : Time Complexity : O(n) __ Space Complexity : O(n)
// (Using an extra space to store the stack elements -- can use a vector / stack to store the elements)
/*
We use an auxiliary stack to hold elements while popping them from the original stack. 
Since stacks are LIFO, pushing all elements into the auxiliary stack will naturally reverse their order. 
Finally, we replace the original stack with the auxiliary stack.
*/
void reverseStack1(stack<int> &st) {
    stack<int> temp;

    while(!st.empty()) {
        temp.push(st.top());
        st.pop();
    }

    st = temp;
}

// If we try to reverse the stack without using extra space to store the elements, then the time complexity will increase
// "Time - Space Tradeoff"

// Recursive Code Implementation : Time Complexity : O(n²) __ Space Complexity : O(n)
// (without using any extra space to store elements, although it still utilizes O(n) space due to recursive call stack)
/*
We want to reverse the stack without using any extra space to store the stack elements. Say,
        | 4 |                                   | 1 |
stack = | 3 |       ------------->     stack =  | 2 |
        | 2 |       after reversal              | 3 |
        | 1 |                                   | 4 |
        -----                                   -----

If we try to use recursion/backtracking concept, to store the current top element in a temp variable and 
reverse the rest of the stack, then we will have to insert the stored top element at the bottom of the stack.

say, for the above stack, we store the top value `4` in a temp variable and then pop it from the stack and 
call the recursive reverse function for the rest of stack, then it would do:
        | 4 |
stack = | 3 |
        | 2 |
        | 1 |
        -----
temp = 4, pop 4

        | 3 |       say we reversed this stack                      | 1 |
stack = | 2 |       --------------------------->            stack = | 2 |        
        | 1 |       using the reverse function                      | 3 |
        -----       and we get the reversed stack                   -----

Now, we have to put the temp value '4' in this reversed smaller stack. 
To get the final reversed stack, 4 must be placed at the bottom of stack.
So, we need to insert 4 at the bottom of stack & we know for stacks, we can't directly insert an element at any random position.
So, we will need to use a helper function which will pop elements and then push '4' at bottom and place the popped elements back.
To do so, we create another recursive method `insertAtBottom(stack<int>& st, int x)` which inserts x at bottom of stack st.

>> Recursive Approach 
The idea is to use the recursion to reverse the given stack.
• First, we keep removing elements from the stack until stack becomes empty.
• Once the stack is empty, we start going back in the recursion. 
  At each step, instead of placing the element back on top, we insert it at the bottom of the stack.
• To insert an element at the bottom, we recursively pop all elements, 
  push the current element, and then put the popped elements back.

>> Algorithm 
Define a helper function insertAtBottom to insert a value at the bottom of the stack.
• If the stack is empty, push the value.
• If the stack is not empty, pop the top element, recursively call insertAtBottom, and push the popped element back.

Define the main function reverseStack:
• If the stack is empty, return.
• Pop the top element, recursively reverse the rest of the stack.
• Use insertAtBottom to insert the popped element at the bottom of the stack.

>> Complexity Analysis 

# Time Complexity
O(n²), as each element is popped and inserted at the bottom (O(n) per element).

-> insertAtBottom()
If the stack has n elements:
    • It recursively pops all n elements → O(n)
    • Then pushes them back → O(n), but still overall O(n)
So:
    Time: O(n)
    Auxiliary space: O(n) — recursion stack. 
    If we don't consider this recursion call stack space, then space complexity is O(1)

-> reverseStack()
For n elements:

    reverseStack(n)
        ↓
    reverseStack(n-1)
        ↓
    ...
    reverseStack(1)

At each level, after the recursive call returns, we call:
    insertAtBottom(st, temp);
And that itself takes O(n) in the worst case.

So the total work is: O(n) + O(n-1) + O(n-2) + ... + O(1)
which is: Time: O(n²)
The recursion depth of reverseStack is O(n), and insertAtBottom also has recursion depth up to O(n).
Auxiliary space: O(n)

The important reason for the O(n²) is that every element we remove, 
requires another traversal down to the bottom to put it back.
*/

void insertAtBottom(stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    
    int temp = st.top();
    st.pop();
    
    insertAtBottom(st, x);
    
    st.push(temp);
}

void reverseStack(stack<int>& st) {
    if (st.empty()) {
        return;
    }
    
    int temp = st.top();
    st.pop();
    
    reverseStack(st);
    
    insertAtBottom(st, temp);
}

int main() {
    // stack<int> st;
    // st.push(1);
    // st.push(2);
    // st.push(3);
    // st.push(4);

    // printStack(st);
    // reverseStack(st);
    // printStack(st);

    return 0;
}