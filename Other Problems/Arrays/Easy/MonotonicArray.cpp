/*
Leetcode - 896. Monotonic Array : Easy

An array is monotonic if it is either monotone increasing or monotone decreasing.
An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. 
An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
Given an integer array nums, return true if the given array is monotonic, or false otherwise.

Examples :-

Input: nums = [1,2,2,3] __ Output: true
Input: nums = [6,5,4,4] __ Output: true
Input: nums = [1,3,2] __ Output: false

Constraints :-
1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
*/

#include<bits/stdc++.h>
using namespace std;

// Flag Based Linear Scan Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
💡 Intuition
An array is monotonic if it is either:
- Entirely non-decreasing (each element ≤ next), or
- Entirely non-increasing (each element ≥ next).
So, while iterating, if you ever find both increasing and decreasing patterns, the array can’t be monotonic.

⚙️ Algorithm
1. Initialize two boolean flags:
-- inc → becomes true if any nums[i] < nums[i+1]
-- dec → becomes true if any nums[i] > nums[i+1]
2. Traverse the array once and update the flags.
3. If both inc and dec become true at any point → not monotonic → return false.
4. Otherwise → monotonic → return true.

<< Equal condition (nums[i]==nums[i+1]) isn't considered because equal elements are both montonic increasing/dereasing >>

⏱️ Complexity
Time: O(n) — single pass through the array.
Space: O(1) — constant extra space.
*/
bool isMonotonic(vector<int>& nums) {
    int n = nums.size();
    bool dec = 0, inc = 0;

    for (int i=0; i<n-1; i++) {
        if (nums[i] < nums[i+1]) inc = 1;
        else if (nums[i] > nums[i+1]) dec = 1;

        if (inc && dec) return false;
    }

    return true;
}

int main() {

    return 0;
}