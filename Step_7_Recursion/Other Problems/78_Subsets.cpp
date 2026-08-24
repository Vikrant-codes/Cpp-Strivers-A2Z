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

// Recursive Implementation : Time Complexity : O(2^n . L) __ Space Complexity : O(2^n . L)
/*
We can use the standard pick/not-pick recursion for each element to generate all possible subsets.

>> Complexity Analysis
Let,
• n = no. of elements
• L = average length of subsets

-> Time Complexity
The whole recursive subset generation takes O(2^n) time, or we can say that there are 2^n recursive leaf nodes.
These 2^n recursive leaf nodes generates all the possible subsets (2^n subsets).
And each of this subset are added to the result.
Assuming the average length of subset is L, this subset insertion to result vector takes O(L) for each insertion.
Thus, for 2^n subsets, the insertion would take O(2^n . L)
and hence, total time = O(2^n . L)

-> Space Complexity 
The recursion depth is `n`, so the recursive stack space is O(n)
But we are storing the subsets into an output vector.
This vector stores 2^n subsets.
Considering average subset length is `L`, the space required for output vector is O(2^n . L)

Thus, auxiliary space considering the output vector is : O(2^n . L)
without considering the output vector, O(n)
*/

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