// XOR of numbers in a given range l to r

#include <bits/stdc++.h>
using namespace std;

// XOR of Numbers from 1 to N
/*
Problem Statement
Given an integer n, find the XOR of all integers from 1 to n.
In other words, calculate: 1 ^ 2 ^ 3 ^ ... ^ n
*/

// Naive Approach: Time Complexity : O(n) __ Space Complexity : O(1)
int xorTillNBrute(int n) {
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans ^= i;
    }

    return ans;
}

// Optimal Approach (Observation Based): Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition
Instead of calculating the XOR of every number, we can observe a repeating pattern in the results.
Let's calculate the XOR for the first few values of n:

n	| XOR from 1 to n	              | Result
1	| 1	                              | 1
2	| 1 ^ 2	                          | 3
3	| 1 ^ 2 ^ 3	                      | 0
4	| 1 ^ 2 ^ 3 ^ 4	                  | 4
5	| 1 ^ 2 ^ 3 ^ 4 ^ 5	              | 1
6	| 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6	          | 7
7	| 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6 ^ 7	      | 0
8	| 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6 ^ 7 ^ 8	  | 8

Notice the pattern:
n % 4 = 0  ->  XOR = n
n % 4 = 1  ->  XOR = 1
n % 4 = 2  ->  XOR = n + 1
n % 4 = 3  ->  XOR = 0
The pattern repeats every four numbers.
So, we can simply get the xor value till n by considering the value of n % 4.

>> Complexity Analysis:
- Time Complexity: O(1) — We perform only a modulo operation and a few comparisons.
- Space Complexity: O(1) — No additional space proportional to input size is used.
*/
int xorTillN(int n) {
    int rem = n % 4;

    if (rem == 0) 
        return n;

    else if (rem == 1) 
        return 1;
    
    else if (rem == 2) 
        return n + 1;
    
    else 
        return 0;
}

// XOR of numbers in a given range l to r
/*
GFG - XOR of a Number Range : Easy

Given two integers l and r, find the XOR of elements of the range [l, r].

Examples :-

Input: l = 4, r = 8 __ Output: 8 
Explanation: The value of (4 ^ 5 ^ 6 ^ 7 ^ 8) = 8.

Input: l = 2, r = 4 __ Output: 5
Explanation: The value of (2 ^ 3 ^ 4) = 5.

Input: l = 5, r = 9 __ Output: 5
Explanation: The value of (5 ^ 6 ^ 7 ^ 8 ^ 9) = 5.
 
Constraints :-
• 1 ≤ l, r ≤ 10^9
*/

// Optimal Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
We can use the XOR prefix function we discussed above to calculate the XOR in a given range 
without iterating through every number.

Let xorTillN(n) represent the XOR of all numbers from 1 to n.

We know: 
xorTillN(r) = 1 ^ 2 ^ 3 ^ ... ^ r, and
xorTillN(l-1) = 1 ^ 2 ^ 3 ^ ... ^ l-1
If we XOR these two results, the common elements cancel out, leaving only the XOR from l to r.

Therefore: xorLtoR(l, r) = xorTillN(r) ^ xorTillN(l - 1)

We simply calculate the prefix XOR for r and l-1 using the four-case observation-based approach, 
then XOR the two results to get xor in range l to r.

>> Complexity Analysis:
- Time Complexity: O(1) — Two constant-time prefix XOR calculations and one XOR operation.
- Space Complexity: O(1) — Only a few variables are required.
*/
int findXOR(int l, int r) {
    return xorTillN(l-1) ^ xorTillN(r);
}

int main() {
    return 0;
}