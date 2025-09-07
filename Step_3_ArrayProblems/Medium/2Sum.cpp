/*
Given an array of integers arr[] and an integer target. 
1st variant : Return true if there exists two numbers such that their sum is equal to target.
2nd variant : Return the indices of the two numbers, in case no such pair exists return [-1,-1] 
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Brute Force Approach -> Time Complexity : O(n^2) __ Space Complexity : O(1)
pair<int, int> TwoSumBrute(vector<int> arr, int target){
    int n = arr.size();
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]+arr[j] == target){
                return {i, j};
            }
        }
    }
    return {-1,-1};
}

// Better ApproACH (using Hashing) -> Time Complexity : O(n) __ Space Complexity : O(n)
// Time Complexity : unordered_map --> O(n) {best case}, O(n^2) {worst case} .... map --> O(n log n)
pair<int, int> TwoSumHash(vector<int> arr, int target){
    unordered_map<int, int> mpp;
    for(int i=0; i<arr.size(); i++){
        int pair = target - arr[i];
        // Check if pair element exists in the map
        if(mpp.find(pair) != mpp.end()){
            return{mpp[pair], i}; 
        }
        mpp[arr[i]] = i;        // add the current element to the map
    }
    return {-1,-1};
}

// Optimal Approach -> Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
Sort the array and then use 2 pointer approach to find the 2 sum pair elements. Take a left pointer & right pointer (initially at 0 & end). 
Check if left & right element sum == target. If it is greater than move right to left (do right --) , so to lower the sum ..
If the sum is lower than move left towards right (do left ++). return once we find the the pair.
*/
bool TwoSum2Pointer(vector<int> arr, int target){
    int n = arr.size(), left = 0, right = n - 1;
    sort(arr.begin(), arr.end());
    for(int i=0; i<n; i++){
        if (arr[left] + arr[right] == target) return true;
        else if (arr[left] + arr[right] > target) right--;
        else left++; 
    }
    return false;
}

int main() {
    vector<int> arr = {2,6,5,8,11,9};
    int target = 14;
    pair<int, int> ans = TwoSumHash(arr, target);
    cout << "Indices : " << ans.first << " _ " << ans.second << endl;
    cout << "Elements : " << arr[ans.first] << " _ " << arr[ans.second];

    bool x = TwoSum2Pointer(arr, target);
    if(x) cout << "\nPair exists" << endl;
    else cout << "\nPair does not exist" << endl;
    return 0;
}