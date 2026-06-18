/*
GFG - Palindrome Number : Easy

You are given an integer n. Your task is to determine whether it is a palindrome.
A number is considered a palindrome if it reads the same backward as forward, as the number examples "12121" or "555".

Examples :-

Input: n = 555 __ Output: true
Explanation: The number 555 reads the same backward as forward, so it is a palindrome.

Input: n = 123 __ Output: false
Explanation: The number 123 reads differently backward (321), so it is not a palindrome.

Input: n = -121 __ Output: true
Explanation: if number is palindrome, mainly ignore sign.

Constraints :-  -10^9 ≤ n ≤ 10^9
*/

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(int n) {
    // if number is neagative, make it positive (using n = n * -1 or n = -n)
    if (n < 0) 
        n = -n;
    
    int rev = 0;
    int temp = n;   // store the value of n in temp variable so number's value is not lost
    
    while (temp) {
        int dig = temp % 10;
        rev = rev * 10 + dig;
        temp /= 10;
    }
    
    return rev == n;
}

int main() {
    return 0;
}