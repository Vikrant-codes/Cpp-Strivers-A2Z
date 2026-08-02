/*
Leetcode - 50. Pow(x, n) : Medium

Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

Examples :-

Input: x = 2.00000, n = 10 __ Output: 1024.00000

Input: x = 2.10000, n = 3 __ Output: 9.26100

Input: x = 2.00000, n = -2 __ Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

Constraints :-
• -100.0 < x < 100.0
• -2^31 <= n <= 2^31-1
• n is an integer.
• Either x is not zero or n > 0.
• -10^4 <= x^n <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Read: "Maths / Advanced Maths / PowerExponentiation.cpp" to understand the logic behind the approach.

// Recursive Implementation

// helper method: calculates power considering n is +ve
// it uses `n` as long long for the reason that if initially n == INT_MIN, then its absolute value is outside int range.
double power(double x, long long n) {
    if (n == 0)
        return 1;
    
    if (n % 2 == 0) 
        return power(x * x, n / 2);
    
    return x * power(x * x, n / 2);

    /*
    double half = power(x, n / 2);
    
    if (n % 2 == 0) 
        return half * half;
    
    return x * half * half;
    */
}

double myPowRecursive(double x, int n) {
    // if n == INT_MIN, for that case, taking abs(n) will be outside int limits, so we store its absolute value in long long
    long long N = n;

    if (N < 0) {
        x = 1.0 / x;
        N = -N;
    }

    return power(x, N);
}

int main() {
    return 0;
}