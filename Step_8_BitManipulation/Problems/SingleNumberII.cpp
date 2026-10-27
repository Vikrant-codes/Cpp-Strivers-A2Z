/*
Leetcode - 137. Single Number II : Medium

Given an integer array nums where every element appears three times except for one, 
which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples :-

Input: nums = [2,2,3,2] __ Output: 3
Input: nums = [0,1,0,1,0,1,99] __ Output: 99

Constraints :-
• 1 <= nums.length <= 3 * 10^4
• -2^31 <= nums[i] <= 2^31 - 1
• Each element in nums appears exactly three times except for one element which appears once.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n) __ Space Complexity : O( (n-1)/3 + 1 )
int singleNumberHashMap(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int& x: nums)
        freq[x]++;
    
    for (auto& it : freq) 
        if (it.second == 1)
            return it.first;

    return -1;
}

int singleNumber(vector<int>& nums) {
    int ans = 0;

    for (int bitIndex = 0; bitIndex < 32; bitIndex++) {
        int cnt = 0;
    
        for (int& x : nums)
            if (x & (1 << bitIndex))
                cnt++;
    
        if (cnt % 3 != 0) 
            ans = ans | (1 << bitIndex);
    }

    return ans;
}

int singleNumber(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());
    
    for (int i = 1; i < n; i += 3) {
        if (nums[i] != nums[i - 1]) {
            return nums[i - 1];
        }
    }
    
    return nums[n - 1];
}


int main() {
    return 0;
}