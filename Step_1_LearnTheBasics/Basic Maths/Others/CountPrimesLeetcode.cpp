/*
Leetcode - 204. Count Primes : Medium

Given an integer n, return the number of prime numbers that are strictly less than n.

Examples :-

Input: n = 10 __ Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Input: n = 0 __ Output: 0

Input: n = 1 __ Output: 0

Constraints :- 0 <= n <= 5 * 10^6
*/

#include <bits/stdc++.h>
using namespace std;

/*
For the given constraints :- 0 <= n <= 5 * 10^6
The naive approach to loop till and check each number for prime will take O(n * sqrt(n)).
Since, n can be 5 * 10^6, this naive approach will exceed the time limit and is thus inefficient.
So, we need a faster approach to find the count of primes till n.
This is where Sieve of Eratosthenes comes in play.
*/

/*
🔹 Sieve of Eratosthenes – 
It’s called the “Sieve of Eratosthenes” because it was invented by the ancient Greek mathematician Eratosthenes of Cyrene 
(around 240 BC).
The word sieve comes from the physical tool used to separate finer particles from coarser ones 
(like flour from bran, or sand from pebbles).
Similarly, the algorithm “sifts out” the non-primes step by step, leaving only primes behind.

Algorithm & Intuition :- 
Goal: Find/count all prime numbers strictly less than 𝑛

Intuition :-
> A prime is a number with no divisors except 1 and itself.
> If a number 𝑝 is prime, then all multiples of 𝑝 are composite.
> So instead of testing each number individually, we can mark composites in bulk by iterating through primes.

Algorithm :-
> Create an array isPrime[0 … n-1], initialize all as true.
> Mark 0 and 1 as false (they’re not prime).
> For each 𝑝 from 2 to 𝑛 :
>> If isPrime[p] is true (i.e., 𝑝 is prime) : Mark all multiples of 𝑝, starting at 𝑝×𝑝, as non-prime.
> At the end, numbers with isPrime[i] == true are primes.

Que >> Why start at 𝑝×𝑝?
Because any multiple smaller than 𝑝×𝑝 (like 2𝑝, 3𝑝…) would already have been marked by smaller primes.

At the end, numbers with isPrime[i] == true are primes.

Complexity Analysis :-

>> Time Complexity : O(nloglogn) 

🔹 Step 1: What work do we do? 
For each prime 𝑝 ≤ 𝑛, we mark its multiples: 𝑝^2, 𝑝^2 + 𝑝, 𝑝^2 + 2𝑝, ⋯ < 𝑛
So roughly 𝑛/𝑝 operations for each prime 𝑝.

🔹 Step 2: Total work
The total number of operations is: ∑ (𝑛/𝑝) for p <= n where p is prime
Factor out 𝑛: = 𝑛⋅ ∑ 1/𝑝,    condition: p is prime & p <= n

🔹 Step 3: Harmonic sum over primes
It’s a known result in number theory that: ∑ (1/𝑝) ≈ log⁡log⁡𝑛 .. over condition p is prime & p <= n
(This comes from the Prime Number Theorem and related estimates.)

🔹 Step 4: Final complexity
So the total work is: 𝑂 ⁣(𝑛⋅loglog𝑛)

>> Space Complexity : O(n)
*/


int countPrimes(int n) {
    vector<bool> isPrime(n, true);

    for (int i = 2; i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j < n; j += i)
                isPrime[j] = false;
    
    int cnt = 0;
    for (int i = 2; i < n; i++)
        if (isPrime[i])
            cnt++;

    return cnt;
}

// Previous Implementations

// My implementation 
int countPrimesMy(int n) {
    if (n == 0 || n == 1) return 0;
    vector<int> isPrime(n, 1);
    isPrime[0] = 0, isPrime[1] = 0;     // mark 0 & 1 as non-primes
    int sq = sqrt(n);
    // for i in range (2, sqrt(n)) __ mark all multiples of integer i as non-prime
    for (int i = 2; i <= sq; i++) {
        int k = i;
        int ind = i * k;
        while (ind < n) {
            isPrime[ind] = 0;
            ind = i * (++k);
        }
    }
    int cnt = 0;
    // count all primes i.e. all indices with value 1
    for (int x : isPrime) {
        if (x == 1) cnt++;
    }
    return cnt;
}

// Best Implementation --- Some guy on Leetcode
int countPrimesX(int n) {
    vector<int> prime(n,1);
    for(int i=2;i*i <=n;i++){
        if(prime[i]){
            for(int j=i*i;j<n;j+=i){
                prime[j]=0;
            }
        }
    }
    int cnt =0;
    for(int i=2;i<n;i++) cnt+= prime[i];
    return cnt;
}

int printCountPrimes(int n) {
    if (n < 2) return 0;
    vector<int> isPrime(n, 1);
    for(int i=2; i*i < n; i++) {
        // mark multiples of i only if i is prime
        if (isPrime[i]) {
            for (int j = i*i; j<n; j+=i) {
                isPrime[j] = 0;
            }
        }
    }
    int cnt = 0;
    for (int i = 2; i<n; i++) {
        if (isPrime[i]) {
            cnt++;
            cout << i << " ";
        }
    }
    return cnt;
}

/*
Implementation Comparisons :- 
1> I checked for n == 0 && n === 1, but the other guy didn't. Because the for loop will not run when n < 2 and cnt will return as 0.
2> I calculated sqrt(n) and ran the loop till that, but the other guy ran the loop till i*i <= n.
3> I did the marking of multiples for each integer i in range (2, sqrt(n)) but the best implementation did so only for prime integers. 
i.e. if i is a prime, then only mark its multiples as non-prime. This is a good optimization and also the reason why my implementation is much slower.
We don't need to mark multiples of non-prime integers because they would have already been marked by their prime factors.
4> Also, to do the marking, I used a while loop, but the other guy used a for loop with j+=i. This is also a good optimization.
5> At last, I counted the primes by counting all indices with value 1, but the other guy did so by adding up all values in the prime array 
that too from index 2 to n-1. This is because all values are either 0 or 1, so adding them up gives the count of primes directly. 
And range 2 to n-1 is used becuause 0 & 1 are not primes and thus there counts should not be included.
*/

int main() {
    int n = 1000;
    int x = printCountPrimes(n);
    cout << "\nNumber of primes less than " << n << " are : " << x << endl;
    return 0;
}