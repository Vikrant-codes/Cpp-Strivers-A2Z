/*
Leetcode - 1848. Minimum Distance to the Target Element : Easy

Given an integer array nums (0-indexed) and two integers target and start, find an index i such that nums[i] == target 
and abs(i - start) is minimized. Note that abs(x) is the absolute value of x.
Return abs(i - start).
It is guaranteed that target exists in nums.

Examples :-

Input: nums = [1,2,3,4,5], target = 5, start = 3
Output: 1
Explanation: nums[4] = 5 is the only value equal to target, so the answer is abs(4 - 3) = 1.

Input: nums = [1], target = 1, start = 0
Output: 0
Explanation: nums[0] = 1 is the only value equal to target, so the answer is abs(0 - 0) = 0.

Input: nums = [1,1,1,1,1,1,1,1,1,1], target = 1, start = 0
Output: 0
Explanation: Every value of nums is 1, but nums[0] minimizes abs(i - start), which is abs(0 - 0) = 0.

Constraints :-
- 1 <= nums.length <= 1000
- 1 <= nums[i] <= 10^4
- 0 <= start < nums.length
- target is in nums.
*/

#include <bits/stdc++.h>
using namespace std;

// Linear Scan Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Traverse the entire array and whenever nums[i] == target, compute the distance abs(i - start). 
Keep track of the minimum such distance.
*/
int getMinDistance1(vector<int>& nums, int target, int start) {
    int n = nums.size();
    
    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
        if (nums[i] == target) 
            ans = min(ans, abs(start - i));
    
    return ans;
}

// Two Pointers Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach (Two-Pointer from Start):
Start from index start and expand outward using two pointers (l = start, r = start). (l moves to left and r moves to right)
At each step, check left and right positions.
The first time we encounter target, return the distance immediately.
👉 Since we expand in increasing distance order, the first match is guaranteed to be the minimum.

Time Complexity: O(n) (in worst case traverse entire array)
Space Complexity: O(1)
*/
int getMinDistance2(vector<int>& nums, int target, int start) {
    int n = nums.size();
    int l = start, r = start;

    while (l >= 0 && r < n) {
        if (nums[l] == target) return (start - l);
        else if (nums[r] == target) return (r - start);
        l--;
        r++;
    }

    while (l >= 0) {
        if (nums[l] == target) return (start - l);
        l--;
    }
    while (r < n) {
        if (nums[r] == target) return (r - start);
        r++;
    }

    return -1;      // dummy return, won't execute since it is guaranteed target exists in nums.
}

// Same approach, just better implementation
int getMinDistance3(vector<int>& nums, int target, int start) {
    int n = nums.size();
    int l = start, r = start;

    while (l >= 0 || r < n) {
        if (l >= 0 && nums[l] == target) return (start - l);
        if (r < n && nums[r] == target) return (r - start);
        l--;
        r++;
    }

    return -1;      // dummy return, won't execute since it is guaranteed target exists in nums.
}

int main() {
    return 0;
}