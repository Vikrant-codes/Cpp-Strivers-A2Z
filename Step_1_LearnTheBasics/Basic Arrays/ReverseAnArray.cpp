/*
TUF - 741. Reverse an array

Given an array arr of n elements. The task is to reverse the given array. The reversal of array should be inplace.

Examples :-

Input: n=5, arr = [1,2,3,4,5]
Output: [5,4,3,2,1]
Explanation: The reverse of the array [1,2,3,4,5] is [5,4,3,2,1]

Input: n=6, arr = [1,2,1,1,5,1]
Output: [1,5,1,1,2,1]
Explanation: The reverse of the array [1,2,1,1,5,1] is [1,5,1,1,2,1].

Constraints :-
• 1 <= n <= 10^4
• 1 <= arr[i] <= 10^5
*/

#include<bits/stdc++.h>
using namespace std;

// Using a temporary array: Time Complexity : O(2n) __ Space Complexity : O(n)
void reverse(int arr[], int n){
    int temp[n];
    
    // traverse elements of arr in reverse order and add them to temp array
    int k = 0;      // curr index pointer for temp array
    for (int i = n - 1; i >= 0; i--) {
        temp[k] = arr[i];
        k++;
    }

    // re-write elements of arr with values from temp array
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

// Using two pointers: Time Complexity : O(n) __ Space Complexity : O(1)
void reverse(int arr[], int n){
    int i = 0, j = n-1;

    while (i < j) {
        swap(arr[i], arr[j]);
        i++; 
        j--;
    }
}

int main() {
    return 0;
}