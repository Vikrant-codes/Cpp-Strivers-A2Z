/*
Leetcode - 2523. Closest Prime Numbers in Range : Medium

Given two positive integers left and right, find the two integers num1 and num2 such that:
- left <= num1 < num2 <= right .
- Both num1 and num2 are prime numbers.
- num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.

Return the positive integer array ans = [num1, num2]. 
If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value.
If no such numbers exist, return [-1, -1].

Examples :-

Input: left = 10, right = 19 __ Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Input: left = 4, right = 6 __ Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.

Constraints :- 
• 1 <= left <= right <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(n log(log n)) + O(n) ~ O(n log(log n)) __ Space Complexity : O(n)
/*
Since the range of numbers can be from 1 to 10^6, 
we must use Sieve of Eratosthenes to quickly check for prime numbers in the range.

So, we firstly generate a sieve of prime numbers from 1 to right (O(right log(log right)) time complexity).
Then we iterate through the range [left, right] and check for prime numbers.

We have to find the closest prime numbers in the range, 
so we keep track of the last prime number seen and whenever we find a new prime number, 
we check the distance between this new prime and the last prime seen.
If the distance is smaller than the previous minimum distance, we update our answer.
*/

vector<bool> getSieve(int n) {
    vector<bool> isPrime(n+1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;

    return isPrime;
}

vector<int> closestPrimes1(int left, int right) {
    vector<bool> isPrime = getSieve(right);

    vector<int> ans = {-1, -1};

    int l = left;
    while (l <= right && !isPrime[l]) l++;

    // now l is the first prime in range [left, right]
    // we keep l as 'last prime seen till now' and move another pointer r starting from l + 1
    // whenever we find another prime (isPrime[r] == true), 
    // we check the distance between r and l (distance between this prime pair)
    // if distance is smaller than previous found pair, update ans 
    // whenever any new prime is found, we update l (last prime seen) as that prime even if ans updates or not

    for (int r = l+1; r <= right; r++) {
        if (isPrime[r]) {
            if (ans[0] == -1 || ans[1] - ans[0] > (r - l)) {
                // ans[0] = l;
                // ans[1] = r;
                // or we can do this in one line as below
                ans = {l , r};
            }
            l = r;
        }
    }

    return ans;
}

vector<int> closestPrimes2(int left, int right) {
    vector<bool> isPrime = getSieve(right);

    vector<int> ans = {-1, -1};
    int prevPrime = -1;
    int minDiff = INT_MAX;

    for (int i = left; i <= right; i++) {
        if (!isPrime[i]) 
            continue;
        
        if (prevPrime != -1) {
            int diff = i - prevPrime;
            
            if (diff < minDiff) {
                minDiff = diff;
                ans = {prevPrime, i};
            }
        }
    
        prevPrime = i;
    }

    return ans;
}

// Early exit condition
/*
We know that 2 is the only even prime number, and all other prime numbers are odd.
Due to this, all consecutive pair of prime numbers have a minimum distance of 2 at least (since only odd numbers are prime)
The prime pair (2, 3) is the only exception apart from this pair, any other prime pair would have at least a min. gap of 2.

Ex -> pairs (5, 7), (11, 13), (17, 19) etc. have a gap of 2

Since, we are supposed to find the prime pairs with the min. gap and 
in case of same gap, we need to consider the smaller prime pair, 
thus if our pair has a gap of 1 or 2, we know that we won't be able to find any other pair with a smaller gap available.

So, in case the current prime pair has a gap of 1 or 2 (gap 1 for prime pair (2, 3)), then we can simply return that pair.
*/
vector<int> closestPrimes(int left, int right) {
    vector<bool> isPrime = getSieve(right);

    vector<int> ans = {-1, -1};

    int l = left;
    while (l <= right && !isPrime[l]) l++;

    for (int r = l+1; r <= right; r++) {
        if (isPrime[r]) {
            int gap = r - l;
            int ansGap = ans[1] - ans[0];
            if (ans[0] == -1 || gap < ansGap) {
                ans = {l, r};
                if (gap == 1 || gap == 2) 
                    return ans;
            }
            l = r;
        }
    }

    return ans;
}

int main() {

    return 0;
}