/*
-- Smallest / Least Prime Factor --
The least prime factor of an integer 'n' is the smallest prime number that divides the number. 
For example, the least prime factor of 945 is 3. 
The least prime factor of all even numbers is 2. 
A prime number is its own least prime factor (as well as its own greatest prime factor).

By convention, 1 is given as its own least prime factor.
Each prime number is its own least and greatest prime factor.

Since, the least prime factors of all even integers is 2, thus percentage of integers with lpf = 2 is 50% !!
*/

#include <bits/stdc++.h>
using namespace std;

// The code for Naive Approach is available in 'GFG_LeastPrimeFactor.cpp'

// Sieve of Eratosthenes for Computing SPF : Time Complexity : O(n log log n) __ Space Complexity : O(n)
/*
The Sieve of Eratosthenes can be used to precompute the Smallest Prime Factor (SPF) for all numbers from 1 to n. 
Here's the basic idea behind the algorithm:
Initially, assume that each number is its own smallest prime factor. 
For each prime number p, iterate through all multiples of p and set their smallest prime factor to p. 
This method allows us to compute the SPF for all numbers up to 100,000 efficiently in O(n log log n) time complexity.
*/
/*
To get the smallest/least prime factor of all numbers till n, we use an approach similar to Sieve of Eratosthenes
We know that the lpf of prime number is itself and for composite numbers, their lpf is the least prime factor they have.
So, we can use an approach similar to Sieve of Eratosthenes to mark the least prime factor for all numbers from 2 to n.

- Initialize an array of size n+1 and set all values to their own index (i.e., spf[i] = i)
- For each number i from 2 to √n, if spf[i] == i, this means i is prime
- Mark the multiples of such i, like we did to get prime sieve, but here we mark the multiples to have their lpf set to i
- It is possible that some multiple of i has been already marked by some previous prime number,
  ex- 12 would have been marked by 2 and then is also a multiple of 3 as well, so we won't mark it for 3 since 12's lpf is 2.
  We can use the if condition (spf[j] == j) or (spf[j] > i), to check for such numbers which have been already marked.
- Return the spf/lpf array as the answer where spf[i] tells us the smallest prime factor of i.

>> Complexity Analysis :-

-> Time Complexity : O(n log log n) => The approach works similar to Sieve of Eratosthenes and have same time complexity
-> Space Complexity :
Since, the current problem needs an array holding lpf of all numbers from 0 to n, so the spf array can be returned 
and thus we can avoid considering it as extra space, but if the problem had been somewhat different like 
'printing lpf of numbers from 0 to n', then this array would be considered as an extra space.
This is also similar to how the space complexity of Sieve of Eratosthenes is O(n)
*/

vector<int> leastPrimeFactor(int n) {
    vector<int> spf(n+1);
    
    for (int i = 0; i <= n; i++)
        spf[i] = i;
        
    
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                // we must mark lpf of only those multiples which haven't been marked earlier by any smaller primes
                // so we use the if condition if (spf[j] == j), or, if (spf[j] > i) to mark only unmarked multiples 
                if (spf[j] > i) {
                    spf[j] = i;
                }
            }
        }
    }
    
    return spf;
}

// Use of Smallest / Least Prime Factor (spf/lpf)
/*
1. Check number is prime

    we know that the spf of a prime number is itself. 
    So, to check x is prime or not
    if (spf[x] == x), this means x is prime

2. Check number is semi-prime

    semi-prime: Product of two prime numbers (may be both are equal) Example: 25=5*5, 4=2*2, 77=7*11, 6 = 2*3

    A number is semi-prime, if it has only two prime factors.
    In that case, to check a number 'n' is semi-prime, we firstly find the spf of current number (say spf[n] = x), 
    then we find n / x to find the factor pair of x. let n / x = y.
    Now, n will be a semi-prime, only if both x and y are primes.

    int n;
    cin >> n;
    int x = spf[n];
    int y = n / x;
    if (spf[x] == x && spf[y] == y)
        cout << "Given number is semi-prime";

3. Finding the Prime Factorization of a Number

    int n;
    cin >> n;
    int x = n;
    while (x!=1) {
        cout << spf[x] << " ";
        x = x / spf[x];
    }

4. Check two numbers are co-primes

    To check a & b are co-primes
    get prime factorization of numbers a & b using spf and store them in two vectors v1 & v2
    a & b are co-primes if they don't share any common factor other than 1, 
    so the two prime factorization vectors must not have any common value
    By checking for this, we can determine whether a & b are co-primes or not

    We can also check for co-primes by checking gcd(a, b) == 1
*/ 

int main() {
    return 0;
}