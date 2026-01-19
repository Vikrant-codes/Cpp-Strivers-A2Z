/*
Leetcode - 961. N-Repeated Element in Size 2N Array : Easy

You are given an integer array nums with the following properties:
• nums.length == 2 * n.
• nums contains n + 1 unique elements.
• Exactly one element of nums is repeated n times.
Return the element that is repeated n times.

Examples :-
Input: nums = [1,2,3,3] __ Output: 3
Input: nums = [2,1,2,5,3,2] __ Output: 2
Input: nums = [5,1,5,2,5,3,5,4] __ Output: 5

Constraints :-
• 2 <= n <= 5000
• nums.length == 2 * n
• 0 <= nums[i] <= 104
• nums contains n + 1 unique elements and one of them is repeated exactly n times.
*/

#include <bits/stdc++.h>
using namespace std;

// Hashing Approach :- Time Complexity : O(n) __ Space Complexity : O(n)
int repeatedNTimesHash1(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> mpp;
    for (int x : nums) {
        mpp[x]++;
        if (mpp[x] == n/2) return x;
    }
    return -1;
}

int repeatedNTimesHash2(vector<int>& nums) {
    unordered_set<int> st;
    for (int x : nums) {
        if (st.count(x)) return x;
        st.insert(x);
    }
    return -1;
}

// Optimal Approach (Pigeonhole Principle) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Problem fact
• Array size = 2N
• One element appears N times
• All other elements appear exactly once
So total elements :- N (repeated element) + N (distinct elements) = 2N

Core pigeonhole insight -> Think in terms of positions, not values.
If one number appears N times in an array of length 2N,
👉 it is impossible for all its occurrences to be far apart.

Why?
If every occurrence of the repeated number were separated by ≥ 4 positions, then:
You’d need at least 3 distinct numbers between each pair
For N occurrences, you’d need ≥ 3(N−1) other numbers
But you only have N − 1 distinct numbers total

❌ Impossible.
This is exactly the pigeonhole principle:
|   You can’t distribute N identical items into 2N slots while keeping all of them “far apart” — some must land close together.

What “close together” guarantees
From the above constraint, at least two occurrences of the repeated element must be within distance ≤ 3.
So one of these must happen somewhere :
nums[i] == nums[i+1]
nums[i] == nums[i+2]
nums[i] == nums[i+3]

-- We are checking upto 3 places for repeated elements for conditions like XabXcdXefX....
becuase doing will require ≥ 3(N−1) distinct integers while we only have 'N' distinct 
and we know N < 3(N-1) for all values of N in range [2,infinity), here n is in range [2,5000]

But why do we check upto 3 places, why not just 2 places ??
If we assume that every occurrence of the repeated number were separated by ≥ 3 positions, 
then we'd need at least 2 distinct numbers between each pair
For N occurrences, you’d need ≥ 2(N−1) other numbers
Now, we have 'N' distinct. N can have any value between [2,5000], but we see for N == 2, 2(N-1) is also 2.
So, N < 2(N-1) is not always true for range [2,5000], as for N = 2, N = 2(N-1)
Thus, we check for at at least two occurrences of the repeated element within distance ≤ 3.

When N = 2, conditions like XabX might exist where two distinct element can exist between the repetitions,
but this condition is only possible for N = 2. 
For any other condition, the minimum distance between any two reptitions can only be at most 1 place like XaXbXcXd.
*/

int repeatedNTimes(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n-1; i++) {
        if (nums[i] == nums[i+1] ) return nums[i];
        if (i+2 < n && nums[i] == nums[i+2]) return nums[i];
        if (i+3 < n && nums[i] == nums[i+3]) return nums[i];
    }
    return -1;
}

int main() {
    return 0;
}