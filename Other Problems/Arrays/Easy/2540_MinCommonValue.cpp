/*
Leetcode - 2540. Minimum Common Value : Easy

Given two integer arrays nums1 and nums2, sorted in non-decreasing order, 
return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.
Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.

Examples :-

Input: nums1 = [1,2,3], nums2 = [2,4]
Output: 2
Explanation: The smallest element common to both arrays is 2, so we return 2.

Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
Output: 2
Explanation: There are two common elements in the array 2 and 3 out of which 2 is the smallest, so 2 is returned.

Constraints:-
- 1 <= nums1.length, nums2.length <= 10^5
- 1 <= nums1[i], nums2[j] <= 10^9
- Both nums1 and nums2 are sorted in non-decreasing order.
*/

#include <bits/stdc++.h>
using namespace std;

// There can be multiple approaches to this problem --
// 1. Naive : For each element of array1, linear search whether it exists in array2. If yes, return it.
// 2. Better : use binary search to search for the element in arr2 as arr is sorted so binary search can be used
// 3. Hashing : insert all elements of one array into a hashing data structure, find the first element of arr2 which exists in arr1.

// Optimal Approach (Two Pointers Approach): Time Complexity : O(n1 + n2) __ Space Complexity : O(1)
int getCommon(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0;
    int m = nums1.size(), n = nums2.size();

    while (i < m && j < n) {
        if (nums1[i] == nums2[j])
            return nums1[i];
        else if (nums1[i] > nums2[j]) j++;
        else i++;
    }

    return -1;
}

int main() {
    return 0;
}