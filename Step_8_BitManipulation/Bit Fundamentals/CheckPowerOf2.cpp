/*
Leetcode - 231. Power of Two : Easy

Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2^x.

Examples :-

Input: n = 1 __ Output: true
Explanation: 2^0 = 1

Input: n = 16 __ Output: true
Explanation: 2^4 = 16

Input: n = 3 __ Output: false

Constraints :-
• -2^31 <= n <= 2^31 - 1

Follow up: Could you solve it without loops/recursion?
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach (Repeatedly divide by 2): Time Complexity : O(log₂ n) __ Space Complexity : O(1)
/*
Naive Approach: Repeatedly Divide by 2 — Intuition

A power of two can be repeatedly divided by 2 until it becomes 1, without ever leaving a remainder. 
For example, 16 → 8 → 4 → 2 → 1.
A power of two can be repeatedly divided by 2 until it becomes 1, without ever leaving a remainder. For example, \(16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1\).

So, to check whether a number is a power of 2, we can repeatedly divide it by 2 as long as it is completely divisible. 
Then, we check if the number has reached 1 (it is then a power of two); otherwise, it is not a power of 2.

>> Complexity Analysis:
- Time: O(log₂ n) — Each division by 2 reduces the number by half, requiring at most O(log₂ n) iterations.
- Space: O(1) — Only a constant number of variables are used.
*/
bool isPowerOfTwoNaive(int n) {
    if (n <= 0) return false;

    while (n % 2 == 0) {
        n = n / 2;
    }

    return n == 1;
}

// Better Approach (Count set bits)
/*
Count the number of set bits (1s) in the binary representation of n.

A power of two always has exactly one set bit, because it can be represented as a single power of two. 
For example, 8 = 2^3 = (1000)₂, which contains only one set bit.

Therefore, n is a power of two if it is positive and its binary representation contains exactly one set bit.

Complexity Analysis:
- Time: O(log₂ n) / O(k) — Depends on how we implement the count of set bits logic.
- Space: O(1) — Only a counter is needed.
*/

// Time Complexity : O(log₂ n)
bool isPowerOfTwo1(int n) {
    if (n <= 0) return false;
    
    int cnt = 0;

    while (n) {
        cnt += (n & 1);
        n >>= 1;
    }

    return cnt == 1;
}

// Brian Kernighan's algorithm for getting count of set bits - Time Complexity : O(k)
int countSetBits(int n) {
    int cnt = 0;

    while (n) {
        cnt++;
        n = n & (n - 1);
    }

    return cnt;
}

bool isPowerOfTwo2(int n) {
    if (n <= 0) return false;

    return countSetBits(n) == 1;
}

// Optimal Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
We know that the binary representation of a power of 2 contains only one set bit (1), 
while all the remaining bits are 0.

So, if we try to unset the rightmost set bit using n = n & (n - 1), 
n would become zero if it is a power of 2. 
Otherwise, some set bits would remain, and the result would be non-zero.

Examples - 
1.  n = 8 = (1000)₂
    n - 1 = 7 = (0111)₂
    (1000)₂ & (0111)₂ = (0000)₂
    Result is 0 → Power of two.

2.  n = 13 = (1101)₂
    n - 1 = 12 = (1100)₂
    (1101)₂ & (1100)₂ = (1100)₂
    Result is non-zero → Not a power of two.

Therefore, for n > 0, if (n & (n - 1)) == 0, then n is a power of two.
*/
bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    
    return (n & n-1) == 0;
}

int main() {
    return 0;
}