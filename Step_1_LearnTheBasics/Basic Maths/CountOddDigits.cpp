/*
TUF - 950. Count number of odd digits in a number

You are given an integer n. You need to return the number of odd digits present in the number.
The number will have no leading zeroes, except when the number is 0 itself.

Examples :-

Input: n = 5 __ Output: 1
Explanation: 5 is an odd digit.

Input: n = 25 __ Output: 1
Explanation: The only odd digit in 25 is 5.

Input: n = 15 __ Output: 2

Constraints :-
• 0 <= n <= 5000
• n will contain no leading zeroes except when it is 0 itself.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(log10(n))
// Extract each digit using `n%10` and increment counter if that digit is odd. Do `n/10` to extract further digits.
int countOddDigit(int n) {
    int cnt = 0;

    while (n) {
        int dig = n % 10;
        if (dig % 2 == 1) 
            cnt++;
    
        n /= 10;
    }

    return cnt;
}

int main() {
    return 0;
}