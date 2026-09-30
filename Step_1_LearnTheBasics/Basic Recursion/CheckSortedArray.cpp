/*
TUF - 333. Check if the Array is Sorted II

Given an array nums of n integers, return true if the array nums is sorted in non-decreasing order or else false.

Examples :-

Input : nums = [1, 2, 3, 4, 5] __ Output : true
Explanation : For all i (1 <= i <= 4) it holds nums[i] <= nums[i+1], hence it is sorted and we return true.

Input : nums = [1, 2, 1, 4, 5] __ Output : false
Explanation : For i == 2 it does not hold nums[i] <= nums[i+1], hence it is not sorted and we return false.

Constraints :-
• 1 <= n <= 100
• 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// using recursion

bool fun(vector<int>& nums, int ind) {
    if (ind == nums.size()) {
        return true;
    }

    if (nums[ind] < nums[ind-1]) 
        return false;
    
    return fun(nums, ind + 1);
}

bool isSorted(vector<int>& nums){
	return fun(nums, 1);
}

int main() {
    return 0;
}