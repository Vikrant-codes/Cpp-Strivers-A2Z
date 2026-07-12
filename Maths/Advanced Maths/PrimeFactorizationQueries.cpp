/*
Prime factorisation of Numbers - Queries

You are given an integer array queries of length n.
Return the prime factorization of each number in array queries in sorted order.

Examples :-

Input: queries = [2, 3, 4, 5, 6]
Output: [ [2], [3], [2, 2], [5], [2, 3] ]
Explanation: 
The values 2, 3, 5 are itself prime numbers.
The prime factorization of 4 will be --> 2 * 2.
The prime factorization of 6 will be --> 2 * 3.

Input: queries = [7, 12, 18]
Output: [ [7], [2, 2, 3], [2, 3, 3] ]
Explanation: 
The value 7 itself is a prime number.
The prime factorization of 12 will be --> 2 * 2 * 3.
The prime factorization of 18 will be --> 2 * 3 * 3.

Constraints :-
- 1 <= n <= 10^5
- 2 <= queries[i] <= 2*10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * √m) __ Space Complexity : O(1)
/*
- We know how to get prime factorization of a number in O(√n) time (See GFG_PrimeFactorization.cpp).
- For each number in queries, we can get its prime factorization and store it in a vector.
- Finally, we return a vector of vectors containing the prime factorization of each number in queries.

>> Complexity Analysis
-> Time Complexity : O(n * √m), where n = queries.size() and m = max(queries[i])
- For each number in queries, we get its prime factorization in O(√m)
- O(n) to iterate through the queries array.
- Thus, overall O(n * √m)

-> Space Complexity : O(1)

Since the constraints are high, this approach will not work for all test cases and give TLE, so we need to optimize it further.
*/
vector<int> getPrimeFactorization(int n) {
    vector<int> factors;

    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n != 1) factors.push_back(n);

    return factors;
}

vector<vector<int>> primeFactorsNaive(vector<int>& queries){
    int n = queries.size();
    vector<vector<int>> ans(n);

    for (int i = 0; i < n; i++) {
        ans[i] = getPrimeFactorization(queries[i]);
    }

    return ans;
}

// Optimal Approach : Time Complexity : O(max log log max) + O(n * log x) __ Space Complexity : O(max)
// where max = max. value of queries vector
/*
We know that we can easily get the prime factorization of a number in O(log n) time 
if we have the smallest prime factor (SPF) of each number precomputed.

So, we can use the Sieve of Eratosthenes to pre-compute the smallest prime factor (SPF) for each number up to 
the maximum number in queries. 
Then, for each number in queries, we can get its prime factorization in O(log n) time using the SPF array.

>> Complexity Analysis :-
- We must compute sieve so that we can get the spf for all concerned numbers in the queries vector.
  So, we find firstly find the maximum value of the queries vector to know the max. limit for computing sieve.
  O(n) to find the maximum value of the queries vector
- O(m log log m) to compute the sieve, where m = max. value of the queries vector
- Then, we need to iterate the queries vector to get each number and find its prime factorization using sieve
- O(n) to iterate the queries vector, and, O(log x) to get the prime factorization of a number x using sieve
- So, after pre-computating sieve, it takes O(n * log x) to get the prime factorization of all numbers of queries

- Total Time Complexity : O(n) + O(max log log max) + O(n * log x)

-> Space Complexity : O(max) to store the spf sieve upto 'max' value
*/
vector<int> getSieveSPF(int n) {
    vector<int> spf(n+1);

    for (int i = 1; i <= n; i++) 
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

    return spf;
}

vector<vector<int>> primeFactors(vector<int>& queries){
    int n = queries.size();
    vector<vector<int>> ans(n);

    // O(n) to find the maximum value of queries vector
    int mx = 1;
    for (int x : queries) 
        if (x > mx)
            mx = x;
            
    // O(mx log log mx) to get the spf sieve
    vector<int> spf = getSieveSPF(mx);

    // O(n * log x) to find the prime factorization for all number x in queries vector
    for (int i = 0; i < n; i++) {
        int x = queries[i];
        vector<int> temp;

        while (x != 1) {
            temp.push_back(spf[x]);
            x = x / spf[x];
        }

        ans[i] = temp;
    }

    return ans;
}

int main() {
    return 0;
}