/*
Leetcode - 81. Search in Rotated Sorted Array II -- Medium

There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).
Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

Examples :-

nums = [2,5,6,0,0,1,2], target = 0 __ Output: true
nums = [2,5,6,0,0,1,2], target = 3 __ Output: false
*/

#include <bits/stdc++.h>
using namespace std; 

/*
Approach :- 
The problem is similar to 'Leetcode - 33. Search in Rotated Sorted Array' but here we can have duplicates in the array as well. 
These duplicates can cause problems in identifying the sorted half of the array.
Example :- Consider the array [3,1,2,3,3,3] and target = 2. Now the mid element will be 3 and since this isn't equal to target, we will then check 
for sorted half. But this finding of sorted half will be problematic because of duplicates. Since here arr[low] = 3, arr[mid] = 3 and arr[high] = 3, 
so we cannot determine which half is sorted. Since arr[low] <= arr[mid] condition is true and also arr[mid] <= arr[high] condition is true,
we cannot determine which half is sorted.
In such cases we can simply reduce the search space by incrementing low and decrementing high.
*/

// Optimal Approach :- Time Complexity - O(log n) in average case and O(n/2) in worst case, Space Complexity - O(1)

int search(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
            // if we cannot determine which half is sorted, we can simply reduce the search space
            low++;
            high--;
            continue;
        }
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
    vector<int> nums = {2,5,6,0,0,1,2};
    int target = 5;
    bool ans = search(nums, target);
    cout << ans;

    return 0;
}