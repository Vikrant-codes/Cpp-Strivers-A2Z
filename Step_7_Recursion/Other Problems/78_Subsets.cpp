/*
Leetcode - 78. Subsets : Medium

Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Examples :-

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Input: nums = [0]
Output: [[],[0]]

Constraints :-
• 1 <= nums.length <= 10
• -10 <= nums[i] <= 10
• All the numbers of nums are unique.
*/

#include <bits/stdc++.h>
using namespace std;

void recurseSubsets(vector<int>& nums, int ind, vector<int>& ds, vector<vector<int>>& powerSet) {
    if (ind == nums.size()) {
        powerSet.push_back(ds);
        return;
    }

    ds.push_back(nums[ind]);
    recurseSubsets(nums, ind + 1, ds, powerSet);

    ds.pop_back();
    recurseSubsets(nums, ind + 1, ds, powerSet);
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> powerSet;

    vector<int> ds = {};
    recurseSubsets(nums, 0, ds, powerSet);

    return powerSet;
}

int main() {
    return 0;
}