/*
GFG - Primes in a Range : Medium

Given two integers l and r, find and return all prime numbers in the range [l, r] (inclusive).

Examples :-

Input: l = 1, r = 10
Output: [2, 3, 5, 7]
Explanation:
The prime numbers between 1 and 10 are 2, 3, 5 and 7.

Input: l = 2, r = 5
Output: [2, 3, 5]
Explanation:
The prime numbers between 2 and 5 are 2, 3 and 5.

Constraints :- 
• 1 ≤ l ≤ r ≤ 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(r - l + 1) * O(sqrt(r)) __ Space Complexity : O(1)
/*
Naive Approach :-
For each number in range l to r, check if it is prime, add the number to answer only if it is prime.

The prime check takes O(sqrt(x)) time to check whether x is prime or not, 
for all numbers in range [l, r], the naive approach will take approx. O(r-l+1) * O(sqrt(x))
Since constraints are large (1 ≤ l ≤ r ≤ 10^6), this approach will give TLE
*/
bool isPrime(int n) {
    if (n < 2) return false;

    for (int i = 2; i * i <= n; i++) 
        if (n % i == 0)
            return false;

    return true;
}

vector<int> primeRangeNaive(int l, int r) {
    vector<int> ans;

    for (int i = l; l <= r; i++) 
        if (isPrime(i))
            ans.push_back(i);            

    return ans;
}

// Using Sieve of Eratosthenes :- Time Complexity : O(r log log r) + O(r - l + 1) __ Space Complexity : O(r)
// We can use Sieve of Eratosthenes to quickly check whether a number is prime in O(1) after building the sieve.
vector<bool> getSieve(int n) {
    vector<bool> isPrime(n+1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    
    for(int i = 2; i * i <= n; i++)
        if (isPrime[i]) 
            for (int j = i * i; j <= n; j+=i)
                isPrime[j] = false;
    
    return isPrime;
}

vector<int> primeRange(int l, int r) {
    vector<bool> isPrime = getSieve(r);     // O(r log log r)
    vector<int> ans;
    
    // O(r - l + 1)
    for (int i = l; i <= r; i++) 
        if(isPrime[i])
            ans.push_back(i);
            
    return ans;
}

int main() {
    return 0;
}