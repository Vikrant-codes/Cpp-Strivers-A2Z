/*
TUF - 957. Return the Largest Digit in a Number

You are given an integer n. Return the largest digit present in the number.

Examples :-

Input: n = 25 __ Output: 5
Explanation: The largest digit in 25 is 5.

Input: n = 99 __ Output: 9
Explanation: The largest digit in 99 is 9.

Input: n = 1 __ Output: 1

Constraints :-
• 0 <= n <= 5000
• n will contain no leading zeroes except when it is 0 itself.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(log10(n))
int largestDigit(int n) {
    int ans = 0;

    while (n) {
        ans = max(ans, n % 10);
        n /= 10;
    }
    
    return ans;
}

int main() {
    return 0;
}