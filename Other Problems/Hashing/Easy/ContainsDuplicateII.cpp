/*
Leetcode - 219. Contains Duplicate II : Easy

Given an integer array nums and an integer k, 
return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

Examples :-

Input: nums = [1,2,3,1], k = 3 __ Output: true
Input: nums = [1,0,1,1], k = 1 __ Output: true
Input: nums = [1,2,3,1,2,3], k = 2 __ Output: false

Constraints :-
1 <= nums.length <= 10^5
-109 <= nums[i] <= 10^9
0 <= k <= 10^5
*/
#include<bits/stdc++.h>
using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> mpp;
    for (int i=0; i<nums.size(); i++) {
        // if curr element already exists in map check whether curr index - previous index <= k
            
        if (mpp.find(nums[i]) != mpp.end()) {
            if (i - mpp[nums[i]] <= k) return true;
        }

        mpp[nums[i]] = i; // insert element / update value if already exists
    }
    return false;
}

int main() {
    return 0;
}