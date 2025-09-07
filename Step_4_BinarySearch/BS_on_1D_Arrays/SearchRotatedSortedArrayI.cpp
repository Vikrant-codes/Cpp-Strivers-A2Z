/*
Leetcode - 33. Search in Rotated Sorted Array -- Medium

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that 
the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). 
For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

Examples :- 
Input: nums = [4,5,6,7,0,1,2], target = 0 __ Output: 4
Input: nums = [4,5,6,7,0,1,2], target = 3 __ Output: -1
Input: nums = [1], target = 0 __ Output: -1

Constraints :- 1 <= nums.length <= 5000 __ -10^4 <= nums[i] <= 10^4 __ -10^4 <= target <= 10^4
All values of nums are unique.
nums is an ascending array that is possibly rotated.
*/

#include <bits/stdc++.h>
using namespace std; 

/*
Optimal Approach :-
identify the sorted half - then check whether the target element lies in that sorted half or not 
left half is sorted when nums[low] <= nums[mid] and right half is sorted when nums[mid] <= nums[high]
target would lie in sorted half if it's >= the first element of that half and <= the last element of that half
target lies in the left half if nums[low] <= target <= nums[mid]
target lies in the right half if nums[mid] <= target <= nums[high]

once the sorted half is identified we check whether the target lies in that half or not. If it does we adjust the search space accordingly 
otherwise we serach in other half
*/

int search(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        
        // if left half is sorted
        if (nums[low] <= nums[mid]) {
            // check if target lies in this sorted left half 
            if (nums[low] <= target && target <= nums[mid]) high = mid - 1;         // target lies in left half so skip the right half
            else low = mid + 1;        // target does not lie in left half so skip the left half
        }

        // if right half is sorted
        else {
            // check if target lies in this sorted right half
            if (nums[mid] <= target && target <= nums[high]) low = mid + 1;       // target lies in right half so skip the left half
            else high = mid - 1;    // target does not lie in right half so skip the right half
        }
    }
    return -1;
}

int main() {
    vector<int> nums = {6,7,0,1,2,3,4,5};
    int target = 5;
    int ind = search(nums, target);
    cout << ind;

    return 0;
}