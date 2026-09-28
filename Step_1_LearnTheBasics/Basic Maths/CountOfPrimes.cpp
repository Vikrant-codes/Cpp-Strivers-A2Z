/*
TUF - 790. Count of Prime Numbers till N

You are given an integer n. You need to find out the number of prime numbers in the range [1, n] (inclusive). 
Return the number of prime numbers in the range.

A prime number is a number which has no divisors except, 1 and itself.

Examples :-

Input: n = 6 __ Output: 3
Explanation: Prime numbers in the range [1, 6] are 2, 3, 5.

Input: n = 10 __ Output: 4
Explanation: Prime numbers in the range [1, 10] are 2, 3, 5, 7.

Input: n = 20 __ Output: 8

Constraints :-
• 2 <= n <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(n √n) __ Space Complexity : O(1)
// Iterate in the range [1, n] and count the primes numbers in the range (using a function to check if a number is prime). 
bool isPrime(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int primeUptoN_Naive(int n) {
    int cnt = 0;

    for (int i = 1; i <= n; i++)
        if (isPrime(i))
            cnt++;

    return cnt;
}

// Optimal Approach : Time Complexity : O(n log log n + n) __ Space Complexity : O(1)
// We can use 'Sieve of Eratosthenes' to build a prime array and efficiently check if a number is prime or not. 
vector<bool> getSieve(int n) {
    vector<bool> isPrime(n+1, true);

    isPrime[0] = false;
    isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return isPrime;
}

int primeUptoN(int n) {
    vector<bool> isPrime = getSieve(n);

    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (isPrime[i])
            cnt++;

    return cnt;
}

int main() {
    return 0;
}