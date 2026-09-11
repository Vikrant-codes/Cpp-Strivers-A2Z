/*
Leetcode - 1390. Four Divisors : Medium

Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. 
If there is no such integer in the array, return 0.

Examples :-

Input: nums = [21,4,7] __ Output: 32
Explanation: 
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.

Input: nums = [21,21] __ Output: 64

Input: nums = [1,2,3,4,5] __ Output: 0

Constraints :-
- 1 <= nums.length <= 10^4
- 1 <= nums[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(m · √n) __ Space Complexity : O(1)
/*
Intuition
For a number to have exactly 4 divisors, its divisors must be very limited.
Instead of blindly checking all numbers from 1 to n, we use this key idea:
|   👉 Divisors come in pairs : If i divides n, then n / i also divides n.

So by iterating only up to √n, we can:
• Count divisors efficiently
• Accumulate their sum
• Stop early if divisors exceed 4 (since we don’t care anymore)

The helper function hasFourDivisors(n) :-
• Finds all divisors of n
• Keeps track of:
    • cntDiv → number of divisors
    • sum → sum of divisors
• Returns sum only if n has exactly 4 divisors, otherwise 0

Then sumFourDivisors() simply applies this logic to every number and adds up valid results.

Complexity Analysis
Let:
• m = size of nums
• n = value of a number in nums

Time Complexity : O(m · √n)
• hasFourDivisors(n) → O(√n)
• Overall → O(m · √n)
Early stopping (cntDiv > 4) often makes it faster in practice.

Space Complexity : O(1) (only constant extra variables)
*/

// helper function -- return sum of divisors of the number n only if it has exactly 4 divisors, otherwise 0
int hasFourDivisors(int n) {
    int sum = 0;
    int cntDiv = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cntDiv++;
            sum += i;
            int f2 = n / i;
            if (f2 != i) { 
                sum += f2;
                cntDiv++;
            }
        }
        if (cntDiv > 4) return 0;
    }
    return cntDiv == 4 ? sum : 0;
}

int sumFourDivisors(vector<int>& nums) {
    int ans = 0;
    for (int& x : nums) {
        ans += hasFourDivisors(x);
    }
    return ans;
}

int main() {
    vector<int> nums = {1,2,3,4,5,9,16,25};
    int ans = sumFourDivisors(nums);
    cout << ans;

    return 0;
}