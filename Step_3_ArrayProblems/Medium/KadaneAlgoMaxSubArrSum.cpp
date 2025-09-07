/*
Leetcode - 53. Maximum Subarray : Medium
Given an integer array nums, find the subarray with the largest sum, and return its sum. 
*/

#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
int MaxSumBrute(vector<int> arr) {
    int n = arr.size();
    int mx_sum = INT_MIN, sum = 0;
    for(int i=0; i<n; i++) {
        sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            mx_sum = max(mx_sum, sum);
        }
    }
    return mx_sum;
}

// Optimal Approach : 'Kadane's Algorithm' --> Time Complexity : O(n) __ Space Complexity : O(1)
/*
Initially we take max_sum to be INT_MIN. The basic intuition of this algo is that we don't want to carry forward a negative sum since a negative sum
will only lower the subarray sum. Initially sum is 0 we iterate through the array adding the current element to the sum , upadting the max_sum if sum 
is greater than max_sum and then since we don't want to take forward a negative sum so we check whether the sum is negative and if it is then it 
clearly means that those elements won't be a part of  maximum sum subarray since those element sum up to be negative so including them in any subarray 
will only lower the sum.
Example -> arr = [4,3,-8,2,3,-1,0,5,-6] ... initially max_sum = INT_MIN, sum = 0
array has 9 elements so i will go for 0 to 8 index.
i = 0 : sum += arr[i] = 4... max_sum becomes 4 (since 4 > INT_MIN)
i = 1 : sum += arr[i] = 7... max_sum becomes 7
i = 2 : sum += arr[i] = -1... max_sum remains 7 but since the sum becomes -ve so we won't consider [4,3,-8] to be a part of further subarrays . sum = 0
i = 3 : sum += arr[i] = 2... max_sum reamins 7
i = 4 : sum += arr[i] = 5... max_sum reamins 7
i = 5 : sum += arr[i] = 4... max_sum reamins 7
i = 6 : sum += arr[i] = 4... max_sum reamins 7
i = 7 : sum += arr[i] = 9... max_sum becomes 9
i = 8 : sum += arr[i] = 3... max_sum reamins 9
loop ends and we get maximum subarray sum to be 9.

Why we make sum = 0 whenever sum becomes -ve ?? This is done because we want to add elements such that sum becomes maximum but adding elements which 
carry -ve sum will only lower the further subarray sum so we drop the earlier subarray and start by re-initializing sum to be 0. 
*/
int KadanesAlgo(vector<int> arr) {
    int max_sum = INT_MIN, sum = 0;
    for(int i=0; i<arr.size(); i++) {
        sum += arr[i];
        if (sum > max_sum) max_sum = sum;
        if(sum < 0) sum = 0;
    }
    return max_sum;
}

void printMaxSumSubArr(vector<int> arr) {
    int max_sum = INT_MIN, sum = 0;
    int start = -1, ansStart = -1, ansEnd = -1;
    for(int i=0; i<arr.size(); i++){
        if (sum == 0) start = i;
        sum += arr[i];
        if (sum > max_sum){
            max_sum = sum;
            ansStart = start;
            ansEnd = i;
        }
        if (sum < 0) sum = 0;
    }
    for(int i=ansStart; i<=ansEnd; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    vector<int> arr = {4,3,-8,2,3,-1,0,5,-6};
    int max_sum = KadanesAlgo(arr);
    cout << "Max. Subarray sum : " << max_sum << endl;
    printMaxSumSubArr(arr);

    return 0;
}