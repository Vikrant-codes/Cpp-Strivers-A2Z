/*
Leetcode - 448. Find All Numbers Disappeared in an Array : Easy

Given an array nums of n integers where nums[i] is in the range [1, n], 
return an array of all the integers in the range [1, n] that do not appear in nums.

Examples :-

Input: nums = [4,3,2,7,8,2,3,1] __ Output: [5,6]

Input: nums = [1,1] __ Output: [2]

Constraints :-
- n == nums.length
- 1 <= n <= 10^5
- 1 <= nums[i] <= n

Follow up: Could you do it without extra space and in O(n) runtime? 
You may assume the returned list does not count as extra space.
*/

#include <bits/stdc++.h>
using namespace std;

// Sorting Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
Sorting approach : Idea ->
1. Sort the array
2. After sorting, the array should ideally be : 1, 2, 3, 4, ..., n
3. Any gap in this sequence means a number is missing
4. Traverse the sorted array and find the missing elements from the expected sequence
*/
vector<int> findDisappearedNumbersSort(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<int> ans;

    int expected = 1;
    for (int i = 0; i < n; i++) {
        // skip duplicates
        if (i > 0 && nums[i] == nums[i-1]) 
            continue;

        // fill missing numbers
        while (nums[i] > expected) {
            ans.push_back(expected);
            expected++;
        }

        // move expected forward if matched/found in array
        if (nums[i] == expected) 
            expected++; 
    }

    // if numbers at the end are missing
    while (expected <= n) {
        ans.push_back(expected);
        expected++;
    }

    return ans;
}

// HashArray Approach : Time Complexity : O(n) __ Space Complexity : O(n)
vector<int> findDisappearedNumbersHash(vector<int>& nums) {
    int n = nums.size();
    vector<int> hashArr(n);
    vector<int> ans;

    for (int&x : nums) 
        hashArr[x-1]++;
    
    for (int i=0; i<n; i++)
        if (hashArr[i] == 0) 
            ans.push_back(i+1);
    
    return ans;
}

// Optimal Approach (In-place marking approach - mark by negating) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Optimal approach (in-place, no extra array)
Idea:
|   Mark presence by negating the value at index (nums[i] - 1).

What the problem really gives you ?
You are given very strong constraints:
• Array size = n
• Values are only in the range [1, n]
• Duplicates allowed
• Some numbers missing

>> We want to know about the missing numbers, like for x in range [1, n], whether x was present in array or not.
We earlier used a hashArr to keep track of this presence of integer x in array, 
but can we store this info without extra array ?
Now the question becomes:
| “Can the input array store presence information without losing needed data?”
Answer: Yes — because we don’t need exact values anymore, only presence

>> How can an element mark presence?
Each number x belongs to [1, n]
So it corresponds to index:     ind = x - 1
Now we need a marker to mark the presence of element x at the corresponding index 'ind'.
But if we use a particular number (like 0 or -1) to mark this presence, then the value at that index will be lost.
So, we need a marker such that the value is not lost and we can mark the presence also.
We know that all the array elements are initially +ve, so how about we make the element at the index 'ind' negative.
Changing the sign helps us :-
• The actual value at the index will not be lost since we can take abs(value) to get the value
• When we later traverse the array, then we can check whether some element was missing 
    if it's corresponding index is not marked (i.e. if the corresponding index is still +ve)

>> After marking, when we traverse the array there can be two cases 
• nums[i] < 0 → nums[i] is -ve means it is marked by some corresponding element x → number (i+1) exists in array
• nums[i] > 0 → nums[i] is +ve (not marked), thus the corresponding element is missing → number (i+1) is missing

>> Insert all the missing elements in a ans vector and return that vector

Mental model
Think of the array as a notice board:
• Each index is a slot for a number
• When a number appears, you “cross out” its slot
• At the end, uncrossed slots = missing numbers
The “crossing out” is just negation.
*/
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> ans;
    
    for (int i = 0; i < nums.size(); i++) {
        int ind = abs(nums[i]) - 1;
        if (nums[ind] > 0) 
            nums[ind] *= -1;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) 
            ans.push_back(i+1);
    }

    return ans;
}

int main() {
    return 0;
}