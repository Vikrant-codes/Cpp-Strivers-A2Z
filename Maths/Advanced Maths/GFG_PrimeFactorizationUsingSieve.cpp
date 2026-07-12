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