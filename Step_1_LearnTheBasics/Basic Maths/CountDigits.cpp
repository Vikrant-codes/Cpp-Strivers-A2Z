/*
GFG - Count Digits in a Number : Easy

Given a number n, return the count of digits in this number.

Examples :-

Input: n = 1567 __ Output: 4
Explanation: There are 4 digits in 1567, which are 1, 5, 6 and 7.

Input: n = 99999 __ Output: 5
Explanation: Number of digit in 99999 is 5

Constraints :- 
• 1 ≤ n ≤ 10^9
*/

#include<bits/stdc++.h>
#include<cmath>         // for log10 function
using namespace std;

// Standard Approach :- Time Complexity = O(log10(n)) 
/*
Complexity Analysis :-
We are dividing by 10 in each iteration, and loops ends when n becomes 0. 
Thus the total number of iterations done before n becomes 0 is equal to count of times n can be divided by 10 before it becomes 0.
Let n = 10 ^ k, then n can be divided by 10 exactly k times before it becomes 0.
So, the number of iterations is proportional to k, which is log10(n).   (since n = 10^k => log10(n) = k)
Therefore, the time complexity of this approach is O(log10(n)).
*/
int countDigits(int n) {
    int cnt = 0;
        
    while (n > 0) {
        n /= 10;     // same as n = n/10
        cnt++;
    }
    
    return cnt;
}

// Optimized Approach :- Time Complexity = O(1)
/*
It is a mathematical fact that the number of digits in a positive integer n is given by the formula: digits = floor(log10(n)) + 1
This works because log10(n) gives us the exponent k such that 10^k is the largest power of 10 less than or equal to n.

If we had been asked the count of bits/digits in binary representation of a number, then it would have been log2(n) + 1
Similarly, for octal representation, the count of digits is log8(n) + 1
*/
int cntDigitsX(int n) {
    int cnt = (int) (log10(n) + 1);
    return cnt;
}

int main() {
    return 0;
}