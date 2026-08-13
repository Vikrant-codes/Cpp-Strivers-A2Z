// Sort a Stack
/*
Problem Statement: 
You are given a stack of integers. 
Your task is to sort the stack in descending order using recursion, 
such that the top of the stack contains the greatest element. 
You are not allowed to use any loop-based sorting methods (e.g., quicksort, mergesort). 
You may only use recursive operations and the standard stack operations (push, pop, peek/top, and isEmpty).
*/

// GFG - Sort a stack : Medium
/*
GFG - Sort a stack : Medium

Given a stack of integers st[]. 
Sort the stack in ascending order (smallest element at the bottom and largest at the top).

Examples :-

Input: st[] = [41, 3, 32, 2, 11]
Output: [41, 32, 11, 3, 2]
Explanation: After sorting, the smallest element (2) is at the bottom and the largest element (41) is at the top.

Input: st[] = [3, 2, 1]
Output: [3, 2, 1]
Explanation: The stack is already sorted in ascending order.

Constraints :-
• 1 ≤ st.size() ≤ 10^3
• 0 ≤ stack element ≤ 10^3 
*/

#include<bits/stdc++.h>
using namespace std;

/*
The most straight forward and optimal way to sort a stack is to firstly store its elements in an auxiliary array/vector.
then, we can sort this auxiliary vector to get the elements in sorted order, 
and then push these elements back to the stack.
This way, the stack can be efficiently sorted in O(n log n) or O(n^2) time depending on what sorting algo. we use.
*/
// Using an auxiliary vector: Time Complexity : O(n log n) __ Space Complexity : O(n)
void sortStackTempArray(stack<int> &st) {
    vector<int> temp;
    
    while(!st.empty()) {
        temp.push_back(st.top());
        st.pop();
    }
    
    sort(temp.begin(), temp.end());
    
    for (int x : temp)
        st.push(x);
}

// Recursive Approach : Time Complexity : O(n²) __ Space Complexity : O(n)
/*
We use recursion to sort the stack without relying on extra data structures
The approach will be:
• Remove the top element of the stack.
• Recursively sort the remaining stack.
• Insert the removed element back into the stack in its correct sorted position.

>> How Recursion Works
1. Remove the top element of the stack and hold it temporarily.
2. Recursively sort the remaining stack, which is now smaller (it has one fewer element).
3. Once the smaller stack is sorted, insert the held element back into its correct position:
   If the stack is empty or the top element is smaller than the held element, push it directly.
   Otherwise, remove the top element, recursively find the correct position for the held element, 
   and then push back the removed element.
4. Repeat this process as recursion unwinds until all elements are sorted in ascending order, 
   with the smallest at the bottom and the largest at the top.


>> Time Complexity: O(n²)
O(n²) as each element is popped and inserted at its correct position in the sorted stack.
This insertion at correct position could be O(n) in worst case, for each element.
So, total time : O(n²)

>> Auxiliary Space: O(n), due to call stack.
*/

// helper method: inserts an element `x` at its correct position in a sorted stack
void insert(stack<int>& st, int x) {
    // Base case: if the stack is empty or `x` is larger than the top element
    if (st.empty() || st.top() <= x) {
        st.push(x);
        return;
    }
    
    // pop the top element and recursively insert
    int top = st.top();
    st.pop();
    
    insert(st, x);
    
    // push the popped element back
    st.push(top);
}

void sortStack(stack<int>& st) {
    if (st.empty()) 
        return;
        
    int top = st.top();
    st.pop();
    
    sortStack(st);
    
    insert(st, top);
}

int main() {
    return 0;
}