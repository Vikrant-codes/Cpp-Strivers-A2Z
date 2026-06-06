/*
Leetcode - 2574. Left and Right Sum Differences : Easy

You are given a 0-indexed integer array nums of size n.
Define two arrays leftSum and rightSum where:
- leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
- rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.
Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

Examples :-

Input: nums = [10,4,8,3] __ Output: [15,1,11,22]
Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].

Input: nums = [1] __ Output: [0]
Explanation: The array leftSum is [0] and the array rightSum is [0].
The array answer is [|0 - 0|] = [0].

Constraints :-
- 1 <= nums.length <= 1000
- 1 <= nums[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(3*n) __ Space Complexity : O(2*n)
vector<int> leftRightDifference(vector<int>& nums) {
    int n = nums.size();

    vector<int> leftSumArr(n);
    int leftSum = 0;
    for (int i = 0; i < n; i++) {
        leftSumArr[i] = leftSum;
        leftSum += nums[i];
    }

    vector<int> rightSumArr(n);
    int rightSum = 0;
    for (int i = n-1; i >= 0; i--) {
        rightSumArr[i] = rightSum;
        rightSum += nums[i];
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = abs(leftSumArr[i] - rightSumArr[i]);
    
    return ans;
}

// Optimal Approach : Time Complexity : O(2*n) __ Space Complexity : O(1)
vector<int> leftRightDifference(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);

    int sum = 0;            // total Sum
    for (int x : nums) 
        sum += x;
    
    int leftSum = 0, rightSum = sum;
    
    for (int i = 0; i < n; i++) {
        rightSum -= nums[i];
        ans[i] = abs(leftSum - rightSum);
        leftSum += nums[i];
    }

    return ans;
}

int main() {
    return 0;
}