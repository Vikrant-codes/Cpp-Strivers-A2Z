/*
Leetcode - 643. Maximum Average Subarray I : Easy

You are given an integer array nums consisting of n elements, and an integer k.
Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. 
Any answer with a calculation error less than 10-5 will be accepted.

Examples :-

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Input: nums = [5], k = 1
Output: 5.00000

Constraints :-
• n == nums.length
• 1 <= k <= n <= 10^5
• -10^4 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

double findMaxAverage(vector<int>& nums, int k) {
    int n = nums.size();

    int sum = 0;
    
    for (int i = 0; i < k; i++) 
        sum += nums[i];
    
    int maxSum = sum;
    int i = 0;

    for (int j = k; j < n; j++) {
        sum = sum - nums[i] + nums[j];
        i++;

        if (sum > maxSum)
            maxSum = sum;
    }

    return (double (maxSum) / k);
}

double findMaxAverage2(vector<int>& nums, int k) {
    int n = nums.size();

    // Sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++)
        windowSum += nums[i];
    
    int maxSum = windowSum;     // Max window sum (max subarry sum of size k)

    for (int i = k; i < n; i++) {
        // Add the new element & remove the element leaving the window
        windowSum += nums[i] - nums[i-k];

        maxSum = max(maxSum, windowSum);
    }

    return (double (maxSum) / k);
}

int main() {
    return 0;
}