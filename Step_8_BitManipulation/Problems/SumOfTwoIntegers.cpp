/*
Leetcode - 371. Sum of Two Integers : Medium

Given two integers a and b, return the sum of the two integers without using the operators + and -.

Examples :-

Input: a = 1, b = 2 __ Output: 3
Input: a = 2, b = 3 __ Output: 5

Constraints :-
• -1000 <= a, b <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Bit Manipulation Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition – Bit Manipulation

We know that addition in binary involves two operations: calculating the sum of corresponding bits and handling the carry.
We can replicate this process using bitwise operators.

1. Calculate the sum without considering carry:

The XOR (^) operator gives the sum of two bits without considering the carry.

For example:
- 0 ^ 0 = 0
- 0 ^ 1 = 1
- 1 ^ 0 = 1
- 1 ^ 1 = 0
This is exactly how binary addition works when we ignore the carry. 
Therefore, a ^ b gives us the intermediate sum without carry.

2. Calculate the carry:

A carry is generated only when both corresponding bits are 1. The AND (&) operator identifies these positions.

Since the carry belongs to the next higher bit position, we left-shift the result by one (<< 1).

Therefore, (a & b) << 1 gives us the carry.

3. Repeat until there is no carry:

We now have two values:
- a ^ b: Sum without carry.
- (a & b) << 1: Carry generated from the addition.

We repeat the same process using these two values until the carry becomes zero. 
At that point, all carries have been handled, and the remaining value represents the final sum.

>> Complexity Analysis
- Time Complexity: O(1) – For fixed-width integers, the number of iterations is bounded by the number of bits.
- Space Complexity: O(1) – Only a constant amount of extra space is used.
*/
int getSum(int a, int b) {

    while (b != 0) {
        int carry = (a & b) << 1;
    
        a = a ^ b;
        b = carry;
    }

    return a;
}

// Dry Run
/*
Let's take a = 2 and b = 3.

Binary representation:
a = 010
b = 011

-- Iteration 1
carry = (010 & 011) << 1
      = 010 << 1
      = 100

a = 010 ^ 011 = 001
b = 100

-- Iteration 2
carry = (001 & 100) << 1
      = 000

a = 001 ^ 100 = 101
b = 000

Now b == 0, so we stop.
Answer = a = 101 = 5
*/

// Recursive implementation
int getSum(int a, int b) {
    return b == 0 ? a : getSum(a ^ b, (a & b) << 1);
}

int main() {
    return 0;
}