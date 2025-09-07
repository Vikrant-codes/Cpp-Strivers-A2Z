/*
GFG - Implement Lower Bound - Easy

Given a sorted array arr[] and a number target, the task is to find the lower bound of the target in this given array. 
The lower bound of a number is defined as the smallest index in the sorted array where the element is greater than or equal to the given number.
Note: If all the elements in the given array are smaller than the target, the lower bound will be the length of the array. 

Examples :-
Input:  arr[] = [2, 3, 7, 10, 11, 11, 25], target = 9 __ Output: 3
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 11 __Output: 4
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 100 __ Output: 7 __ Explanation: Since all elements are <100 so lb = size of array = 7

Constraints :- 1 ≤ arr.size() ≤ 106 __ 1 ≤ arr[i] ≤ 106 __ 1 ≤ target ≤ 106
*/ 

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity : O(1)
int lowerBoundBrute(vector<int> arr, int target) {
    int n = arr.size();
    for(int i=0; i<n; i++) {
        if (arr[i] >= target)
            return i;
    }
    return n; // If no element is found then return size of the array
}

// Optimal Approach (Binary Search) : Time Complexity : O(log n) __ Space Complexity : O(1)
int lowerBound(vector<int> arr, int target) {
    int low = 0, high = arr.size()-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target)
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return low; // low will be the index of the first element >= target
}

int main() {
    vector<int> arr = {2, 3, 7, 10, 11, 11, 25};
    int target = 100;
    int ind = lowerBound(arr, target);
    if (ind < arr.size()) cout << "Lower bound index : " << ind << " and element : " << arr[ind] << endl;
    else cout << "Lower bound index : " << ind << " and element : " << "No such element" << endl;

    return 0;
}