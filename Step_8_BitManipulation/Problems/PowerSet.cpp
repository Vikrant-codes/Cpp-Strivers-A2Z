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

// The power set problem have two solutions -- using Recursion (Backtracking) & Bit Manipulation
// The recursive solution can be found in Recursion module.

// Bit Manipulation Approach: Time Complexity : __ Space Complexity : 
/*
>> Intuition
For an array of size n, each element has two choices: either include it in a subset or exclude it.

Therefore, the total number of subsets is 2^n.

We can use the binary representation of numbers from 0 to 2^n-1 to represent every possible subset.
- If the i-th bit is 1, include nums[i] in the subset.
- If the i-th bit is 0, exclude nums[i].
This works because an n-bit number represents one unique combination of inclusion/exclusion decisions for the n elements.

-> Example: Suppose nums = [1, 2, 3]. 
Since n = 3, there are 2^3 = 8 subsets, represented by the binary numbers 000 through 111.
-------------------------------
| Number | Binary | Subset    |
-------------------------------
| 0	     |  000	  | []        |
| 1	     |  001	  | [1]       |
| 2	     |  010	  | [2]       |
| 3	     |  011	  | [1, 2]    |
| 4	     |  100	  | [3]       |
| 5	     |  101	  | [1, 3]    |
| 6	     |  110	  | [2, 3]    |
| 7	     |  111	  | [1, 2, 3] |
-------------------------------
For example, take num = 5, whose binary representation is 101.
- Bit 0 is 1 → include nums[0] = 1.
- Bit 1 is 0 → exclude nums[1] = 2.
- Bit 2 is 1 → include nums[2] = 3.
The resulting subset is [1, 3].

>> Approach

For a given array of size n, we first calculate the total number of subsets, which is 2^n (using 1 << n).

The binary representations of numbers from 0 to count - 1 represent all possible combinations of 
inclusion/exclusion decisions for the n elements.

We iterate through each number num from 0 to count - 1. 
For each number, we check every index i from 0 to n - 1 to determine whether to include nums[i] in the current subset.

We check whether the i-th bit of num is set using num & (1 << i). 
If the result is nonzero, we include nums[i] in the current subset; otherwise, we exclude it.

After checking all elements, we add the current subset to powerSet. 
Once all bitmasks have been processed, we return powerSet.

>> Complexity analysis

Time: O(n ∙ 2^n)
- There are 2^n possible subsets.
- For each subset, we check all n bits.
- Therefore, the total time complexity is O(n ∙ 2^n).

Space: O(n ∙ 2^n) for the output, since we store all subsets and their elements. 
The auxiliary space used to construct one subset at a time is O(n), excluding the output.

>> Key takeaway: Bitmasking turns each binary number into a set of inclusion/exclusion decisions. 
Enumerating all 2^n bitmasks therefore generates every subset exactly once.
*/
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> powerSet;

    int n = nums.size();

    int count = 1 << n;     // count of total subsets of nums. count = 2 ^ n = (1 << n)

    // Each number from 0 to count-1 represents one subset using its binary bits.
    for (int num = 0; num < count; num++) {
        vector<int> subset;

        // Check the bit corresponding to each array element.
        for (int i = 0; i < n; i++) {
            // If the i-th bit is set, include nums[i].
            if (num & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }

        // Store the subset represented by this bitmask.
        powerSet.push_back(subset);
    }

    return powerSet;
}

int main() {
    return 0;
}