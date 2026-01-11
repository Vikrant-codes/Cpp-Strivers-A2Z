/*
Leetcode - 448. Find All Numbers Disappeared in an Array : Easy

Given an array nums of n integers where nums[i] is in the range [1, n], 
return an array of all the integers in the range [1, n] that do not appear in nums.

Examples :-

Input: nums = [4,3,2,7,8,2,3,1] __ Output: [5,6]

Input: nums = [1,1] __ Output: [2]

Constraints :-
- n == nums.length
- 1 <= n <= 10^5
- 1 <= nums[i] <= n

Follow up: Could you do it without extra space and in O(n) runtime? 
You may assume the returned list does not count as extra space.
*/

#include <bits/stdc++.h>
using namespace std;

// HashArray Approach : Time Complexity : O(n) __ Space Complexity : O(n)
vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    vector<int> hashArr(n);
    vector<int> ans;

    for (int&x : nums) 
        hashArr[x-1]++;
    
    for (int i=0; i<n; i++)
        if (hashArr[i] == 0) 
            ans.push_back(i+1);
    
    return ans;
}

int main() {
    return 0;
}