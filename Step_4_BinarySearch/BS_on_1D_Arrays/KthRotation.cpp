//Find out how many times the array has been rotated

/*
GFG - Find Kth Rotation -- Easy

Given an increasing sorted rotated array arr of distinct integers. The array is right-rotated k times. Find the value of k.

Examples :-

Input: arr = [5, 1, 2, 3, 4] __ Output: 1
Input: arr = [1, 2, 3, 4, 5] __ Output: 0

Constraints :- 1 ≤ arr.size() ≤10^5 __ 1 ≤ arr[i] ≤ 10^7
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach 1 :- We can find the no. of rotations by the index of the smallest element of the array. In a sorted array the smallest element is at index 0. 
If the array is rotated k times, then that smallest element moves to index k. So to find this smallest element we can iterate through the array and 
find the index of the smallest element. Return that index as the no. of rotations.

Approach 2 :- If we traverse through the rotated sorted array linearly then we can find the no. of rotations by checking the adjacent elements. 
In sorted array the adjacent elements are always in increasing order but in a sorted rotated array there will be a point where the smaller index 
element is greater than the larger index element. This is the point of rotation. 
Ex -> 
[3,4,5,6,1,2] Here 6 > 1 and 1 is at index 4 so the array is rotated 4 times. 
[1,2,3,4,5] Here there is no such condition when the adjacent elements are not in increasing order so the no of rotations is 0. 
*/
int findKRotationBrute1(vector<int> &arr) {
    int n = arr.size();
    int mn = INT_MAX;
    int ind = 0;
    for(int i=0; i<n; i++) {
        if (arr[i] < mn) {
            mn = arr[i];
            ind = i;
        }
    }
    return ind;
}
int findKRotationBrute2(vector<int> &arr) {
    int n = arr.size();
    for(int i=0; i<n-1; i++) {
        if(arr[i] > arr[i+1]) {
            return i+1;
        }
    }
    return 0;
}

// Optimal Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
// Approach :- We use binary search to find the index of the smallest element in the rotated sorted array. 
int findKRotation(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    int ind = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        //search space is already sorted then arr[low] will always be the minimum in that search space:
        if (arr[low] <= arr[high]) {
            if (arr[low] < ans) {
                ans = arr[low];
                ind = low;
            }
            break;
        }
        //if left part is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] < ans) {
                ans = arr[low];
                ind = low;
            }
            low = mid + 1;                   // Eliminate left half
        }
        //if right part is sorted:
        else {
            if (arr[mid] < ans) {
                ans = arr[mid];
                ind = mid;
            }
            high = mid - 1;                  // Eliminate right half
        }
    }
    return ans;
}

int main() {

    return 0;
}