/*
Leetcode - 367. Valid Perfect Square : Easy
GFG - Check Perfect Square : Basic
*/

/*
>> Perfect Square

A perfect square is an integer that is the product of an integer multiplied by itself (e.g., 3 * 3 = 9). 
Expressed as n², perfect squares are non-negative, and their square roots are whole numbers. 
The first 10 perfect squares are 1, 4, 9, 16, 25, 36, 49, 64, 81, and 100.

>> Key Properties & Quick Tricks
To quickly identify whether a number is a perfect square, look for these mathematical traits:
→ Unit Digits: Perfect squares always end in 0, 1, 4, 5, 6, or 9.
    Any number ending in 2, 3, 7, or 8 is never a perfect square.
→ Prime Factorization: In the prime factorization of a perfect square, 
    the exponent of every prime factor is always an even number (e.g., 36 = 2² * 3²).
→ Trailing Zeros: A perfect square must end in an even number of zeros (e.g., 100 is a perfect square, but 1000 is not).
→ Digital Root: If you repeatedly sum the digits of a perfect square until you get a single digit, 
    the result will always be 1, 4, 7, or 9.
*/

/*
Leetcode - 367. Valid Perfect Square : Easy

Given a positive integer num, return true if num is a perfect square or false otherwise.

A perfect square is an integer that is the square of an integer. 
In other words, it is the product of some integer with itself.

You must not use any built-in library function, such as sqrt.

Examples :-

Input: num = 16 __ Output: true
Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

Input: num = 14 __ Output: false
Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an integer.

Constraints :-
• 1 <= num <= 2^31 - 1
*/

/*
GFG - Check Perfect Square : Basic

Given a positive integer n, return true if it is a perfect square, otherwise return false. 
A number is called a perfect square if it can be written in the form a × a, where a is an integer.

Examples :-

Input: n = 35 __ Output: false 
Explanation: 35 is not a perfect square.

Input: n = 49 __ Output: true
Explanation: 49 is a perfect square (7 * 7 = 49).

Constraints :-
• 1 ≤ n ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Using inbuilt sqrt() function: Time Complexity : O(1) __ Space Complexity : O(1)

bool isPerfectSquare1(int n) {
    // negative numbers can't be perfect squares
    if (n < 0) return false;
    
    // store the sqrt in integer variable (root), check if root * root equals n
    int root = sqrt(n);
    return (root * root == n);
}

bool isPerfectSquare2(int n) {
    if (n < 0) return false;
    
    // store sqrt in double variable (root), check if the root value is actually a whole number (root == (int) root)
    double root = sqrt(n);
    return (root == (int) root);
}

// For leetcode variant, we are not supposed to use the sqrt function
// Using Binary Search 

int main() {
    return 0;
}