/*
🔹 Sieve of Eratosthenes

- The Sieve of Eratosthenes is an ancient and highly efficient algorithm used to find all prime numbers 
up to a specified integer, n.
- It works by iteratively "sieving out" (crossing out) all composite numbers, leaving only the primes.
- It’s called the “Sieve of Eratosthenes” because it was invented by the 
ancient Greek mathematician Eratosthenes of Cyrene (around 240 BC).
- The word sieve comes from the physical tool used to separate finer particles from coarser ones 
(like flour from bran, or sand from pebbles).
- Similarly, the algorithm “sifts out” the non-primes step by step, leaving only primes behind.
*/

#include <bits/stdc++.h>
using namespace std;

// Goal : To find/print all the prime numbers upto 'n'

// Naive Approach :- Time Complexity : O(n * √n) __ Space Complexity : O(1)
/*
For each integer in range [1, n] check if it is a prime number.

>> Time Complexity Analysis :-
- Looping through each integer in range [1, n] takes O(n)
- For each number x, prime check takes O(√x), this prime check is done for all iterations. 
- So, total time is roughly O((n * √n) 
*/
bool isPrime(int x) {
    if (x < 2) return false;

    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) 
            return false;

    return true;
}

void printPrimesNaive(int n) {
    for (int i = 2; i < n; i++) 
        if (isPrime(i))
            cout << i << " ";
}

// 🔹 Sieve of Eratosthenes

// Optimal Approach (Sieve of Eratosthenes) :- Time Complexity : 𝑂 ⁣(𝑛⋅log(log 𝑛)) __ Space Complexity : O(n)
/*
>> Goal: Find/count all prime numbers strictly less than 𝑛

>> Intuition :-
- A prime is a number with no divisors except 1 and itself.
- If a number 𝑝 is prime, then all multiples of 𝑝 are composite.
- So instead of testing each number individually, we can mark composites in bulk by iterating through multiples of primes.

>> How the Algorithm Works ? 
1. Initialize: Create a list (or boolean array) of size n+1, where arr[i] will tell us whether 'i' is prime or not. 
Mark all of them initially as "potentially prime" (e.g., True).
Mark 0 & 1 as false, since both 0 & 1 are non-primes.

2. First Prime: Start at the smallest unmarked number, 2. 
Because 2 is prime, keep it but mark all of its proper multiples (e.g., 4, 6, 8, 10, etc.) as "composite" (False).

3. Continue: Move to the next unmarked number. In this case, it is 3. 
It is prime, so you keep it and mark all of its proper multiples as composite.

4. The Result: All numbers that remain unmarked at the end are prime numbers.

|>> Optimizations <<|

>> When marking multiples of a prime number 'p', we can start marking from 'p * p' and go till n.

We are crossing-out all the multiples of prime numbers, since we know those multiples are composites.
Now observe what multiples we cross-out for different prime numbers :-
For 2 :- 2 x 2, 2 x 3, 2 x 4, 2 x 5, 2 x 6, 2 x 7, ..... till n
For 3 :- 3 x 2, 3 x 3, 3 x 4, 3 x 5, 3 x 6, 3 x 7, ..... till n
For 5 :- 5 x 2, 5 x 3, 5 x 4, 5 x 5, 5 x 6, 5 x 7, ..... till n
For 7 :- 7 x 2, 7 x 3, 7 x 4, 7 x 5, 7 x 6, 7 x 7, ..... till n
...

Now, consider for 3, do we actually need to mark 3 x 2 as non-prime, 
we know that 3 x 2 would have already been marked by 2 as non-prime since it is also a factor of 2 (2 x 3 = 3 x 2).
So, for the number 3, we can simply start the marking from 3 x 3.

Similarly, for 5, do we actually need to mark 5 x 2, 5 x 3, 5 x 4
5 x 2 would have been marked by 2 already
5 x 3 would have been marked by 3 already
5 x 4 would have been marked by 2 already (since 4 is a multiple of 2, so 5 x 4 would be marked by 2)
So, for the number 5, we can start the marking from 5 x 5 and go till n marking all its multiples as non-primes.

Similarly, for 7, the multiples 7 x 2, 7 x 3, 7 x 4, 7 x 5, 7 x 6 would have been already marked by smaller primes.
So, we can start the marking from 7 x 7 and go till n. 

So, for a prime number 'p', we should start marking its multiples starting from the number 'p * p', 
since all its previous multiples would have been marked by smaller primes.

>> We can run the outer loop till sqrt(n) only, no need to run till n

We saw that for a prime p, we can start marking its multiples from 'p * p'.
Now assume, p is a prime number (p <= n), such that p * p > n
So, the marking of multiples will never be done for multiples of p.
Ex- assume n = 100.
for p = 7, we start marking multiples of 7 starting from 49 (7 * 7), and going till 98 (98 is the largest factor of 7 till 100).
the next prime after 7 is 11, so we then move to 11.
to mark the multiples of 11, we start the marking from 121 (11 * 11), 
but 121 > 100, so marking of 11's multiples will not be done.

The same will happen for all the next prime numbers (13, 17, 19 etc).

So, we don't need to do anything for those prime number 'p' whose square (p*p) exceeds n itself.
p * p > n    =>    p > sqrt(n)
So, we can simply run the outer loop till sqrt(n) so that we only check multiples of prime numbers which are less than sqrt(n). 


>> Complexity Analysis :-

-> Time Complexity : O(n log(log n))
🔹 Step 1: What work do we do? 
For each prime 𝑝 ≤ 𝑛, we mark its multiples: 𝑝^2, 𝑝^2 + 𝑝, 𝑝^2 + 2𝑝, ⋯ < 𝑛
So roughly 𝑛/𝑝 operations for each prime 𝑝.

🔹 Step 2: Total work
The total number of operations is: ∑ (𝑛/𝑝) for p <= n where p is prime
Factor out 𝑛: = 𝑛⋅ ∑ 1/𝑝,    condition: p is prime & p <= n

🔹 Step 3: Harmonic sum over primes
It’s a known result in number theory that: ∑ (1/𝑝) ≈ log(log ⁡𝑛) .. over condition p is prime & p <= n
(This comes from the Prime Number Theorem and related estimates.)

🔹 Step 4: Final complexity
So the total work is: 𝑂 ⁣(𝑛⋅log(log 𝑛))

-> Space Complexity : O(n), since we are using space for an array of size n+1.
*/

void sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n+1, true);

    // core logic of Sieve of Eratosthenes
    for (int i = 2; i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;

    // print the prime numbers
    for (int i = 2; i <= n; i++)
        if(isPrime[i])
            cout << i << " ";
}

int main() {
    sieveOfEratosthenes(131);

    return 0;
}