/*
Leetcode - 50. Pow(x, n) : Medium

Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

Examples :-

Input: x = 2.00000, n = 10
Output: 1024.00000

Input: x = 2.10000, n = 3
Output: 9.26100

Input: x = 2.00000, n = -2
Output: 0.25000
 
Constraints :-
• -100.0 < x < 100.0
• -2^31 <= n <= 2^31-1
• n is an integer.
• Either x is not zero or n > 0.
• -10^4 <= xn <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

double myPow(double x, int n) {
    if (n == 0) return 1;
    
    // for cases when n == INT_MIN, doing abs(n) will make n value overflow int, so we use long long variable to store n
    long long N = n;
    bool isNegative = false;

    if (N < 0) {
        N = -N;
        isNegative = true;
    }

    double ans = 1;
        
    while (N > 0) {
        if (N % 2 == 1) {
            ans *= x;
            N--;
        }
        else {
            x = x * x;
            N /= 2;
        }
    }

    if (isNegative) ans = 1.0/ans;

    return ans;
}

int main() {
    return 0;
}