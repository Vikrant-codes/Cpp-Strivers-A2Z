/*
Leetcode - 162. Find Peak Element -- Medium

A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. 
If the array contains multiple peaks, return the index to any of the peaks.
You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater 
than a neighbor that is outside the array.
You must write an algorithm that runs in O(log n) time.

Examples :- 
Input: nums = [1,2,3,1] __ Output: 2
Input: nums = [1,2,1,3,5,6,4] __ Output: 1 or 5

Constraints :- 1 <= nums.length <= 1000 __ -2^31 <= nums[i] <= 2^31 - 1 __ nums[i] != nums[i + 1] for all valid i.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity : O(1)
int findPeakBrute(vector<int>& nums) {
    int n = nums.size();
    for(int i=0; i<n; i++) {
        if ( (i==0 || nums[i-1] < nums[i]) && (i==n-1 || nums[i] > nums[i+1]) ) {
            return i;
        }
    }
    return -1; // this line should never be reached if input is valid
}

// Optimal Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    // Edge cases for single element in array and first/last element being peak
    if (n == 1 || nums[0] > nums[1]) return 0;
    if (nums[n-1] > nums[n-2]) return n-1;
    
    // start search space from index 1 to n-2 to avoid out of bounds access
    int low = 1, high = n-2;
        
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) return mid;      // if mid is peak element
        if (nums[mid] > nums[mid - 1]) low = mid + 1;                                // if mid is on increasing slope, peak must be on right side
        else high = mid - 1;                                                         // if mid is on decreasing slope, peak must be on left side 
        // Note: The case where mid is at the vertex of a 'V' shape is handled by the above conditions 
    }

    return -1;
}

int main() {

    return 0;
}

/*
Python Code for the same problem -- GFG160

def peakElement(arr):
    # Binary Search Approach -- O(log n) solution
    n = len(arr)
    if n == 1 or arr[0]>arr[1]:
        return 0
    if arr[n-1]>arr[n-2]:
        return n-1
    low, high = 1, n-2
    while low<=high:
        mid = low + int((high-low)/2)
        # For single peak element in the array 3 conditions exist. These are
        # 1.) Either mid is the peak element , or 
        # 2.) peak is on the right of mid .... in this case mid lies on a increasing slope thus arr[mid]>arr[mid-1] , or
        # 3.) peak is on the left of mid .... in this case mid lies on a decreasing slope thus arr[mid]>arr[mid+1]
        
        if arr[mid]>arr[mid-1] and arr[mid]>arr[mid+1]:
            return mid
        elif arr[mid]>arr[mid-1]:
            low = mid+1
        elif arr[mid]>arr[mid+1]:
            high = mid-1

        # Now for multiple peaks there might be a case when the mid is between a decreasing slope and a increasing slop '\/', like this V vertex in V shape
        # In such case mid is at the terminating end of a decreasing slope and initial end of a increasing slope
        # For such cases arr[mid]<arr[mid-1] and arr[mid]<arr[mid+1] , Ex - [2,5,3,4,1] mid = 3 and 3<5 and 3<4 so 3 is like the vertex of 'V' 
        # In such cases peak exist in both left half and right half so we can check any half we want
        else:
            low = mid+1
            #high = mid-1
    return -1
*/