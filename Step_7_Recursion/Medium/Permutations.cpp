/*
Leetcode - 46. Permutations : Medium

Given an array nums of distinct integers, return all the possible permutations. 
A permutation is a rearrangement of all the elements of an array.

You can return the answer in any order. 

Examples :-

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Input: nums = [1]
Output: [[1]]

Constraints :-
• 1 <= nums.length <= 6
• -10 <= nums[i] <= 10
• All the integers of nums are unique.
*/

#include<bits/stdc++.h>
using namespace std;

// Approach - 1 : Time Complexity : O(n × n!) __ Space Complexity : O(3n)
/*
(My own Approach) Striver's Approach 1

>> Intuition
To get all the permutations, we need to generate all the possible orders of the elements.
We can try to manually create the permutations by placing the elements one position at a time and then 
recursing for the different set of possibilities to explore all the recursive branches.

We can start by considering the 0th index and try placing every element at this position.
Once an element is placed at index 0, we move to the next index. 
At index 1, we can again try placing every element except the element that was already placed at index 0.
Similarly, when we move to index 2, we try placing all the remaining elements, 
except the two elements that have already been placed at indices 0 and 1.

We continue this process until all positions have been filled.

Since every choice can lead to multiple further choices, we can use recursive calls to explore all these possible branches.

? The main issue is: how do we efficiently know which elements have already been used?
To solve this, we maintain a picked array that tells us whether the element at each index 
has already been picked for the current permutation.

For example, while deciding the element for index 0, suppose we pick the element at index 2. 
We mark that element as picked.

We then recursively move on to the next position. 
While choosing an element for that position, we only consider elements whose corresponding picked value is false.

Once we finish exploring all permutations that can be formed using that choice, 
we undo the choice by marking the element as unpicked. 
This allows the element to be considered again in another branch.

So the overall idea is:
Pick an unused element → recursively fill the remaining positions → undo the choice → try the next unused element.

This allows us to systematically explore every possible ordering of the elements 
without using an element more than once in the same permutation.

>> Complexity Analysis
For n elements, there are exactly: n! (n factorial) possible permutations.

For each permutation, we need O(n) time to construct/store it.
Therefore:
Time Complexity: O(n × n!)
There is also the work of scanning the n elements at every recursion level, but the overall complexity remains O(n × n!).

Auxiliary Space:
The recursion depth is n, the current permutation contains n elements, and the picked array contains n elements.
Thus, auxiliary space: O(n) + O(n) + O(n) = O(3n)
This excludes the space required to store the output.

Output Space:
There are n! permutations, each containing n elements:O(n x n!)
So, including the result: O(n × n!) in total space.
*/

// My implementation
void getPermutations(vector<int>& nums, vector<bool>& picked, vector<int>& curr, vector<vector<int>>& result) {
    if (curr.size() == nums.size()) {
        result.push_back(curr);
        return;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (picked[i] == true) 
            continue;
        
        curr.push_back(nums[i]);
        picked[i] = true;
    
        getPermutations(nums, picked, curr, result);
    
        curr.pop_back();
        picked[i] = false;
    }
}

vector<vector<int>> permute1(vector<int>& nums) {
    vector<bool> picked(nums.size());
    vector<int> curr;
    vector<vector<int>> result;
    
    getPermutations(nums, picked, curr, result);
    
    return result;
}

// Striver's implementation
void recurPermute(vector<int>& ds, vector<int>& nums, vector<vector<int>>& ans, int freq[]) {
    if (ds.size() == nums.size()) {
        ans.push_back(ds);
        return;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (!freq[i]) {
            ds.push_back(nums[i]);
            freq[i] = 1;
            recurPermute(ds, nums, ans, freq);
            freq[i] = 0;
            ds.pop_back();
        }
    }
}

vector<vector<int>> permute2(vector<int>& nums) {
    vector<int> ds;
    vector<vector<int>> ans;
    int freq[nums.size()];
    for(int i = 0; i < nums.size(); i++) freq[i] = 0;
    recurPermute(ds, nums, ans, freq);
    
    return ans;
}

// Optimal Approach : Time Complexity : O(n × n!) __ Space Complexity : O(n)
/*
>> Intuition
To generate all permutations, we can again construct the permutation one position at a time.
At any index ind, we need to decide which element should be placed at this position.
Instead of maintaining a separate picked array, 
we can use the array itself to keep track of which elements are already being used.

Suppose we are currently filling index ind.
All positions before ind have already been fixed, 
so the elements from ind onward are the elements that are still available for selection.
We can try placing each of these remaining elements at position ind.

For example, for [1, 2, 3], when filling index 0, we can:
- Keep 1 at index 0
- Swap 2 into index 0
- Swap 3 into index 0

For each of these choices, we recursively move to ind + 1 and 
repeat the same process for the remaining portion of the array.

The important idea is that the swap itself represents the choice.
Once we swap an element into the current position, that position is considered fixed for the current branch. 
Therefore, in the next recursive call, we only consider elements from the next index onward.

After completely exploring that choice, we undo the swap to restore the array to its previous state. 
This allows us to try the next possible element at the current position.

So the overall approach is:
    Choose an element from the remaining portion → swap it into the current position 
    → recursively generate permutations for the remaining positions → undo the swap → try the next element.

This approach achieves the same backtracking idea as the picked-array approach, 
but here the array itself maintains the state, so we don't need a separate picked array.

>> Complexity Analysis
There are n! possible permutations.
For every permutation, we eventually store n elements in the result.

Therefore:
Time Complexity: O(n x n!)
The recursive generation itself involves some additional work at each level, 
but the dominant cost is generating and storing all n! permutations.

Auxiliary Space:
The recursion goes n levels deep: O(n)
The swaps are performed in-place, so there is no additional picked array or separate copy of the permutation required.

Output Space:
There are n! permutations, each containing n elements: O(n × n!)
So including the output, total space is: O(n × n!)
*/

void getPermute(vector<int>& nums, int ind, vector<vector<int>>& ans) {
    if (ind == nums.size()) {
        ans.push_back(nums);
        return;
    }

    for (int i = ind; i < nums.size(); i++) {
        swap(nums[ind], nums[i]);
        
        getPermute(nums, ind + 1, ans);

        swap(nums[ind], nums[i]);       // undo change
    }
}

vector<vector<int>> permute3(vector<int>& nums) {
    vector<vector<int>> ans;
    getPermute(nums, 0, ans);
    return ans;
}

int main() {
    return 0;
}