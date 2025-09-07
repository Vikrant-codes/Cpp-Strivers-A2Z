/*
Leetcode <-- Remove Duplicates from Sorted Array --> Difficulty : Easy
Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. 
The relative order of the elements should be kept the same. Then return the number of unique elements in nums.
*/


#include <iostream>
#include <set>
#include <vector>

using namespace std;

// Brute Force : Use set to store unique array elements, loop thorugh set values and store them in array, once the set loop ends return the index
// Complexity : O(N log N) + O(N)
int removeUsingSet(vector<int>& arr) {
    set<int> s;
    for(int i = 0; i<arr.size(); i++){  // loop runs n times
        s.insert(arr[i]);               // log n for insertion
    }
    int i = 0;
    // set contains only the k distinct element so loop runs k times ... i is incremented each time so at the end i = k
    for(auto x : s){
        arr[i] = x;
        i++;
    }
    return i;           // number of distinct elements in the array
}

// OPtimal Approach : Using two pointers ... Conplexity : O(n)
int removeDuplicates(vector<int>& arr) {
    int i = 0;
    int n = arr.size();
    for(int j = 1; j<n; j++){
        if(arr[i] != arr[j]){
            i++;
            arr[i] = arr[j];
        }
    }
    return i+1;
}

int main() {
    vector<int> arr = {1,1,2,2,3,4,5,5,6};
    int dist = removeDuplicates(arr);
    for(int x : arr) cout << x << " ";
    cout << endl << "Unique Count : " << dist; 

    return 0;
}
