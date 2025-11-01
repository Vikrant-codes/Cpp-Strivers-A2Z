/*
Leetcode - 1614. Maximum Nesting Depth of the Parentheses : Easy

Given a valid parentheses string s, return the nesting depth of s. 
The nesting depth is the maximum number of nested parentheses.

Examples :-
Input: s = "(1+(2*3)+((8)/4))+1" __ Output: 3
Explanation: Digit 8 is inside of 3 nested parentheses in the string.

Input: s = "(1)+((2))+(((3)))" __ Output: 3
Explanation: Digit 3 is inside of 3 nested parentheses in the string.

Input: s = "()(())((()()))" __ Output: 3

Constraints :- 
- 1 <= s.length <= 100
- s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
- It is guaranteed that parentheses expression s is a VPS.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition 
1. We're interested in measuring how deeply nested the parentheses are at any point in the string.
2. Each opening bracket indicates going deeper into a new level of nesting.
3. Each closing bracket signals returning to the previous level of nesting.
4. By tracking how deep we go at each step, we can monitor the peak nesting level.
5. The deepest level we reach during this traversal is the answer.
*/
int maxDepth(string s) {
    int depth = 0, ans = 0;
    for (char c : s) {
        if (c == '(') depth++;
        else if (c == ')') depth--;
        ans = max(depth, ans);   
    }
    return ans;
}

int main() {
    return 0 ;
}