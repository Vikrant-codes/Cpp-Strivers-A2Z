/*
TUF - 821. Reverse an array 2

Given an array nums of n integers, return reverse of the array.

Examples :-

Input : nums = [1, 2, 3, 4, 5] __ Output : [5, 4, 3, 2, 1]
Input : nums = [1, 3, 3, 3, 5] __ Output : [5, 3, 3, 3, 1]

Constraints :-
• 1 <= n <= 100
• 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Reverse Array Using Recursion: Time Complexity : O(n/2) __ Space Complexity : O(n/2) -- recursive stack space

// helper method
void fun(vector<int>& nums, int l, int r) {
    if (l < r) {
        swap(nums[l], nums[r]);
        
        fun(nums, l+1, r-1);
    }
}

// helper method using a single pointer variable
void fun(vector<int>& arr, int l) {
    if (l >= arr.size()/2)
        return;
    
    swap(arr[l], arr[arr.size() - 1 - l]);

    fun(arr, l+1);
}

// actual caller method
vector<int> reverseArray(vector<int>& nums){			
	fun(nums, 0, nums.size()-1);
    return nums;
}

int main() {
    return 0;
}