/*
Leetcode - 1. Two Sum : Easy

You are given an array of integers nums and an integer target, 
return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, 
and you may not use the same element twice.

You can return the answer in any order. 

Examples :-

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation:
The sum of nums[0] and nums[1] is 2 + 7 = 9, which equals the target. Therefore, the indices [0, 1] are returned.

Input: nums = [3,2,4], target = 6
Output: [1,2]
Explanation:
The sum of nums[1] and nums[2] is 2 + 4 = 6, which equals the target. Therefore, the indices [1, 2] are returned.

Input: nums = [3,3], target = 6
Output: [0,1]
Explanation:
The sum of nums[0] and nums[1] is 3 + 3 = 6, which equals the target. Therefore, the indices [0, 1] are returned.

Constraints :-
• 2 <= nums.length <= 10^4
• -10^9 <= nums[i] <= 10^9
• -10^9 <= target <= 10^9
• Only one valid answer exists.

Follow-up: Can you come up with an algorithm that is less than O(n²) time complexity?
*/

#include<bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
Check every possible pair of elements using two nested loops. 
For each pair, if their sum equals target, return their indices. 
Start j from i + 1 to avoid reusing the same element or checking duplicate pairs.

>> Complexity Analysis
-> Time complexity: O(n²) — We check all possible pairs in the worst case.
-> Space complexity: O(1) — Only a constant amount of extra space is used.
*/
vector<int> twoSumBrute(vector<int>& nums, int target) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }

    return {-1, -1};        // dummy return, if no solution is found
}

// Two-pass Hash Table Approach: Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Approach (Two-pass Hash Table)

To improve our runtime complexity, we need a more efficient way to check if the complement exists in the array. 
If the complement exists, we need to get its index. 
What is the best way to maintain a mapping of each element in the array to its index? A hash table.

We can reduce the lookup time from O(n) to O(1) by trading space for speed. 
A hash table is well suited for this purpose because it supports fast lookup in near constant time. 
I say "near" because if a collision occurred, a lookup could degenerate to O(n) time. 
However, lookup in a hash table should be amortized O(1) time as long as the hash function was chosen carefully.

>> Algorithm

First, store each element and its index in a hash map for quick lookup.
Then, traverse the array again. 
For each element nums[i], calculate its complement, target - nums[i]. 
If the complement exists in the map and its index is different from i, we have found the required pair.

Note: The condition hash[comp] != i ensures we don't use the same element twice. 
Since the map stores only one index per value, duplicate values are handled by retaining the last occurrence.

>> Complexity Analysis

-> Time complexity: O(2n) average — Two separate traversals, with average O(1) hash map operations.
-> Space complexity: O(n) — The hash map can store up to n elements.
*/
vector<int> twoSumBetter(vector<int>& nums, int target) {
    unordered_map<int, int> hash;

    for (int i = 0; i < nums.size(); i++) {
        hash[nums[i]] = i;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        int comp = target - nums[i];        // complement of nums[i], for target sum
        // check if complement exists, if it does exist, ensure that its index is not equal to i itself.
        if (hash.find(comp) != hash.end() && hash[comp] != i) {
            return {i, hash[comp]};
        }
    }

    return {};          // If no valid pair is found, return an empty vector
}

// Optimal Approach (One Pass Hash Table): Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Optimal Approach: One Pass Hash Table

We can further optimize the two-pass approach by checking for the complement 
and inserting elements into the hash table in a single traversal.
As we iterate through the array, 
we check whether the current element's complement (target - nums[i]) already exists in the hash table. 
If it does, we have found the pair and can immediately return both indices. 
Otherwise, we insert the current element and its index into the hash table.

Note: We check for the complement before inserting the current element, ensuring we never use the same element twice.

>> Complexity Analysis:
-> Time: O(n) average — We traverse the array once, with average O(1) hash table lookups and insertions.
-> Space: O(n) — In the worst case, the hash table stores up to n elements.
*/
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash;

    for (int i = 0; i < nums.size(); i++) {
        int comp = target - nums[i];        // complement of nums[i], for target sum
    
        // check if complement already exists in the hash table
        if (hash.find(comp) != hash.end()) {
            return {hash[comp], i};         // complement appears before nums[i], so we return {hash[comp], i}
        }
    
        hash[nums[i]] = i;                  // Insert the current element in hash table
    }

    return {};   // Return an empty vector if no solution is found (it is guaranteed a valid solution always exists)
}

int main() {
    return 0;
}