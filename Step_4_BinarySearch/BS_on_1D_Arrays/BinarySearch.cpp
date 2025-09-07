/*
Leetcode - 704. Binary Search

Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. 
If target exists, then return its index. Otherwise, return -1.

Example 1: Input: nums = [-1,0,3,5,9,12], target = 9 __ Output: 4
Example 2: Input: nums = [-1,0,3,5,9,12], target = 2 __ Output: -1 

Constraints: 
1 <= nums.length <= 10 ^ 4 __ -10 ^ 4 < nums[i], target < 10 ^ 4
All the integers in nums are unique __ nums is sorted in ascending order
*/

#include <bits/stdc++.h>
using namespace std;

// Iterative Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
int binarySearch(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

// Recursive Approach : Time Complexity : O(log n) __ Space Complexity : O(log n) due to recursion stack
int binarySearchRec(vector<int> nums, int low, int high, int target) {
    if (low > high) return -1; // Base case : target not found

    int mid = low + (high - low) / 2;

    if (nums[mid] == target) 
        return mid;
    else if (nums[mid] > target) 
        return binarySearchRec(nums, low, mid-1, target);
    else 
        return binarySearchRec(nums, mid+1, high, target);
}

int main() {
    vector<int> arr = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    int ind = binarySearchRec(arr, 0, arr.size()-1, target);
    if (ind != -1) cout << "Element found at index : " << ind << endl;
    else cout << "Element not found" << endl;

    return 0;
}