/*
Combinations — Calculate nCr

Problem statement

Given two integers n and r, calculate the number of ways to select r objects from n distinct objects.
Order does not matter, and an object cannot be selected more than once.

The mathematical formula for calculating combinations is: nCr = n! / {r! * (n - r)!}

For example, if n = 5 and r = 2:
5C2 = 5! / (2! * 3!) = 10
*/

/*
GFG - nCr : Medium

Given two integers n and r, find the value of the binomial coefficient nCr

A binomial coefficient nCr can be defined as the coefficient of x^r in the expansion of (1 + x)^n 
that gives the number of ways to choose r objects from a set of n objects without considering the order.

The binomial coefficient nCr is calculated as : C(n,r) = n! / r! * (n-r) !

Note: If r is greater than n, return 0. It is guaranteed that the value of nCr will fit within a 32-bit integer.

Examples :-

Input: n = 5, r = 2
Output: 10
Explaination: The value of 5C2 is calculated as 5! / ((5−2)! * 2!) = 5! / (3! * 2!) = 10.

Input: n = 2, r = 4
Output: 0
Explaination: Since r is greater than n, thus 2C4 = 0

Input: n = 5, r = 0
Output: 1
Explaination: The value of 5C0 is calculated as 5! / ((5−0)! * 0!) = 5! / (5! * 0!) = 1.

Constraints :-
• 1 ≤ n ≤ 33
• 0 ≤ r ≤ 33
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Approach 1 — Calculate all three factorials separately

We can directly implement the mathematical formula:
1. Calculate n!.
2. Calculate r!.
3. Calculate (n-r)!.
4. Divide n! by the product of the other two factorials.

>> Complexity Analysis
- Time Complexity: O(n) — We calculate three factorials, with n! being the dominant calculation.
- Auxiliary Space: O(1).
*/
long long factorial(int n) {
    long long fact = 1;

    for(int i = 2; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

long long findnCrNaive(int n, int r) {
    if(r > n) return 0;

    long long numerator = factorial(n);
    long long denominator = factorial(r) * factorial(n - r);

    return numerator / denominator;
}

/*
>> Approach 2 — Cancel out the larger factorial

We can optimize the previous approach by simplifying the formula before calculating the factorials.
The important observation is that we don't need to calculate all three factorials.

Starting with:
nCr = n! / {r! * (n-r)!}
We have two possibilities.

Case 1: When r <= n-r

Expand n! until (n-r)! appears:
nCr = { n × (n - 1) × (n - 2) × ... × (n - r + 1) × (n - r)! } / {r! * (n - r)!}

Cancel (n-r)!:
nCr = { n × (n - 1) × (n - 2) × ... × (n - r + 1) } / r!

Case 2: When r > n-r

Instead, expand n! until r! appears:
nCr = { n × (n - 1) × (n - 2) × ... × (r + 1) × r! } / {r! * (n - r)!}

Cancel r!:
nCr = { n × (n - 1) × (n - 2) × ... × (r + 1) } / (n - r)!

Key observation: We should cancel the larger of r! and (n-r)!, because that leaves fewer multiplications to perform.
We can express both cases using: k = min(r, n-r)

Then:
nCr = n × (n - 1) × (n - 2) × ... × (n - k + 1) } / k!

>> Complexity Analysis
- Time Complexity: O(min(r,n-r)) — We perform that many iterations.
- Auxiliary Space: O(1).
*/

// GFG Problem Solution
int nCr(int n, int r) {
    if (r > n) return 0;
    
    int k = min(r, n - r);
    
    long long ans = 1;
    
    for (int i = 0; i < k; i++) {
        ans = ans * (n - i) / (i + 1);
        // when calculated in this manner, the resultant expression would always be an integer value. 
    }
    
    return (int) ans;
}

int main() {
    return 0;
}