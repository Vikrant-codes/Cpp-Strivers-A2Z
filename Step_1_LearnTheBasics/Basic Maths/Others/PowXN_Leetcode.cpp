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

// Time Complexity : O(log n)
double myPow1(double x, int n) {
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

// Recursive Solution
double myPow(double x, int n) {
    if (n == 0) return 1;

    long long N = n;
    bool isNegative = (n < 0) ? true : false;
    if (isNegative) N = -N;

    double ans = 1;

    if (N % 2 == 1)
        ans = x * myPow(x * x, N / 2);
    else 
        ans = myPow(x * x, N / 2);
    
    if (isNegative) ans = 1.0/ans;
    return ans;
}

// Better code for recursive approach
/*
The problem with above recursive solution is that it is handling the negative n case for all the recursive calls as well.
If n is negative, then it would be turned positive and for all the recursive calls, it will remain positive,
so the execution of handling -ve logic for all those recursive calls is unncessary work.

This is optimised here in the below approach,
here we are using a helper method power(x, n), which works assuming n is a positive integer.
If n is negative, myPow makes x = 1/x, 
so that multiplying x would then be equivalent to dividing by x (core idea of -ve power).
Also, it makes n positive and then calls the power(x, n).
Since x value has been turned to x = 1/x... multiplying by x inside power would be equivalent to dividing by x.
*/
double power(double x, int n) {
    if (n == 0)
        return 1;

    if (n % 2 == 0) 
        return power(x * x, n / 2);
    
    return x * power(x * x, n / 2);
}

double myPowEff(double x, int n) {
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