/*
Leetcode - 191. Number of 1 Bits : Easy

Given a positive integer n, write a function that returns the number of set bits in its binary representation 
(also known as the Hamming weight).

Examples :-

Input: n = 11 __ Output: 3
Explanation: The input binary string 1011 has a total of three set bits.

Input: n = 128 __ Output: 1
Explanation: The input binary string 10000000 has a total of one set bit.

Input: n = 2147483645 __ Output: 30
Explanation: The input binary string 1111111111111111111111111111101 has a total of thirty set bits.

Constraints :-
• 1 <= n <= 2^31 - 1

Follow up: If this function is called many times, how would you optimize it?
*/

// Hamming weight & Hamming distance
/*
>> Hamming weight

The Hamming weight of a string is the number of symbols that are different from the zero-symbol of the alphabet used. 
It is thus equivalent to the Hamming distance from the all-zero string of the same length. 
For the most typical case, a given set of bits, this is the number of bits set to 1, 
or the digit sum of the binary representation of a given number.

In this binary case, it is also called the population count, popcount, sideways sum, or bit summation.

>> Hamming distance

In information theory, the Hamming distance between two strings or vectors of equal length 
is the number of positions at which the corresponding symbols are different.

In other words, it measures the minimum number of substitutions required to change one string into the other, 
or equivalently, the minimum number of errors that could have transformed one string into the other. 

In a more general context, the Hamming distance is one of several string metrics for 
measuring the edit distance between two sequences. 
It is named after the American mathematician "Richard Hamming".
*/

#include <bits/stdc++.h>
using namespace std;

// Using built-in method
int hammingWeight(int n) {
    return __builtin_popcount(n);
}

// Naive Approach: Time Complexity : O(log₂ n) __ Space Complexity : O(1)
// Extract every bit one by one and manually count the number of set bits (1s) until n becomes zero.
int hammingWeight1(int n) {
    int cnt = 0;

    while (n != 0) {
        if (n % 2 == 1) cnt++;          // if (n & 1) cnt++;

        n /= 2;                         // n /= 2;
    }

    return cnt;
}

int hammingWeight2(int n) {
    int cnt = 0;

    while (n) {
        cnt += (n & 1);
    
        n >>= 1;
    }

    return cnt;
}

// Optimal Approach (Brian Kernighan's algorithm): Time Complexity : O(k) __ Space Complexity : O(1)
/*
>> Brian Kernighan's algorithm

Instead of extracting every bit and manually counting the set bits, 
we can remove the rightmost set bit one by one using `n = n & (n - 1)` until n becomes zero. 
Count the number of times the loop runs, and that gives us the total number of set bits.

>> Complexity Analysis
Time Complexity: O(k), where k is the count of set bits.
*/
int hammingWeight(int n) {
    int cnt = 0;

    while (n) {
        n = n & (n - 1);
        cnt++;
    }
    
    return cnt;
}

/*
| Brian Kernighan's algorithm can be faster than manually extracting and counting every bit 
| because it removes only the set bits (1s).

-----------------------------------------------------------------------------
| Approach	                    | Time complexity  |  Iterations            |
| Manual Extraction & Count	    | O(log n)	       |  Number of bits        |
| Brian Kernighan's Algorithm	| O(k)	           |  Number of set bits    |
-----------------------------------------------------------------------------
Here, k is the number of set bits.

For example, consider n = 128, whose binary representation is 10000000.
- Manual extraction approach: 8 iterations
- Brian Kernighan's: 1 iteration

But if n = 255 (11111111):
- Manual extraction approach: 8 iterations
- Brian Kernighan's: 8 iterations
*/

int main() {
    return 0;
}