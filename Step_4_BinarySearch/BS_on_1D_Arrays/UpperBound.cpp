/*
GFG - Implement Upper Bound - Easy

Given a sorted array arr[] and a number target, the task is to find the upper bound of the target in this given array.
The upper bound of a number is defined as the smallest index in the sorted array where the element is greater than the given number.
Note: If all the elements in the given array are smaller than or equal to the target, the upper bound will be the length of the array.

Examples :-
Input:  arr[] = [2, 3, 7, 10, 11, 11, 25], target = 9 __ Output: 3
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 11 __ Output: 6
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 100 __ Output: 7

Constraints :- 1 ≤ arr.size() ≤ 106 __ 1 ≤ arr[i] ≤ 106 __ 1 ≤ target ≤ 106
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity : O(1)
int upperBoundBrute(vector<int> arr, int target) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        if (arr[i] > target) return i;
    }
    return n;
}

int upperBound(vector<int> arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if ( arr[mid] <= target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}

int main() {
    vector<int> arr = {2, 3, 7, 10, 11, 11, 25};
    int target = 11;
    int ind = upperBound(arr, target);
    if (ind < arr.size()) cout << "Upper bound index : " << ind << " and element : " << arr[ind] << endl;
    else cout << "Upper bound index : " << ind << " and element : " << "No such element" << endl;

    return 0;
}