/*
Permutations — Find nPr

Problem statement

Given two integers n and r, calculate the number of ways to select and arrange r objects from n distinct objects, 
where repetition is not allowed and order matters.

The mathematical formula for calculating permutations is: nPr = n! / (n - r)!

For example, if n = 5 and r = 3:
5P3 = 5! / (5-3)! = 5! / 2! = 60
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Approach 1 — Calculate both factorials separately

We can directly implement the mathematical formula.
1. Calculate n!.
2. Calculate (n-r)!.
3. Divide n! by (n-r)!.

>> Complexity Analysis
- Time Complexity: O(n) — Calculating n! takes O(n), while calculating (n-r)! takes O(n-r). Overall, O(n).
- Auxiliary Space: O(1).
*/
long long factorial(int n) {
    long long fact = 1;

    for(int i = 2; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

long long findnPr(int n, int r) {
    if (r > n) 
        return 0;

    long long numerator = factorial(n);
    long long denominator = factorial(n - r);

    return numerator / denominator;
}

/*
>> Approach 2 — Simplify the mathematical formula

We can optimize the previous approach by observing that we don't actually need to calculate both factorials.
Let's expand the numerator:

nPr = n! / (n - r)!

Expanding n!: 
nPr = { n × (n - 1) × (n - 2) × ... × (n - r + 1) × (n - r)! } / (n - r)!

Now, we can cancel out the common (n - r)! from numerator and denominator.

We are left with: nPr = n × (n - 1) × (n - 2) × ... × (n - r + 1)

So, instead of calculating two factorials, we only need to perform r multiplications.

>> Complexity Analysis
- Time Complexity: O(r) — We perform exactly r multiplications.
- Auxiliary Space: O(1).
*/
long long nPr(int n, int r) {
    if(r > n) return 0;

    long long ans = 1;

    for(int i = 0; i < r; i++) {
        ans *= (n - i);
    }

    return ans;
}

int main() {
    return 0;
}