/*
Leetcode - 35. Search Insert Position

Given a sorted array of distinct integers and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.

Examples :-
Input: nums = [1,3,5,6], target = 5 __ Output: 2
Input: nums = [1,3,5,6], target = 2 __ Output: 1
Input: nums = [1,3,5,6], target = 7 __ Output: 4

Constraints :- 1 <= nums.length <= 10^4 __ -10^4 <= nums[i] <= 10^4 __ -10^4 <= target <= 10^4
nums contains distinct values sorted in ascending order.
*/

#include <bits/stdc++.h>
using namespace std;

int searchInsert(vector<int> &nums, int target) {
    int low = 0;
    int high = nums.size()-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> nums = {1,3,5,6};
    int target = 7;
    int pos = searchInsert(nums, target);
    cout << "Search Insert Pos is :- " << pos << endl;

    return 0;
}