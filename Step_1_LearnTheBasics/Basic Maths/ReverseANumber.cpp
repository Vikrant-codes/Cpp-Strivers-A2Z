/*
GFG - Reverse digits : Basic

You are given an integer n. Your task is to reverse the digits, ensuring that the reversed number has no leading zeroes.

Examples :-

Input: n = 122 __ Output: 221
Input : n = 200 __ Output: 2
Input : n = 12345 __ Output: 54321

Constraints :- 1 <= n <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

int reverseNumber(int n) {
    int rev = 0;

    while (n > 0) {
        int lastDig = n % 10;
        rev = rev * 10 + lastDig;
        n /= 10;
    }

    return rev;
}

int main() {
    return 0;
}