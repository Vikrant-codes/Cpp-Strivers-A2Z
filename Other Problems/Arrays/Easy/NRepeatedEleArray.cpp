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

int main() {
    return 0;
}