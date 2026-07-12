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
• 1 <= n <= 10^5
• 1 <= l <= r <= 10^6
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

// Better Approach : Sieve of Eratosthenes
// Time Complexity : O(n) + O(maxR log log maxR) + O(n * (r - l + 1)) __ Space Complexity : O(maxR) / O(10^6)
/*
The Naive approach has very high time complexity, so we must think about how to optimise it.
We can't escape the O(n) outer loop which loops through each query as we need to read all queries,
so to optimise the time complexity, we must try to optimise the prime check which is taking O(sqrt(x)) for a number x.
We know that the best way to check for primes in a range is by using 'Sieve of Eratosthenes'.
So, we can create a sieve which will take O(n * log(log(n)) ) where n is the upper limit upto which prime check will be done.
Since the constraints guarantee that the max. value of r can be 10^6, so we can either compute the sieve till 10^6
or, we can find the maximum value of 'r' across all the queries and then get the sieve till that value.

Once, we get the sieve, we can simply loop through all the queries and for each l & r of current query, 
we can count primes in the range [l, r] by simply looping through the numbers and 
checking whether the number is prime or not using sieve (prime check using sieve will be O(1)).

>> Complexity Analysis :-

### Time Complexity :

++ Pre-computation of Sieve:-
    - To create the sieve upto some value n, the time required is 'O(n log log n)'
    - If we get the sieve till 10^6 (which is the max. value r can have), the time would be O(10^6 log log 10^6)
    - Or, we can firstly find the maximum value of r across all queries and get the sieve till that maximum value of r (maxR),
      for that case, time will be O(n) + O(maxR log log maxR)
    - For some queries, it is possible that the max. value of r is much smaller than 10^6, so it is generally good to 
      firstly get the max. value of r and then get the sieve till that value.
So, sieve pre-computation takes O(n) + O(maxR log log maxR)

- Iterating in queries takes O(n) time, where n is the number of queries.
- For each query, iterating from l to r takes O(r - l + 1) time.
- Using sieve, prime check can be done in O(1)
Thus, after getting sieve, the time taken to count primes for each query will be O(n * (r - l + 1))

So, total time complexity = O(n) + O(maxR log log maxR) + O(n * (r - l + 1))

### Space Complexity :
- We are using an extra space to store the sieve, this will be O(maxR) in size and in worst-case it will be O(10^6)
*/
vector<int> getSieve(int n) {
    vector<int> isPrime(n+1, 1);
    isPrime[0] = 0;
    isPrime[1] = 0;

    for (int i = 2; i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j <= n; j+=i)
                isPrime[j] = false;

    return isPrime;
}

vector<int> countPrimesInRangesBetter(vector<vector<int>>& queries) {
    int n = queries.size();
    vector<int> ans(n);

    // find the maximum value of 'r' across all queries to know the maximum limit upto which sieve must be created : O(n)
    int maxR = 0;
    for (vector<int> query : queries)
        maxR = max(maxR, query[1]);

    // create sieve containing data of primes upto maximum r : O(maxR log log maxR)
    vector<int> isPrime = getSieve(maxR);

    // for each query [l,r], count the no. of primes in range l to r using sieve to check for prime
    for (int i = 0; i < n; i++) {
        int l = queries[i][0], r = queries[i][1];
        int cnt = 0;

        for (int x = l; x <= r; x++) 
            cnt += isPrime[x];

        ans[i] = cnt;
    }

    return ans;
}

// Optimal Approach : Sieve of Eratosthenes and Prefix Sum
// Time Complexity : O(n) + O(maxR log log maxR) + O(n) + O(n) __ Space Complexity : O(maxR) / O(10^6)
/*
The previous approach still has high time complexity, we must optimise it further.
The problem is the repetitive counting of primes in range [l, r] for all queries.
We need to count how many primes exist in range [l, r] for all queries.
If we can optimise this, then the approach can be optimised.

To do so, we use the prefix sum approach on the sieve.
Instead of storing whether a particular number i is prime or not at index i, 
if we can pre-compute the count of primes till i and store it in some vector/array for all the numbers,
then it would become easier to find the count of primes in range [l, r].

Ex- assume for numbers till 20
sieve = [0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0]
         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
Now, if we want to check how many primes exists in range [l, r], then we can simply count primes from l to r.
But, doing this for multiple queries will be inefficient.
So, what if we pre-compute the no. of primes till all numbers, i.e. prime[i] will tell us the count of primes till 'i'

prime = [0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 8, 8]
         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20

Now, suppose we need the count of primes in range [5, 18]
Prime count till 18 = prime[18] = 7, 
Prime count till 5 = prime[5] = 3,
but, since we need to check for prime count in range[5, 18], we need to consider 5 as well, so we do 
Prime count in range [5, 18] = Prime count till 18 - Prime count till (5-1) 
                             = 7 - 2 = 5

So, we just need to create a prefix-sum array which will tell us the count of primes till each number 'i'.
This will help us to count the number of primes in range [l, r] in O(1) time for each query.

Instead of creating a different array to build prefix sum array, we can over-write the sieve to give us the prime counts. 

>> Algorithm 
- Pre-compute all primes till the maximum value of r across all queries
- build a prefix-sum array of prime counts (say arr), such that arr[i] gives the count of primes till i
- loop through all queries, for each query range [l, r], prime count = arr[r] - arr[l-1]

>> Complexity Analysis :-

### Time Complexity :

- Pre-computation of Sieve :- O(n) + O(maxR log log maxR), or, O(10^6 log log 10^6)

++ Building PrefixSum array of prime counts : O(n)

- Iterating in queries takes O(n) time, where n is the number of queries.
- The count of primes in range [l, r] for each query can be found in O(1) using the prefix-sum array
- So, after building sieve and prefix-sum array, the prime count for all the queries can be found in O(n)

So, total time complexity = O(n) + O(maxR log log maxR) + O(n) + O(n)

### Space Complexity :
- We are using an extra space to store the sieve & prefic-sum array, 
  this will be O(maxR) in size and in worst-case it will be O(10^6)
*/
vector<int> countPrimesInRanges(vector<vector<int>>& queries) {
    int n = queries.size();
    vector<int> ans(n);

    int maxR = 0;
    for (vector<int> query : queries)
        maxR = max(maxR, query[1]);
    
    vector<int> isPrime = getSieve(maxR);

    int sum = 0;
    for (int i = 2; i <= maxR; i++) {
        sum += isPrime[i];
        isPrime[i] = sum;
    }

    for (int i = 0; i < n; i++) {
        int l = queries[i][0], r = queries[i][1];
        int cnt = isPrime[r] - isPrime[l-1];

        ans[i] = cnt;
    }

    return ans;
}

int main() {
    vector<vector<int>> queries = {{1, 10}, {5, 10}, {11, 20}, {1, 100000}};

    vector<int> ans = countPrimesInRanges(queries);

    for (int x : ans) 
        cout << x << " ";

    return 0;
}