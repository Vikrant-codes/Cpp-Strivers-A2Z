/*
Leetcode - 1922. Count Good Numbers : Medium

A digit string is good if the digits (0-indexed) at even indices are even and 
the digits at odd indices are prime (2, 3, 5, or 7).

For example, "2582" is good because the digits (2 and 8) at even positions are even 
and the digits (5 and 2) at odd positions are prime. 
However, "3245" is not good because 3 is at an even index but is not even.

Given an integer n, return the total number of good digit strings of length n. 
Since the answer may be large, return it modulo 10^9 + 7.

A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.

Examples :-

Input: n = 1 __ Output: 5
Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

Input: n = 4 __ Output: 400

Input: n = 50 __ Output: 564908303

Constraints :-
• 1 <= n <= 10^15
*/

#include<bits/stdc++.h>
using namespace std;

/*
>> Intuition

For every position in the number, the available choices are independent of the choices made at the other positions.
• At an even index, we can choose one of 0, 2, 4, 6, 8 → 5 choices.
• At an odd index, we can choose one of 2, 3, 5, 7 → 4 choices.

Therefore, the total number of good numbers is obtained by multiplying the number of choices at every position.
For example, for n = 5: 5 × 4 × 5 × 4 × 5
Instead of thinking of this as repeatedly multiplying 5 and 4, we can group the same factors together:
5 × 5 × 5 × 4 × 4
= 5³ × 4²

In general:
answer = 5^( ceil(n/2) ) * 4^(floor (n/2))

Now the problem reduces to calculating two potentially very large powers. 
Since n can be extremely large, calculating them using a simple linear loop would take O(n) time.

We can instead use fast exponentiation, which reduces the exponent by roughly half at every step. 
The key idea is to transform a power like: base^(exp)
into something like: (base^2) ^ (exp/2)
For an odd exponent, we keep one base aside and apply the same idea to the remaining exponent.

This reduces the time required to calculate each power from O(n) to O(log n). 
Since the answer can become extremely large, we perform all calculations modulo 1e9 + 7.

So the overall approach is:
| Count the choices at each position → express the repeated multiplication as powers → 
| calculate those powers using fast exponentiation.

>> Complexity Analysis

We first calculate: 5^(ceil (n/2)) and 4^(floor (n/2)) using fast exponentiation.
Since fast exponentiation halves the exponent at every step, calculating a power takes O(log n) time.
We calculate two such powers, so:
Time Complexity: O(log n) + O(log n) = O(log n)
Space Complexity: O(log n) due to the recursive call stack.

Therefore:
Time:  O(log n)
Space: O(log n)  // recursive implementation
If fast exponentiation were implemented iteratively, the auxiliary space would become O(1).
*/

// Using Recursive implementation of Fast-Exponentiation
int constant = 1e9+7;

int power(long long base, long long exp) {
    if (exp == 0) return 1;

    long long val = base * base;
    val = val % constant;
    
    long long ans;
    
    if (exp % 2 == 0) 
        ans = power(val, exp / 2);
    
    else
        ans = base * power(val, exp / 2);

    return ans % constant;
}

int countGoodNumbers1(long long n) {
    long long x = n / 2, y = n / 2;
    // x is the exponent term corresponding to count of even index positions. power(5, x)
    // y is the exponent term corresponding to count of odd index positions. power(4, y)

    if (n % 2 == 1) x++;
    
    // x = ceil(n / 2), y = floor(n / 2)

    int val1 = power(5, x);
    int val2 = power(4, y);
    
    return (1LL * val1 * val2) % constant;
}

// Other Recursive implementation
const int MOD = 1e9+7;

int findPower(long long a, long long b) {
    if (b == 0) 
        return 1;

    long long half = findPower(a, b/2);
    
    long long result = (half * half) % MOD;
    
    if (b % 2 == 1) 
        result = (result * a) % MOD;
    
    return result;
}

int countGoodNumbers2(long long n) {
    return (1LL * findPower(5, (n+1)/2) * findPower(4, n/2)) % MOD;
}

// ChatGPT's solution / using Standard implementation of fast-exponentiation (Iterative implementation)
long long powerX(long long base, long long exp) {
    long long ans = 1;

    while (exp > 0) {
        if (exp & 1)
            ans = (ans * base) % MOD;

        base = (base * base) % MOD;
        exp /= 2;
    }

    return ans;
}

int countGoodNumbers3(long long n) {
    long long even = (n + 1) / 2;
    long long odd = n / 2;

    return (powerX(5, even) * powerX(4, odd)) % MOD;
}

int main() {
    return 0;
}