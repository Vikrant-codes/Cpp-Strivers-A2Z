/*
Leetcode - 167. Two Sum II - Input Array Is Sorted : Medium

You are given a 1-indexed array of integers numbers that is already sorted in non-decreasing order.

Find two numbers such that they add up to a specific target number. 
Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers index1 and index2 as an integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

Your solution must use only constant extra space.

Examples :-

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].

Constraints :-
• 2 <= numbers.length <= 3 * 10^4
• -1000 <= numbers[i] <= 1000
• numbers is sorted in non-decreasing order.
• -1000 <= target <= 1000
• The tests are generated such that there is exactly one solution.
*/

#include<bits/stdc++.h>
using namespace std;

/*
The problem is quite similar to LeetCode 1: Two Sum, with two key differences:
- The array is sorted in non-decreasing order.
- The array uses 1-based indexing, so we return {i + 1, j + 1}.

We could use the brute-force or hash-table approaches from LeetCode 1, 
but this problem requires constant extra space, so the hash-table approach doesn't satisfy the requirement.
Instead, we can take advantage of the sorted array using the Two Pointers approach.
*/

// Optimal & Expected Approach (Two Pointers): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
Since the array is sorted in non-decreasing order, 
we can use two pointers to find the target without checking every possible pair.

Start with one pointer i at the beginning (smallest element) and another pointer j at the end (largest element). 
Calculate their sum and compare it with the target.
- If sum == target: We have found the required pair, so return their 1-based indices.
- If sum > target: The sum is too large, so move j left to a smaller element, reducing the sum.
- If sum < target: The sum is too small, so move i right to a larger element, increasing the sum.

Repeat until the target is found. 
The key idea is that the sorted order helps us decide which pointer to move, eliminating the need to check every pair.

Complexity Analysis:
-> Time: O(n) — The pointers move inward, and each element is visited at most once.
-> Space: O(1) — Only a constant amount of extra space is used.
*/
vector<int> twoSum(vector<int>& numbers, int target) {
    int n = numbers.size();
    int i = 0, j = n - 1;

    while (i < j) {
        int sum = numbers[i] + numbers[j];
    
        if (sum == target)
            return {i + 1, j + 1};      // return indices considering 1-based indexing
    
        else if (sum > target) j--;     // move right pointer to reduce the overall sum
        
        else i++;                       // move left pointer to increase the overall sum
    }
    
    return {-1, -1};   // this will never execute, since testcases are guaranteed to always have solution
}

int main() {
    return 0;
}