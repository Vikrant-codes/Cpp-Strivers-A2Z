/*
leetcode - 88. Merge Sorted Array : Easy

You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, 
representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1. 
To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, 
and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

Examples :-

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3 __ Output: [1,2,2,3,5,6]

Input: nums1 = [1], m = 1, nums2 = [], n = 0 __ Output: [1]

Input: nums1 = [0], m = 0, nums2 = [1], n = 1 __ Output: [1]
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
 
Constraints:- nums1.length == m + n __ nums2.length == n __ 0 <= m, n <= 200 __ 1 <= m + n <= 200 __ -109 <= nums1[i], nums2[j] <= 109

Follow up: Can you come up with an algorithm that runs in O(m + n) time?
*/

#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m-1, j = n-1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        // if nums1[i] >= nums2[j] then we select the nums1[i] and place it at nums1[k] position and decrement the pointer i
        if (nums1[i] >= nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        }
        // else when nums1[i] < nums2[j] then nums2[j] is selected and placed at nums1[k] position, decrement the pointer j
        else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    // check if any elements are left in nums2 and if so copy them to nums1
    while (j >= 0) {
        nums1[k] = nums2[j];
        k--;
        j--;
    }
}

// This above code can be written in a more compact way as below .. The logic is same but the code is more compact
void mergeCompactVersion(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        nums1[k--] = (nums1[i] >= nums2[j]) ? nums1[i--] : nums2[j--];
    }
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}


int main() {
    vector<int> arr1 = {1,2,4,7,9,0,0,0,0}, arr2 = {3,5,6,8};
    int m1 = 5, n1 = 4;
    vector<int> arr3 = {1,2,3,0,0,0}, arr4 = {2,5,6};
    int m2 = 3, n2 = 3;
    vector<int> arr5 = {1}, arr6 = {};
    int m3 = 1, n3 = 0;
    vector<int> arr7 = {0}, arr8 = {1};
    int m4 = 0, n4 = 1;
    
    merge(arr1, m1, arr2, n1);
    for(int x : arr1) cout << x << " ";

    return 0;
}