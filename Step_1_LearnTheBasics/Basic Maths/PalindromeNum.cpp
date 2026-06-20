/*
Leetcode - 9. Palindrome Number : Easy
GFG - Palindrome Number : Easy
*/

/*
>> Palindrome Number 
A palindrome number is a positive integer (or zero) that reads the same backward as forward.
It is a number that remains exactly the same when its digits are reversed. 

Negative numbers are generally not considered palindromes because of the presence of the negative sign.

>> Properties & Fun Facts

- Even-digit palindromes: 
    All palindromic numbers with an even number of digits (like 1331 or 4554) are completely divisible by 11.
    
- The 196 algorithm: 
    If you take a non-palindrome number, reverse its digits, and add the two numbers together, 
    you can usually reach a palindrome after a few repetitions. 
    However, mathematicians have not yet found a palindrome for certain numbers like 196, 
    despite testing it millions of times.
*/

#include <bits/stdc++.h>
using namespace std;

// Leetcode Variant
/*
Leetcode - 9. Palindrome Number : Easy
Given an integer x, return true if x is a palindrome, and false otherwise.
* An integer is a palindrome when it reads the same forward and backward.

Examples :-

Input: x = 121 __ Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Input: x = -121 __ Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Input: x = 10 __ Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Constraints:- -2^31 <= x <= 2^31 - 1

Follow up: Could you solve it without converting the integer to a string?
*/

bool isPalindrome(int x) {
    // if number is negative, it cannot be a palindrome
    if (x < 0) 
        return false;

    long long rev = 0;      
    // the reversed number might exceed the range of int for the given constraints, so use long long to store reverse number
    int temp = x;   // store the value of n in temp variable so original number's value is not lost
        
    while (temp) {
        int dig = temp % 10;
        rev = rev * 10 + dig;
        temp /= 10;
    }

    return rev == x;
}

// GFG Variant
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

bool isPalindromeGFG(int n) {
    // if number is negative, make it positive (using n = n * -1 or n = -n)
    if (n < 0) 
        n = -n;
    
    int rev = 0;
    int temp = n;   // store the value of n in temp variable so original number's value is not lost
    
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