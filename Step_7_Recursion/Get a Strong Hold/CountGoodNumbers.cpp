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

//* A2Z sheet article's solution
// ⚠️ Time Complexity : O( 5 ^ (ceil(n/2)) * 4 ^ (floor(n/2)) ) __ Space Complexity : O(n)

/*
>> Intuition

We try constructing the number one digit at a time using recursion.
At every index, the set of valid digits depends on whether the index is even or odd:
- At an even index, we have 5 possible choices: 0, 2, 4, 6, 8.
- At an odd index, we have 4 possible choices: 2, 3, 5, 7.

So, at each position, we try every valid choice and recursively move to the next index.

For example, for n = 3, the recursion explores:
    index 0 → 5 choices
              ↓
    index 1 → 4 choices
              ↓
    index 2 → 5 choices
              ↓
    index 3 → number formed → return 1

The base case is reached when index == n. At that point, we have successfully constructed a valid number, so we return 1.

The results from all recursive branches are then added together to obtain the total number of good numbers.
In other words, the recursion is essentially exploring all possible combinations:
5 * 4 * 5 * 4 * ...
and counting each valid number once.

>> Why this approach doesn't work for the given constraints
Although this is a good recursive way to understand the problem, 
it is not feasible for the actual constraints of the problem.

At every even index we create 5 recursive calls, and at every odd index we create 4 recursive calls. 
Therefore, the number of recursive calls grows exponentially with n.

The total number of leaf nodes is approximately: 5 ^ (ceil(n/2)) * 4 ^ (floor(n/2))

So the time complexity is exponential: O( 5 ^ (ceil(n/2)) * 4 ^ (floor(n/2)) )
and the recursion depth is: O(n)

Since, given constraint is `1 <= n <= 10^15`, this solution is not feasible at all.
*/

const int MOD = 1e9 + 7;

// Recursive function to count good numbers
int countGoodNumbers(int index, int n) {
    // Base case: if we've reached the end of the string
    if (index == n) {
        // Return 1 as we've formed a valid string
        return 1; 
    }

    int result = 0;
    // Even index: Use even digits
    if (index % 2 == 0) {  
        // Even digits: 0, 2, 4, 6, 8
        for (int digit : {0, 2, 4, 6, 8}) {
            result = (result + countGoodNumbers(index + 1, n)) % MOD;
        }
    } 
    // Odd index: Use prime digits
    else {  
        // Prime digits: 2, 3, 5, 7
        for (int digit : {2, 3, 5, 7}) {
            result = (result + countGoodNumbers(index + 1, n)) % MOD;
        }
    }
    return result;
}

// Optimal Solution : Time Complexity : O(log n) __ Space Complexity : O(log n)
/*
We don't need to generate all the digit strings instead we just need the total count of possible digit strings.

For even indices, we can have 5 choices (5 even numbers which are [0,2,4,6,8])
and for odd indices, we can have 4 choices (4 prime numbers which are [2,3,5,7])

Thus, for digit strings of length `n`, the total count can be calculated using permutation logic, 
by multiplying the possible choices at each index.
Giving us :- 5 * 4 * 5 * 4 * 5 * 4 * .... n times

Thus, the count will be equal to 5 * 4 * 5 * 4 * 5 * 4 * .... n times
This can be written as (5 ^ x) * (4 ^ y),
where x = ceil(n/2), y = floor(n/2) 

Thus, we need to calculate these two exponents and return their product while making sure the answer remains within limits 
by doing modulus with 1e9 + 7.

We use fast-exponentiation to efficiently find the two exponents.
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

int countGoodNumbers(long long n) {
    long long x = n / 2, y = n / 2;
    // x is the exponent term corresponding to count of even index positions. power(5, x)
    // y is the exponent term corresponding to count of odd index positions. power(4, y)

    if (n % 2 == 1) x++;
    
    // x = ceil(n / 2), y = floor(n / 2)

    int val1 = power(5, x);
    int val2 = power(4, y);
    
    return (1LL * val1 * val2) % constant;
}

int main() {
    
    return 0;
}