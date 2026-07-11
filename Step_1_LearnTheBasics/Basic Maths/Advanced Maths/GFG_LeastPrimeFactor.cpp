/*
GFG - Least Prime Factor : Easy

Given a number N, find the least prime factors for all numbers from 1 to N.  
The least prime factor of an integer X is the smallest prime number that divides it.

Note : 
- 1 needs to be printed for 1.
- You need to return an array/vector/list of size N+1 and need to use 1-based indexing to store the answer for each number.

Examples :-

Input: N = 6
Output: [0, 1, 2, 3, 2, 5, 2] 
Explanation: 
least prime factor of 1 = 1,
least prime factor of 2 = 2,
least prime factor of 3 = 3,
least prime factor of 4 = 2,
least prime factor of 5 = 5,
least prime factor of 6 = 2.
So answer is[1, 2, 3, 2, 5, 2]. 

Input: N = 4
Output: [0, 1, 2, 3, 2]
Explanation: least prime factor of 1 = 1,
least prime factor of 2 = 2,
least prime factor of 3 = 3,
least prime factor of 4 = 2.
So answer is[1, 2, 3, 2]. 

Constraints: 2 <= n <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * √x) __ Space Complexity : O(1)
/*
- For each number 0 to n, compute its lpf and store it in an ans vector.

>> How to compute least prime factor of a number n ?
- If n is less than 2 (for n = 0 or 1), we return n itself.
- Else we loop from 2 to √n and return the first factor encountered (this will definitely be the lpf)
- In case no factor is found, it means n itself is prime, so return n

>> Complexity Analysis

-> Time Complexity
- O(n) to loop from 0 to n
- O(√x) to get the lpf of a number x (this will be called for all x in range [0, n])
- Total : O(n * √x) 

-> Space Complexity 
O(1) since no extra space is used, 
the ans vector is used but it is required for the question so it can't be avoided and hence not considered as extra space.
*/
int getLPF(int n) {
    if (n < 2) return n;
    
    for (int i = 2; i * i <= n; i++) 
        if (n % i == 0)
            return i;
    
    return n;
}

vector<int> leastPrimeFactorNaive(int n) {
    vector<int> ans;
    
    for (int i = 0; i <= n; i++)
        ans.push_back(getLPF(i));
        
    return ans;
}

// Optimal Approach : Time Complexity : O(n log log n) __ Space Complexity : O(n)
// See 'SmallestPrimeFactor.cpp' to understand the approach
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


int main() {
    return 0;
}