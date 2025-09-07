/*
Leetcode - 34. Find First and Last Position of Element in Sorted Array -- Medium

Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].

Examples :-
Input: nums = [5,7,7,8,8,10], target = 8 __ Output: [3,4]
Input: nums = [5,7,7,8,8,10], target = 6 __ Output: [-1,-1]
Input: nums = [], target = 0 __ Output: [-1,-1]

Constraints :- 0 <= nums.length <= 10^5 __ -10^9 <= nums[i] <= 10^9 __ -10^9 <= target <= 10^9
nums is a non-decreasing array.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(2 log n) - log nfor both searches (first and last occurrence) __ Space Complexity: O(1)
int firstOccurrence(vector<int>& nums, int target) {
    int n = nums.size();
    int first = -1;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= target) {
            if (nums[mid] == target) first = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return first;
}

int lastOccurrence(vector<int> &nums, int target) {
    int n = nums.size();
    int last = -1;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] <= target) {
            if (nums[mid] == target) last = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return last;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = firstOccurrence(nums, target);
    int last = lastOccurrence(nums, target);
    
    return {first, last};
}

int main() {
    vector<int> arr = {5, 7, 7, 8, 8, 10};
    int x = 8;
    vector<int> result = searchRange(arr, x);
    cout << "First : " << result[0] << " __ Last : " << result[1] << endl;

    return 0;
}