/*
Leetcode - 3658. GCD of Odd and Even Sums : Easy

You are given an integer n. Your task is to compute the GCD (greatest common divisor) of two values:
• sumOdd: the sum of the smallest n positive odd numbers.
• sumEven: the sum of the smallest n positive even numbers.
Return the GCD of sumOdd and sumEven.

Examples :-

Input: n = 4 __ Output: 4
Explanation:
Sum of the first 4 odd numbers sumOdd = 1 + 3 + 5 + 7 = 16
Sum of the first 4 even numbers sumEven = 2 + 4 + 6 + 8 = 20
Hence, GCD(sumOdd, sumEven) = GCD(16, 20) = 4.

Input: n = 5 __ Output: 5
Explanation:
Sum of the first 5 odd numbers sumOdd = 1 + 3 + 5 + 7 + 9 = 25
Sum of the first 5 even numbers sumEven = 2 + 4 + 6 + 8 + 10 = 30
Hence, GCD(sumOdd, sumEven) = GCD(25, 30) = 5.

Constraints :-
• 1 <= n <= 10​​​​​​​00
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O( log Φ (min(a, b)) ) __ Space Complexity : O(1)
/*
sumOdd: the sum of the smallest n positive odd numbers.
sumEven: the sum of the smallest n positive even numbers.

We know sum of first n odd numbers = n * n. (can be derived using AP sum formula)
Similarly, sum of first n even numbers = n * (n + 1), or, n * n + n
                                       = oddsum + n         (since, n * n = oddsum)

We can then calculate their gcd using the built-in gcd function / euclidean algo. for gcd in O(log Φ (min(a, b))) time
where a & b are the two values (sum of first n odd & even numbers)
*/
int gcdOfOddEvenSumsNaive(int n) {
    int oddSum = n*n;
    int evenSum = oddSum + n;

    return gcd(oddSum, evenSum);
}

// Optimal Approach (Mathematical) : Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> This approach uses two mathematical identities/properties of GCD
| GCD(a * x, a * y) = a * GCD(x, y)
| GCD of two consecutive terms is always 1. => GCD(a, a+1) = 1

>> Observations :-
- The two values sumOdd and sumEven are (n * n) and (n * (n + 1))
- We need to find their gcd.
- Notice, that n is a common factor to both the values (since both values contains n * something)
- So, GCD(sumOdd, sumEven) = GCD(n * n, n * (n + 1) ) 
                           = n * GCD(n, n + 1)          ... Using GCD(a*x, a*y) = a * GCD(x, y)
                           = n * 1                      ... since, n & n+1 are consecutive numbers, GCD(n, n+1) = 1
                           = n 
*/
int gcdOfOddEvenSums(int n) {
    return n;
}

int main() {
    return 0;
}