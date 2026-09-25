/*
>> Factorial 

The factorial of a non-negative integer n is the product of all positive integers less than or equal to n.
It is denoted by `n!`.

The factorial of n also equals the product of n with the next smaller factorial, i.e., n! = n x (n-1)!

n! = n x (n-1) x (n-2) x (n-3) x ... x 3 x 2 x 1

   = { 1 ,               if n = 0
     { n x (n - 1)! ,    if n >= 1

For example, 5! = 5 x 4! = 5 x 4 x 3 x 2 x 1 = 120.

The value of 0! is 1, according to the convention for an empty product.

empty product: In mathematics, an empty product, or nullary product or vacuous product, 
    is the result of multiplying no factors. 
    It is by convention equal to the multiplicative identity, 
    just as the empty sum — the result of adding no numbers — is by convention equal to the additive identity (zero).

Factorials are not defined for negative numbers.

The factorial operation is encountered in many areas of mathematics, notably in combinatorics, 
where its most basic use counts the possible distinct sequences – the permutations – of n distinct objects: there are n!

Many other notable functions and number sequences are closely related to the factorials, 
including the binomial coefficients, double factorials, falling factorials, primorials, and subfactorials.
*/

#include<bits/stdc++.h>
using namespace std;

/*
GFG - Factorial : Basic

Given a positive integer, n. Find the factorial of n.

Examples :-

Input: n = 5 __ Output: 120
Explanation: 1 x 2 x 3 x 4 x 5 = 120

Input: n = 4 __ Output: 24
Explanation: 1 x 2 x 3 x 4 = 24

Constraints :-
• 0 ≤ n ≤ 12
*/

// Recursive Implementation: Time Complexity : O(n) __ Space Complexity : O(n), this is the recursive stack space
int factorial(int n) {
    if (n == 0)
        return 1;
        
    return n * factorial(n - 1);
}

// Iterative Implementation: Time Complexity : O(n) __ Space Complexity : O(1)
int factorialIterative(int n) {
    int ans = 1;
    
    while (n) {
        ans *= n;
        n--;
    } 
        
    return ans;
}

int main() {
    return 0;
}