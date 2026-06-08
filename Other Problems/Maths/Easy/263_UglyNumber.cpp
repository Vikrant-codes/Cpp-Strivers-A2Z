/*
Leetcode - 263. Ugly Number : Easy

An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.
Given an integer n, return true if n is an ugly number.

Examples :-

Input: n = 6 __ Output: true
Explanation: 6 = 2 × 3

Input: n = 1 __ Output: true
Explanation: 1 has no prime factors.

Input: n = 14 __ Output: false
Explanation: 14 is not ugly since it includes the prime factor 7.

Constraints :-
-2^31 <= n <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

bool isUgly(int n) {
    if (n <= 0) return false;

    while (n % 2 == 0)
        n = n / 2;
    while (n % 3 == 0)
        n = n / 3;
    while (n % 5 == 0)
        n = n / 5;

    return n == 1;
}

int main() {
    return 0;
}