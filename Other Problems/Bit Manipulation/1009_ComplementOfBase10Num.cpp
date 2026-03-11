/*
Leetcode - 1009. Complement of Base 10 Integer : Easy

Note: This question is the same as "Leetcode - 476. Number Complement"

The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its 
binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer n, return its complement.

Examples :-
Input: n = 5 __ Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

Input: n = 7 __ Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

Input: n = 10 __ Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.

Constraints :-
- 0 <= n < 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Find the 'mask' number which have all bits set to '1', complement = mask ^ n ... or complement = mask - n.
int bitwiseComplement(int n) {
    if (n == 0) return 1;

    int noBits = log2(n) + 1;
    int mask = pow(2, noBits) - 1;

    return mask - n;            // mask ^ n  =  mask - n
}

int main() {
    return 0;
}