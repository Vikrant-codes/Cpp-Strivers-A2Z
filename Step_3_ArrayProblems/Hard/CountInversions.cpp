/*
GFG - Count Inversions : Medium

Given an array of integers arr[]. Find the Inversion Count in the array.
Two elements arr[i] and arr[j] form an inversion if arr[i] > arr[j] and i < j.

Inversion Count: For an array, inversion count indicates how far (or close) the array is from being sorted. 
> If the array is already sorted then the inversion count is 0.
> If an array is sorted in the reverse order then the inversion count is the maximum. 

Examples :-

Input: arr[] = [2, 4, 1, 3, 5] __ Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).

Input: arr[] = [2, 3, 4, 5, 6] __ Output: 0
Explanation: As the sequence is already sorted so there is no inversion count.

Input: arr[] = [10, 10, 10] __ Output: 0
Explanation: As all the elements of array are same, so there is no inversion count.

Constraints: 1 ≤ arr.size() ≤ 10^5 __ 1 ≤ arr[i] ≤ 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n ^ 2) __ Space Complexity : O(1)
// Approach : For each element index i loop from i+1 to end and count the no of elements smaller than arr[i], return the total count for all elements
int countInvBrute(vector<int> arr) {
    int n = arr.size();
    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if (arr[j] < arr[i]) cnt++;
        }
    }
    return cnt;
}

// Optimal Approach (merge sort approach) : Time Complexity : O(n log n) __ Space Complexity : O(n)
/*
Approach :- Same as Merge Sort. Here while merging two sorted portions we check for inversion count by comparing the elements of left & right subarr 
if left element is bigger it means there is an inversion and that right element will be a inversion pair for all the remaining elements of left subarr
also. So we add mid-left+1 to inversion_count. After the whole array is sorted we get the inversion_count for the whole array. 

Now to consider this count for various left & right sub-arrays we can either use a global count variable and update it in the merge function. Or 
we can pass the count variable as a reference to the merge function and update it there.
*/

int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid+1;
    int invCount = 0;
        
    while(left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
            invCount += (mid - left + 1);
        }
    }
        
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
        
    for(int i=low; i<=high; i++) {
        arr[i] = temp[i - low];
    }
        
    return invCount;
}
    
int mergeSort(vector<int> &arr, int low, int high) {
    int invCount = 0;
    if (low >= high) return invCount;
        
    int mid = low + (high - low) / 2;
        
    invCount += mergeSort(arr, low, mid);
    invCount += mergeSort(arr, mid+1, high);
    invCount += merge(arr, low, mid, high);
        
    return invCount;
}
    
int inversionCount(vector<int> &arr) {
    return mergeSort(arr, 0, arr.size()-1);
}

int main() {
    vector<int> arr = {5, 3, 2, 4, 1};
    int inv = inversionCount(arr);
    cout << inv;
    return 0;
}