// Given an array, print all the elements which are leaders. 
// A Leader is an element that is greater than all of the elements on its right side in the array.

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1) {O(n) for storing the result}
vector<int> leadersBrute(vector<int> arr) {
    int n = arr.size();
    vector<int> result;
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            if(arr[i] < arr[j]) break;
            if(j == n-1) result.push_back(arr[i]);
        }
    }
    return result;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1) {O(n) for storing the result}
vector<int> getLeaders(vector<int> arr) {
    int n = arr.size();
    int max = INT_MIN;
    vector<int> result;
    for(int i=n-1; i>=0; i--) {
        if(arr[i] > max) {
            result.push_back(arr[i]);
            max = arr[i];
        }
    }
    return result;
}

int main() {
    vector<int> arr = {16, 17, 4, 3, 5, 2};
    vector<int> leaders = getLeaders(arr);
    cout << "Leaders in the array are: ";
    for(int x : leaders) cout << x << " ";
    return 0;
}