#include <bits/stdc++.h>
using namespace std;

/*
TUF - 1004. Count all subsequences with sum K

Given an array nums and an integer k.
Return the number of non-empty subsequences of nums such that the sum of all elements in the subsequence is equal to k.

Examples :-

Input : nums = [4, 9, 2, 5, 1] , k = 10
Output : 2
Explanation : The possible subsets with sum k are [9, 1] , [4, 5, 1].

Input : nums = [4, 2, 10, 5, 1, 3] , k = 5
Output : 3
Explanation : The possible subsets with sum k are [4, 1] , [2, 3] , [5].

Constraints :-
• 1 <= nums.length <= 20
• 1 <= nums[i] <= 100
• 1 <= k <= 2000
*/

// Recursive Approach (Backtracking): Time Complexity : O(2^n) __ Space Complexity : O(n)

// By maintaining a current subsequence sum variable
int countSubseq(vector<int>& nums, int k, int sum, int ind) {
    if (ind == nums.size()) 
        return sum == k ? 1 : 0;

    // the array don't have negatives or 0, so we can return the moment sum becomes `k`
    if (sum == k) return 1;  
    // this early return won't work when array have `0` or -ves   
    
    // if sum has exceeded `k`, adding further elements can't make the sum `k` since -ves are not present, so return 0
    if (sum > k) return 0;
    
    return countSubseq(nums, k, sum + nums[ind], ind + 1) + countSubseq(nums, k, sum, ind + 1);
}

// Without using an extra variable to store sum
int countSubseq(vector<int>& nums, int k, int ind) {
    if (ind == nums.size()) 
        return k == 0 ? 1 : 0;

    if (k == 0) return 1;
    if (k < 0) return 0;
    
    return countSubseq(nums, k - nums[ind], ind + 1) + countSubseq(nums, k, ind + 1);
}

int countSubsequenceWithTargetSum(vector<int>& nums, int k){
    // return countSubseq(nums, k, 0, 0);
	return countSubseq(nums, k, 0);
}

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

// This GFG problem is essentially same but has larger constraints

int count(vector<int>& arr, int k, int i) {
    if (i == arr.size())
        return k == 0 ? 1 : 0;
            
    // if (k == 0) return 1;
    // we can't use this early return since array can have 0, so cases like [1, 2], [1, 2, 0] could be both valid when k = 3

    if (k < 0) return 0;
    // since array don't have -ves, we can keep this early return statement
    
    return count(arr, k - arr[i], i + 1) + count(arr, k, i + 1);
}

int countSubseqWithSum(vector<int>& arr, int k) {
    return count(arr, k, 0);
}

// ⚠️ This backtracking solution is not the optimal/expected approach for the GFG variant, since it has larger constraints
// Due to this, this solution will give TLE when submitted on GFG
// ✅ The expected approach for this problem uses DP (Dynamic Programming) concept

int main() {
    return 0;
}