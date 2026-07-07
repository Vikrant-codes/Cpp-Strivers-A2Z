/*
Leetcode - 3754. Concatenate Non-Zero Digits and Multiply by Sum I : Easy

You are given an integer n.

Form a new integer x by concatenating all the non-zero digits of n in their original order. 
If there are no non-zero digits, x = 0.

Let sum be the sum of digits in x.

Return an integer representing the value of x * sum.

Examples :-

Input: n = 10203004 __ Output: 12340
Explanation:
The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
Therefore, the answer is x * sum = 1234 * 10 = 12340.

Input: n = 1000 __ Output: 1
Explanation:
The non-zero digit is 1, so x = 1 and sum = 1.
Therefore, the answer is x * sum = 1 * 1 = 1.

Constraints: 0 <= n <= 10^9
*/

#include<bits/stdc++.h>
using namespace std;

long long sumAndMultiply(int n) {
    int x = 0;
    int mul = 1;
    int sum = 0;

    while (n) {
        int dig = n % 10;

        if (dig != 0) {
            sum += dig;
            x = dig * mul + x;
            mul *= 10;
        }

        n /= 10;
    }
    
    return 1LL * x * sum;
}

int main() {
    return 0;
}