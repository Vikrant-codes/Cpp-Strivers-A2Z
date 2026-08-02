/*
GFG - Power Using Recursion : Basic

You are given two numbers n and p. You need to find n^p.

Examples :-

Input: n = 9, p = 9 __ Output: 387420489
Explanation: 9 raised to power 9 is 387420489.

Input: n = 2, p = 9 __ Output: 512
Explanation: 2 raised to power 9 is 512.

Constraints :-
• 1 ≤ n ≤ 10
• 0 ≤  p ≤ 9
*/

#include <bits/stdc++.h>
using namespace std;

// Approach : multiply n by itself p times to get n ^ p. 
// Time Complexity : O(p) __ Space Complexity : O(p)

// Using Parameterized Recursion 
/*
>> How it works
- ans carries the accumulated result.
- Each recursive call multiplies ans by n.
- When p becomes 0, the accumulated answer is returned.

Example: 2^4
    helper(1,2,4)
    → helper(2,2,3)
    → helper(4,2,2)
    → helper(8,2,1)
    → helper(16,2,0)
    → 16
*/
int helper(int ans, int n, int p) {
    if (p == 0) return ans;
    
    return helper(ans*n, n, p-1);
}

int recursivePower1(int n, int p) {
    return helper(1, n, p);
}

// Using Functional Recursion
/*
>> How it works
Here, each function returns the answer for its subproblem.
Example: 2^4
    recursivePower(2,4)
    = 2 * recursivePower(2,3)
    = 2 * (2 * recursivePower(2,2))
    = 2 * (2 * (2 * recursivePower(2,1)))
    = 2 * (2 * (2 * (2 * recursivePower(2,0))))
    = 2 * (2 * (2 * (2 * 1)))
    = 16
*/
int recursivePower(int n, int p) {
    if (p == 0) return 1;
    
    return n * recursivePower(n, p - 1);
}

int main() {
    return 0;
}