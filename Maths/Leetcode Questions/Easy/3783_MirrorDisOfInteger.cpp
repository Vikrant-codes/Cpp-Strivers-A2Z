/*
Leetcode - 3783. Mirror Distance of an Integer : Easy

You are given an integer n.
Define its mirror distance as: abs(n - reverse(n))​​​​​​​ where reverse(n) is the integer formed by reversing the digits of n.
Return an integer denoting the mirror distance of n​​​​​​​.
abs(x) denotes the absolute value of x.

Examples :-

Input: n = 25 __ Output: 27
Explanation: reverse(25) = 52.
Thus, the answer is abs(25 - 52) = 27.

Input: n = 10 __ Output: 9
Explanation: reverse(10) = 01 which is 1.
Thus, the answer is abs(10 - 1) = 9.

Input: n = 7 __ Output: 0
Explanation: reverse(7) = 7.
Thus, the answer is abs(7 - 7) = 0.

Constraints: 1 <= n <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

int reverse(int n) {
    int rev = 0;
    while (n) {
        rev = rev * 10 + (n % 10);
        n = n / 10;
    }
    return rev;
}

int mirrorDistance(int n) {
    return abs(n - reverse(n));
}

int main() {
    return 0;
}