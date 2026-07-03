/*
Count Primes in Ranges

Given a 2d array queries[][] of size n, where each query queries[i] contain 2 elements [l, r], 
your task is to find the count of number of primes in inclusive range [l, r].
Return an array of size n, where the ith element is the answer to the ith query, 
i.e., ans[i] = the count of prime numbers in the range [l, r] specified by queries[i].

Example :-

Input: queries = [[1, 10], [5, 10], [11, 20]]
Output: [4, 2, 4]
Explanation:-
Query [1, 10]: The prime numbers are 2, 3, 5, 7, so the answer is 4.
Query [5, 10]: The prime numbers are 5, 7, so the answer is 2.
Query [11, 20]: The prime numbers are 11, 13, 17, 19, so the answer is 4.

Constraints:-
- 1 <= n <= 10^5
- 1 <= l <= r <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * (r - l + 1) * sqrt(r)) __ Space Complexity : O(1)
/*
For each query [l, r], iterate through all the numbers from l to r.
Check if the current number is prime using the checkPrime function.
Keep a counter variable to count the number of primes found in the range.
Store the count in the ith position of the answer array for the ith query.

>> Complexity Analysis :-
- Iterating in queries takes O(n) time, where n is the number of queries.
- For each query, iterating from l to r takes O(r - l + 1) time.
- Checking if a number is prime takes O(sqrt(k)) time, where k is the number being checked.
Since, we are gonna check all the numbers from l to r, the time complexity for isPrime() can't be calculated properly, 
but we can say that it will take O(sqrt(r)) time in the worst case.

So, total time complexity = O(n * (r - l + 1) * sqrt(r))

This approach doesn't uses any extra space, so the space complexity is O(1).
*/
bool isPrime(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    
    return true;
}

vector<int> countPrimesInRangesNaive(vector<vector<int>>& queries) {
    int n = queries.size();
    
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        int cnt = 0;

        int l = queries[i][0], r = queries[i][1];

        for (int j = l; j <= r; j++)
            if (isPrime(j)) 
                cnt++;

        ans[i] = cnt;
    }

    return ans;
}

// Better Approach 
vector<int> getSieve(int n) {
    vector<int> isPrime(n+1, 1);
    isPrime[0] = 0;
    isPrime[1] = 0;
}


int main() {
    return 0;
}