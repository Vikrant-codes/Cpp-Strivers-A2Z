/*
Leetcode - 2220. Minimum Bit Flips to Convert Number : Easy

A bit flip of a number x is choosing a bit in the binary representation of x 
and flipping it from either 0 to 1 or 1 to 0.

For example, for x = 7, the binary representation is 111 and we may choose any bit 
(including any leading zeros not shown) and flip it. 
We can flip the first bit from the right to get 110, 
flip the second bit from the right to get 101, 
flip the fifth bit from the right (a leading zero) to get 10111, etc.

Given two integers start and goal, return the minimum number of bit flips to convert start to goal.

Examples :-

Input: start = 10, goal = 7 __ Output: 3
Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
- Flip the first bit from the right: 1010 -> 1011.
- Flip the third bit from the right: 1011 -> 1111.
- Flip the fourth bit from the right: 1111 -> 0111.
It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.

Input: start = 3, goal = 4 __ Output: 3
Explanation: The binary representation of 3 and 4 are 011 and 100 respectively. We can convert 3 to 4 in 3 steps:
- Flip the first bit from the right: 011 -> 010.
- Flip the second bit from the right: 010 -> 000.
- Flip the third bit from the right: 000 -> 100.
It can be shown we cannot convert 3 to 4 in less than 3 steps. Hence, we return 3.

Constraints :-
• 0 <= start, goal <= 10^9

Note: This question is the same as 461: Hamming Distance.
*/

/*
Leetcode - 461. Hamming Distance : Easy

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, return the Hamming distance between them.

Examples :-

Input: x = 1, y = 4 __ Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.

Input: x = 3, y = 1 __ Output: 1

Constraints :-
• 0 <= x, y <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition

To find the minimum bit flips needed to convert start into goal, 
we need to count how many bit positions differ between their binary representations. 
Each differing bit requires exactly one flip.

First, convert both integers into 32-bit binary strings of length 32. 
Since both strings have equal lengths, we don't need to make them equal-sized later.

Then, compare the two strings bit by bit and count the positions where the bits differ. 
Return this count, as it represents the number of bit flips needed to make both integers equal.

This is also the Hamming distance between the two binary representations.

>> Complexity Analysis:
- Time: O(1) — Both strings have a fixed length of 32 bits.
- Space: O(1) — Two fixed-length binary strings are used.
*/
string convert2Binary(int n) {
    string s = "";

    for(int i = 0; i < 32; i++) {
        if (n & 1) s += '1';
        else s += '0';
    
        n >>= 1;
    }

    reverse(s.begin(), s.end());
    
    return s;
}

int minBitFlips(int start, int goal) {
    string s1 = convert2Binary(start);
    string s2 = convert2Binary(goal);
    
    int cnt = 0;
    
    for (int i = 0; i < 32; i++)
        if (s1[i] != s2[i])
            cnt++;
    
    return cnt;
}

// Optimal Approach (XOR + Brian Kernighan's Algorithm): Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition

We need to count the differing bits between the two integers. 
Instead of generating their binary string representations and comparing them, we can use the XOR (^) operator.

XOR gives 1 when the corresponding bits of the two operands differ and 0 when they are the same. 
So, XORing the two integers produces a number whose set bits represent the positions where their bits differ.

Example:
    x =  10 = 1010
    y =   7 = 0111
    x ^ y   = 1101

Here, the XOR result has three set bits, meaning there are three differing bit positions. 
Therefore, the Hamming Distance is 3.

We can simply take the XOR of the two integers and count the set bits in the result. 
This can be done using the built-in method (__builtin_popcount() in C++), 
or using Brian Kernighan's algorithm, which repeatedly removes the rightmost set bit using n & (n - 1) until n becomes zero.

The count of set bits in a number is called its Hamming Weight, 
while the count of differing positions between two binary strings is called their Hamming Distance. 
In general, Hamming Distance applies to strings of equal length.

Complexity Analysis:
- Time: O(k), where k is the number of set bits in x ^ y using Brian Kernighan's algorithm.
- Space: O(1) — Only a constant amount of extra space is used.
*/
// hamming weight = count of set bits in a number (Brian Kernighan's Algorithm)
int hammingWeight(int n) {
    int cnt = 0;

    while (n) {
        n = n & (n - 1);
        cnt++;
    }
    
    return cnt;
}

// hamming distance = count of differing bits between two numbers (or, in general, differing positions between two strings)
int hammingDistance(int x, int y) {
    int xr = x ^ y;

    return hammingWeight(xr);
    // return __builtin_popcount(x);
}

int main() {
    return 0;
}