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

// Sorting Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
Sorting approach : Idea ->
1. Sort the array
2. After sorting, the array should ideally be : 1, 2, 3, 4, ..., n
3. Any gap in this sequence means a number is missing
4. Traverse the sorted array and find the missing elements from the expected sequence
*/
vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<int> ans;

    int expected = 1;
    for (int i = 0; i < n; i++) {
        // skip duplicates
        if (i > 0 && nums[i] == nums[i-1]) 
            continue;

        // fill missing numbers
        while (nums[i] > expected) {
            ans.push_back(expected);
            expected++;
        }

        // move expected forward if matched/found in array
        if (nums[i] == expected) 
            expected++; 
    }

    // if numbers at the end are missing
    while (expected <= n) {
        ans.push_back(expected);
        expected++;
    }

    return ans;
}

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