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

// Leetcode Variant
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

// GFG Variant
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
// For the leetcode problem, we are not supposed to use this built-in sqrt function 
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

// Using Mathematical Properties : Time Complexity : O(√n) __ Space Complexity : O(1)
/*
The idea is based on the fact that every perfect square is equal to the sum of the first few consecutive odd numbers. 
Therefore, we repeatedly subtract consecutive odd numbers (1, 3, 5...) from the given number. 
If it becomes exactly 0, the number is a perfect square; otherwise, it is not.

1 + 3 = 4
1 + 3  + 5 = 9
1 + 3 + 5 + 7 = 16
1 + 3 + 5 + 7 + 9 = 25
1 + 3 + 5 + 7 + 9 + 11 = 36 and so on.

- If the given number is negative, return false since negative numbers cannot be perfect squares.
- Initialize the first odd number as 1.
- Repeatedly subtract the current odd number from the given number and increment the odd number by 2.
- Continue this process until the given number becomes 0 or negative.
- If the remaining value is 0, return true; otherwise, return false.
*/
bool isPerfectSquare3(int n) {
    // Negative numbers can't be perfect squares
    if (n < 0) return false;
    // 0 is a perfect square
    if (n == 0) return true;
    
    // Start with the first odd number 1
    int odd = 1;
    // keep subtracting consecutive odd numbers till n becomes 0 or negative
    while (n > 0) {
        n -= odd;
        odd += 2;
    } 
    
    // if n has become 0, it means original value is a perfect square
    return n == 0;
}

// Time Complexity : O(√n) __ Space Complexity : O(1) 
/*
A perfect square is a number that can be written as k × k for some integer k.
So, we only need to try values of i starting from 1 and check whether i × i equals n.
    for (int i = 1; i * i <= n; i++)
We stop when i * i becomes greater than n because after that, the squares will only get larger and can never equal n.

For example, if n = 36:
    1² = 1
    2² = 4
    3² = 9
    4² = 16
    5² = 25
    6² = 36  ✓ Found

If n = 20:
    1² = 1
    2² = 4
    3² = 9
    4² = 16
    5² = 25  (>20) Stop
Since no square matched 20, it isn't a perfect square.

Time Complexity: O(√n), because i only goes up to √n, not all the way to n.
*/
bool isPerfectSquare4(int n) {
    if (n < 0) return false;
    if (n == 0) return true;
    
    for (int i = 1; i * i <= n; i++)
        if (i * i == n) 
            return true;
    
    return false;
}

// Optimal Approach (Using Binary Search) : Time Complexity : O(log n) __ Space Complexity : O(1)
/*
Since, we are not allowed to use the inbuilt sqrt method, we need to think of some other way to check for perfect square.
If a number n is perfect square, then it must be square of an integer number in the range [1, n]
So, we find to find an integer x in range [1, x] such that square of x = n, i.e., x * x == n.
If such an integer exists, we can conclude that n is a perfect square.
So, we can use binary search to find this x in this range.

- Initialize low = 1, high = n
- While low <= high
    - Calculate mid = (low + high)/2
    - Calculate square of mid. Check if that square equals n.
    - If mid * mid == n: We have found the x we have been looking for, which means n is a perfect square
    - Else if mid * mid > n: 
        We need to eliminate the right half since the square of all integers of right half would also be greater than n 
    - Else: 
        We need to eliminate the left half since the square of all integers of left half would also be less than n
- Loop exits when low & high crosses, which means x doesn't exists... So return false

>> Time Complexity ; O(log n)
*/
bool isPerfectSquare(int n) {
    // negative numbers can't be perfect squares
    if (n < 0) 
        return false;
    
    // 0 & 1 are perfect squares
    if (n == 0 || n == 1) 
        return true;

    // Apply binary search in range [1, n] to find a number x such that square of x is n.
    // If such element is found -> n is a perfect square, else n is not a perfect square

    int low = 1, high = n;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long square = 1LL * mid * mid;
        
        if (square == n) 
            return true;
        else if (square > n)
            high = mid - 1;
        else 
            low = mid + 1;
    }

    return false;
}

// Leetcode Solution :- No need to check for conditions like (n < 0) or (n == 0), as constraints guarantee that n >= 1
bool isPerfectSquareLeetcode(int n) {
    int low = 1, high = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long square = 1LL * mid * mid;
    
        if (square == n) 
            return true;

        else if (square > n)
            high = mid - 1;
        
        else 
            low = mid + 1;
    }
    
    return false;
}


int main() {
    return 0;
}