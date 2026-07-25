// Right Rotate Array by K Places

/*
Leetcode - 189. Rotate Array : Medium

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Examples :-

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints :-
• 1 <= nums.length <= 10^5
• -2^31 <= nums[i] <= 2^31 - 1
• 0 <= k <= 10^5

Follow up:
Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
*/

#include<bits/stdc++.h>
using namespace std;

// Optimal Approach (Reversal) : Time Complexity : O(2n) __ Space Complexity : O(1)
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    vector<int>::iterator it = nums.begin();
    
    reverse(it, it + n);
    reverse(it, it + k);
    reverse(it + k, it + n);
}

/*
Without using the built-in reverse method & iterator

void reverseArr(vector<int>& nums, int start, int end) {
    while (start < end) {
        swap(nums[start], nums[end]);
        start++; end--;
    }
}

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    reverseArr(nums, 0, n-1);      // reverse the whole array
    reverseArr(nums, 0, k-1);      // reverse the first k elements
    reverseArr(nums, k, n-1);      // reverse the next n-k elements
}
*/




int main() {
    return 0;
}