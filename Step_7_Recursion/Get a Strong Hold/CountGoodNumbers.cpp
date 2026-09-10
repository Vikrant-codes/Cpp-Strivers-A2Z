/*
Leetcode - 1922. Count Good Numbers : Medium

A digit string is good if the digits (0-indexed) at even indices are even and 
the digits at odd indices are prime (2, 3, 5, or 7).

For example, "2582" is good because the digits (2 and 8) at even positions are even 
and the digits (5 and 2) at odd positions are prime. 
However, "3245" is not good because 3 is at an even index but is not even.

Given an integer n, return the total number of good digit strings of length n. 
Since the answer may be large, return it modulo 10^9 + 7.

A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.

Examples :-

Input: n = 1 __ Output: 5
Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

Input: n = 4 __ Output: 400

Input: n = 50 __ Output: 564908303

Constraints :-
• 1 <= n <= 10^15
*/

#include<bits/stdc++.h>
using namespace std;

//* A2Z sheet article's solution

const int MOD = 1e9 + 7;

// Recursive function to count good numbers
int countGoodNumbers(int index, int n) {
    // Base case: if we've reached the end of the string
    if (index == n) {
        // Return 1 as we've formed a valid string
        return 1; 
    }

    int result = 0;
    // Even index: Use even digits
    if (index % 2 == 0) {  
        // Even digits: 0, 2, 4, 6, 8
        for (int digit : {0, 2, 4, 6, 8}) {
            result = (result + countGoodNumbers(index + 1, n)) % MOD;
        }
    } 
    // Odd index: Use prime digits
    else {  
        // Prime digits: 2, 3, 5, 7
        for (int digit : {2, 3, 5, 7}) {
            result = (result + countGoodNumbers(index + 1, n)) % MOD;
        }
    }
    return result;
}

int main() {
    return 0;
}