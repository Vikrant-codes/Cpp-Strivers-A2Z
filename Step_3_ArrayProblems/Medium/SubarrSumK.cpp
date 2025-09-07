/*
Leetcode - 560. Subarray Sum Equals K : Medium

Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
A subarray is a contiguous non-empty sequence of elements within an array.

Input: nums = [1,1,1], k = 2 __ Output: 2 __ Explanation : The two subarrays with sum = 2 are arr[0:1] and arr[1:2]

Input: nums = [1,2,3], k = 3 __ Output: 2 __ Explanation : The two subarrays with sum = 3 are arr[0:1] and arr[2:2]

Input: nums = [1,2,3,-3,1,1,1,4,2,-3], k = 3 __ Output: 8
Subarrays are : {1,2}, {1,2,3,-3}, {2,3,-2,1}, {3}, {3,-3,1,1,1}, {-3,1,1,1,4,2,-3}, {1,1,1}, {4,2,-3}
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
// Approach :- Check the sum of all possible subarrays and increment the count variable if sum equals k 
int CountSubarrSumKBrute(vector<int> arr, int k) {
    int n = arr.size();
    int count = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            if (sum == k) count++;
        }
    }
    return count;
}

// Optimal Approach (Prefix Sum Approach) : Time Complexity : O(n) __ Space Complexity : O(n)
/*
Prefix Sum Approach : We traverse the array storing the sum upto current element in a sum variable now we are interested in sum == k ... 
let's assume that a subarray with sum = k exists such that the current element is at the end of that subarray ... to know whether such a subarray 
exists or not we check whether sum-k exists in the prefix_sum map or not. Because if a subarray having sum = sum-k exists in the map that means 
there is a subarray having sum k so we update the count. But we don't just simply increment the count because there might be multiple subarrays having 
sum = sum-k .. Consider the example [1,2,3,-3,1,1,1,4,2,-3] , k = 3... now for i = 6 i.e. for the array [1,2,3,-3,1,1,1] the total sum = 6 
and we check whether some PrefixSumSubarrays with sum = 3 are present or not .. here there are 2 such subarrays which are [1,2] and [1,2,3,-3] 
(we only check for subarrays having sum = sum-k and starting at index 0 so even though [3] also has sum = 3 , it isn't considered) so for these two 
prefixSumSubarrays we can get two subarrays having sum = 3 which are [3,-3,1,1,1] (for prefixSumSubarr [1,2]) & [1,1,1] (for prefixSumSubarr [1,2,3,-3])
So we keep track of the count of prefixSumSubarrays having same sum so while storing these prefixSums in map we do mpp[sum]++. 
And also if prefixSubarr with sum = sum-k is found then we update the count with the total number of prefixSubarr having sum = sum-k
*/
int subarraySum(vector<int> arr, int k) {
    int n = arr.size();
    int count = 0, sum = 0;
    unordered_map<int, int> mpp;  // this map will store {prefixSum, count} i.e. prefixSum and how many times it occured
    mpp[0] = 1;
    for(int i=0; i<n; i++) {
        sum += arr[i];            // add current element to prefix Sum
        int preSum = sum - k;     // Calculate sum-k 
        // Add the number of subarrays having preSum = sum-k... if no such prefixSubarr exists then mpp[preSum] gives 0
        count += mpp[preSum];
        mpp[sum]++;               // Update the count of prefix sum in the map.
    }
    return count;
}

int main() {
    vector<int> arr = {1,2,3,-3,1,1,1,4,2,-3};
    int k = 3;
    int count = subarraySum(arr, k);
    cout << "Count of subarrays with sum " << k << " : " << count;
    return 0;
}