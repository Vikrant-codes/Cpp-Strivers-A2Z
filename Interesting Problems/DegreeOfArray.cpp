/*
Leetcode - 697. Degree of an Array

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:- Input: nums = [1,2,2,3,1] __ Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.

Example 2:- Input: nums = [1,2,2,3,1,4,2] __ Output: 6
Explanation: 
The degree is 3 because the element 2 is repeated 3 times.
So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.

Constraints:-
nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
*/
#include <bits/stdc++.h>
using namespace std;

int findShortestSubArray(vector<int>& nums) {
    unordered_map<int, int> freq;           // stores frequency of each element
    unordered_map<int, int> st_ind;         // stores first occurence of each element
    int mx_freq = -1;
    int len = 0;

    for (int i=0; i<nums.size(); i++) {
        freq[nums[i]]++;             // update frequency of current element
        if (st_ind.find(nums[i]) == st_ind.end()) {
            st_ind[nums[i]] = i;    // add if it's first occurence of current element
        }
        // if max_freq is exceeded or same degree element with shorter occurence length is found
        if (freq[nums[i]] > mx_freq || (freq[nums[i]] == mx_freq && len > i-st_ind[nums[i]] + 1)){
            mx_freq = freq[nums[i]];
            len = i - st_ind[nums[i]] + 1;
        }
    }

    return len;
}

int main() {
    vector<int> nums = {1,2,2,3,1,4,2};
    cout << findShortestSubArray(nums) << endl;
    return 0;
}