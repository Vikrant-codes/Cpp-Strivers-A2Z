/*
Length of the longest subarray with zero Sum

Problem Statement: Given an array containing both positive and negative integers, 
we have to find the length of the longest subarray with the sum of all elements equal to zero.

Examples -

array[] = {9, -3, 3, -1, 6,  -5} __ Output = 5
Explanation :- Subarrays are {-3, 3} , {-1, 6, -5}, {-3, 3, -1, 6, -5}. Since we require the length of the longest subarray, our answer is 5.

array[] = {6, -2, 2, -8, 1, 7, 4, -10} __ Output = 8
Explanation :- Subarrays are {-2, 2}, {-8, 1, 7}, {-2, 2, -8, 1, 7}, {6, -2, 2, -8, 1, 7, 4, -10}

array[] = {1, 0, -5} __ Output = 1
Explanation :- Subarray : {0}. Length of subarray is 1.

array[] = {1, 3, -5, 6, -2} __ Output = 0
Explanation :- No subarray with sum 0.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n ^ 2) __ Space Complexity : O(1)
// Approach :- check all subarrays whose sum is zero and return the length of the longest subarray
int longest0SubarrBrute(vector<int> arr) {
    int max_len = 0;
    int n = arr.size();
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            // if sum of subarray is 0, check the length of the subarray using length = (j-i+1) and update max_len if this length is greater  
            // if (sum == 0) {
            //     int length = j-i+1;
            //     max_len = max(max_len, length);
            // }
            if (sum == 0 && (j-i+1) > max_len) {
                max_len = j-i+1;
            }
        }
    }
    return max_len;
}

// Optimal Approach (Prefix Sum Approach) : Time Complexity : O(n) __ Space Complexity : O(n) 
/*
Approach :- We use prefix sum approach to solve this problem. We use an unordered_map / map data structure and traverse the array using a single loop.
Assume the sum upto current element is k and we need a subaaray of sum = 0. If the current element is the last element of a 0 sum subaaray then 
there must exist a subarray whose sum is equal to k. For ex-> for the array portion {9,1,3,-3} the sum upto the last element is 10 and the subarr {3,-3}
has the sum = 0 now such a subarray exists only when then the remaining portion of the array has a sum equal to 10. 
We keep a map data structure and evaluate the sum upto current element (let it be k)... if that sum itself is zero then this subarr would 
definitely be the longest till now so we update max_len to be i+1. Else we check if the sum k already exists in the map then the zero sum subarr would 
have a length of i - mpp[sum] and we update max_len accordingly. Else if sum not exists in the map then we insert the the sum value with index i. 
*/
int longest0Subarr(vector<int> arr) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    int max_len = 0, sum = 0;
    for(int i=0; i<n; i++) {
        sum += arr[i];
        if (sum == 0) max_len = i+1;
        else {
            if (mpp.find(sum) != mpp.end()) {
                max_len = max(max_len, i - mpp[sum]);
            }
            else {
                mpp[sum] = i;
            }
        }
    }
    return max_len;
}

int main() {
    vector<int> v = {9, -3, 3, -1, 6,  -5};
    int x = longest0Subarr(v);
    cout << x;
    return 0;
}