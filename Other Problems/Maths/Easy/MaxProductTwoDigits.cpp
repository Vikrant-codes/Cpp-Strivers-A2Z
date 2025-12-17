/*
Leetcode - 3536. Maximum Product of Two Digits : Easy

You are given a positive integer n.
Return the maximum product of any two digits in n.
Note: You may use the same digit twice if it appears more than once in n.

Examples :-

Input: n = 31 __ Output: 3
Explanation:
The digits of n are [3, 1].
The possible products of any two digits are: 3 * 1 = 3.
The maximum product is 3.

Input: n = 22 __ Output: 4
Explanation:
The digits of n are [2, 2].
The possible products of any two digits are: 2 * 2 = 4.
The maximum product is 4.

Input: n = 124 __ Output: 8
Explanation:
The digits of n are [1, 2, 4].
The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
The maximum product is 8.

Constraints : 10 <= n <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

/*
To find the maximum product of any digits of 'n', we just need to find the two maximum digits of 'n'.
So, we extract digits from n and find the two maximum digits and return their product.
*/
int maxProduct(int n) {
    int n1 = 0, n2 = 0;
    while (n != 0) {
        int dig = n % 10; 
        if (dig > n1) {
            n2 = n1;
            n1 = dig;
        }
        else if (dig > n2) {
            n2 = dig;
        }
        n = n / 10;
    }
    return n1 * n2;
}

int main() {
    return 0;
}