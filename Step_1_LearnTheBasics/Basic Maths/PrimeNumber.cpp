// GFG - Prime Number : Easy
/*
>> Prime Number
A prime number is a natural number greater than 1 that has exactly two factors: 1 and itself.
1 is not a prime number because it has only one factor (1).

- Wikipedia Definition: 
A prime number (or a prime) is a natural number greater than 1 that is not a product of two smaller natural numbers.
*/

/*
GFG - Prime Number : Easy

Given a number n, determine whether it is a prime number or not.
Note: A prime number is a number greater than 1 that has no positive divisors other than 1 and itself.

Examples :-

Input: n = 7 __ Output: true
Input: n = 25 __ Output: false
Input: n = 1 __ Output: false

Constraints:- 1 ≤ n ≤ 10^9
*/

#include <iostream>
using namespace std;

/*
There are two ways we can check whether a number 'n' is prime or not.

1. Count the no. of positive factors 'n' has. A prime number has exactly two factors (1 and 'n' itself).
The number of factors can be counted either in O(n) or O(sqrt(n)) depending on the approach.

2. A prime number 'n' has exactly 2 factors 1 & n itself. 
So, a prime number is only divisible by 1 and itself. 
So, it must not be divisible by any number in the range [2, n-1].
i.e., for a no. 'n' to be prime, it must not have any divisor in the range 2 to n-1.
So, we can just check for divisors in this range and conclude whether the number is prime or not.
While checking for divisibility in the range [2, n-1], this range doesn't exist for n = 1 & 2.
So, we must handle these cases as loop won't run for n = 1 and n = 2.

Again to check for divisors from this range, this can be done in either O(n) or O(sqrt(n)).
*/

// <-- Count factors approach --> 

// Naive Approach : Time Complexity: O(n) __ Space Complexity: O(1)
bool isPrimeNaive(int n) {
    int cnt = 0;
    
    for (int i = 1; i <= n; i++) 
        if (n % i == 0)
            cnt++;
    
    return cnt == 2;
}

// Efficient Approach : Time Complexity: O(sqrt(n)) __ Space Complexity: O(1)
/*
We just need to count all the factors (divisors) of n and check whether the count equals 2. 
We already know how to get all the divisors of a number 'n' in sqrt(n) time.
So, we simply use that approach to count the divisors / factors of n and check if that count equals 2.
*/
bool isPrime(int n) {
    int cnt = 0;
    
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            
            if ( (n / i) != i)
                cnt++;
        }
    }
    
    return cnt == 2;
}

// <-- Check divisibility in range 2 to n-1 (prime no. 'n' must not be divisible by any number from this range) --> 

// Naive Approach : Time Complexity : O(n) __ Space Complexity : O(1)
bool isPrimeNaiveX(int n) {
    if (n < 2) return false;

    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

// Efficient Approach : Time Complexity : O(sqrt(n)) __ Space Complexity : O(1)
bool isPrimeX(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    
    return true;
}

int main() {
    return 0;
}