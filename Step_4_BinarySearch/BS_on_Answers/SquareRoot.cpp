// Binary Search is used on answers when we need to find the maximum or minimum value that satisfies a certain condition.

/*
GFG - Square Root : Easy

Given a positive integer n, find the square root of n. If n is not a perfect square, then return the floor value.
Floor value of any number is the greatest Integer which is less than or equal to that number.

Examples :-

Input: n = 4 __ Output: 2
Explanation: Since, 4 is a perfect square, so its square root is 2.

Input: n = 11 __ Output: 3
Explanation: Since, 11 is not a perfect square, floor of square root of 11 is 3.

Constraints :- 1 ≤ n ≤ 3*104
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach :- Time Complexity : O(log n) __ Space Complexity : O(1)
// Use Binary Search to check for the greatest number x such that x^2 <= n.
int floorSqrt(int n) {
    int low = 0;
    int high = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int val = mid * mid;
        if (val == n) return mid;
        if (val < n) low = mid + 1;
        else high = mid - 1;
    }
    return high;
}

// Leetcode Problem Solution
/*
Leetcode - 69. Sqrt(x) -- Easy
Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
You must not use any built-in exponent function or operator. For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.

Examples :-
Input: x = 4 __ Output: 2
Explanation: The square root of 4 is 2, so we return 2.

Input: x = 8 __ Output: 2
Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.
 

Constraints :- 0 <= x <= 2^31 - 1
*/
int mySqrt(int x) {
    if (x == 0 || x == 1) return x;
    int low = 1, high = x;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long val = 1LL * mid * mid;
        if (val == x) return mid;
        if (val < x) low = mid + 1;
        else high = mid - 1;
    }
    return high;
}

int main() {
    int n = 10000;
    int x = floorSqrt(n);
    cout << "Sqrt of " << n << " is : " << x << endl;

    return 0;
}