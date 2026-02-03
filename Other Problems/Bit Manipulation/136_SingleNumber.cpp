/*
Leetcode - 136. Single Number : Easy

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples :-
Input: nums = [2,2,1] __ Output: 1
Input: nums = [4,1,2,1,2] __ Output: 4
Input: nums = [1] __ Output: 1

Constraints :-
• 1 <= nums.length <= 3 * 10^4
• -3 * 10^4 <= nums[i] <= 3 * 10^4
• Each element in the array appears twice except for one element which appears only once.
*/

#include <bits/stdc++.h>
using namespace std;

int singleNumber(vector<int>& nums) {
    int x = 0;
    for(int i=0; i<nums.size(); i++) x ^= nums[i];
    return x;
}

int main() {
    return 0;
}