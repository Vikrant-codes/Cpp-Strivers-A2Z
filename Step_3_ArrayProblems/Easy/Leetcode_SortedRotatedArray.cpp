/*
Leetcode <-- Check if Array Is Sorted and Rotated --> Difficulty: Easy

Given an array arr, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). 
Otherwise, return false. There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.
*/

#include <iostream>
#include <vector>
using namespace std;

bool checkSorted(vector<int> arr){
    int n = arr.size();
    int drop = 0;
    // consider array to be circular, so use modulo operator to wrap around the end of the array
    // use arr[(i+1)%n] to get the next element wrapping around
    // check if the current element is greater than the next element
    // if it is, increment the drop count
    // for a rotated sorted array there can be at most one drop ... so return false if drop count exceeds 1
    for(int i=0; i<n; i++){
        if(arr[i] > arr[(i+1)%n]) drop++;
        if(drop>1) return false;
    }
    return true;
}

int main() {
    vector <int> arr = {3,4,5,1,2};
    cout << checkSorted(arr);
    return 0;
}