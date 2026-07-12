/*
GFG - Prime Factorization using Sieve : Medium

You are given a positive number N. Using the concept of Sieve, compute its prime factorisation.

Example :-

Input: n = 12246
Output: 2 3 13 157
Explanation: 2*3*13*157 = 12246 = n.

Constraints :- 
• 2 <= n <= 2*10^5
*/

// The problem wants us to find the prime factorization using the concept of Smallest/Least Prime Factor Sieve computation

#include <bits/stdc++.h>
using namespace std;

// SPF Sieve Approach : Time Complexity : O(n log log n) + O(log n) __ Space Complexity : O(n)
/*
The prime factorization of a number can be easily found with the help of Smallest Prime Factor Sieve.
So, we firstly build / pre-compute the smallest prime factor sieve.

When we find the prime factorization of a number 'x', we keep dividing it by the smallest prime factors while reducing x.
Ex- assume x = 280
Divide by 2:- x becomes 140
Divide by 2:- x becomes 70
Divide by 2:- x becomes 35
Now, 35 is not divisible by 2 anymore, so we need to divide it with the next smallest prime factor which can divide it.
Divide by 5:- x becomes 7
Divide by 7:- x becomes 1

We stop at x = 1 and the prime factors we used to divide it are the prime factorization of the number 280 = 2 * 2 * 2 * 5 * 7
When we reached 35, we needed to get the next smallest prime factor which can divide it. 
This is where the Smallest Prime Factor Sieve comes into play.

With the help of SPF Sieve, we can easily get the smallest prime factor which can divide the current 'x'.

So, after pre-computing the sieve, the process of prime factorization becomes
    while (x != 1) {
        factor.push_back(spf[x]);
        x = x / spf[x];
    }
For current x, we know that spf[x] is the smallest prime factor which can divide it. 
So, we push it into the factor array and 
divide x by spf[x] to get the next number for which we need to find the smallest prime factor.

>> Complexity Analysis :-
- O(n log log n) to pre-compute the SPF Sieve
- Once, the spf sieve pre-computation is done, the prime factorization can be found very fast in very limited steps.
  Since, in each step, we are dividing the number by its smallest prime factor, 
  the number of steps will be at most log(n) (in case of prime numbers).

  The worst case would be when all prime factors are two, i.e., when n is a power of 2 ex- 512, 1024 etc
  For n = 1024, prime factorization = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
  For such cases when n is a power of 2, the reduction of n to 1 will takes the most no. of iteartions which is O(log2(n))
- So, after pre-computing spf sieve, the worst case complexity to get the prime factorization will be O(log2(n))

-> Space Complexity : O(n) extra space for the sieve array
*/
vector<int> findPrimeFactors(int n) {
    vector<int> spf(n+1);
    
    for (int i = 0; i <= n; i++) 
        spf[i] = i;
        
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
    
    vector<int> primeFactors;
    
    while (n != 1) {
        primeFactors.push_back(spf[n]);
        
        n = n / spf[n];
    }
    
    return primeFactors;
}

int main() {
    return 0;
}