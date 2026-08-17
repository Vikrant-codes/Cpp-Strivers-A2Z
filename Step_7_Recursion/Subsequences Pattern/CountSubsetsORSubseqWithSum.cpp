// Count all subsequences with sum K
/*
Problem Statement: 
Given an array nums and an integer k.
Return the number of non-empty subsequences of nums such that the sum of all elements in the subsequence is equal to k.
*/

// GFG - Count Subsets with Sum : Medium
/*
GFG - Count Subsets with Sum : Medium

Given an array arr of non-negative integers and an integer target, 
the task is to count all subsets of the array whose sum is equal to the given target.

Examples :-

Input: arr[] = [5, 2, 3, 10, 6, 8], target = 10
Output: 3
Explanation: The subsets {5, 2, 3}, {2, 8}, and {10} sum up to the target 10.

Input: arr[] = [2, 5, 1, 4, 3], target = 10
Output: 3
Explanation: The subsets {2, 1, 4, 3}, {5, 1, 4}, and {2, 5, 3} sum up to the target 10.

Input: arr[] = [5, 7, 8], target = 3
Output: 0
Explanation: There are no subsets of the array that sum up to the target 3.

Input: arr[] = [35, 2, 8, 22], target = 0
Output: 1
Explanation: The empty subset is the only subset with a sum of 0.

Constraints :-
• 1 ≤ arr.size() ≤ 10^3
• 0 ≤ arr[i] ≤ 10^3
• 0 ≤ target ≤ 10^3
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach: Time Complexity : O(2^n) __ Space Complexity : O(n)

// By maintaining a current subsequence sum variable
int countSubsequences(vector<int>& arr, int k, int i, int sum) {
    if (i == arr.size())
        return sum == k ? 1 : 0;

    return countSubsequences(arr, k, i + 1, sum + arr[i]) + countSubsequences(arr, k, i + 1, sum);
}

// Without using an extra variable to store sum
int countSubsequences2(vector<int>& arr, int k, int i) {
    if (i == arr.size())
        return k == 0 ? 1 : 0;
            
    return countSubsequences2(arr, k - arr[i], i + 1) + countSubsequences2(arr, k, i + 1);
}

int countSubseqWithSum(vector<int>& arr, int k) {
    return countSubsequences2(arr, k, 0);
}

// ⚠️ This solution is still not optimal/expected approach for the problem since it takes exponential time O(2^n)
// Due to this, the solution gives TLE on submission
// ✅ The expected approach for this problem uses DP (Dynamic Programming) concept

int main() {
    vector<int> arr = {1, 3, 2, 0};
    int k = 6;

    cout << countSubseqWithSum(arr, k);

    return 0;
}