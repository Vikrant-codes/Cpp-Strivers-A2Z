/*
Leetcode - 202. Happy Number : Easy

Write an algorithm to determine if a number n is happy.
A happy number is a number defined by the following process:
- Starting with any positive integer, replace the number by the sum of the squares of its digits.
- Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
- Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

Examples :-

Input: n = 19 __ Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

Input: n = 2 __ Output: false

Constraints :-
- 1 <= n <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

int getDigitSqSum(int x) {
    int sum = 0;
    while (x) {
        int dig = x % 10;
        sum += dig * dig;
        x /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    while (n >= 10) {
        n = getDigitSqSum(n);
    }
    return n == 1 || n == 7;
}

int main() {
    return 0;
}