/*
Leetcode - 896. Monotonic Array : Easy

An array is monotonic if it is either monotone increasing or monotone decreasing.
An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. 
An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
Given an integer array nums, return true if the given array is monotonic, or false otherwise.

Examples :-

Input: nums = [1,2,2,3] __ Output: true
Input: nums = [6,5,4,4] __ Output: true
Input: nums = [1,3,2] __ Output: false

Constraints :-
1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
>> Intuition 
An array is considered monotonic if it is either monotone increasing or decreasing.
So, we use two helper functions :-
    - isIncreasing :- returns true if the array is monotone increasing (not strictly increasing)
    - isDecreasing :- returns true if the array is monotone decreasing (not strictly decreasing)
If any of the function returns true, it means the array is monotonic.
So, we just need to return the value of isIncreasing(nums) || isDecreasing(nums).

If the array is non-monotonic, ex -> [1, 2, 3, 2, 1], then both isIncreasing & isDecreasing functions would return false.
*/
bool isIncreasing(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) 
        if (nums[i] < nums[i-1])
            return false;
    return true;
}

bool isDecreasing(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) 
        if (nums[i] > nums[i-1])
            return false;
    return true;
}

bool isMonotonicNaive(vector<int>& nums) {
    return isIncreasing(nums) || isDecreasing(nums);
}

// Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)

/*
Approach 1 — “Validity Checking Approach”

💡 Intuition
A monotonic array must satisfy at least one of these conditions throughout the entire traversal:
- Non-decreasing → every element ≤ next element
- Non-increasing → every element ≥ next element
we assume both possibilities are valid initially and eliminate them whenever a violation is found.

- If we ever see nums[i] > nums[i+1], then the array cannot be non-decreasing → set inc = false
- If we ever see nums[i] < nums[i+1], then the array cannot be non-increasing → set dec = false

At the end:
- If either inc or dec is still true → array is monotonic
- If both become false → array is not monotonic

⚙️ Algorithm
1. Initialize:
    -- inc = true → assume array is non-decreasing
    -- dec = true → assume array is non-increasing
2. Traverse the array:
    -- If nums[i] > nums[i+1] → violates increasing order → inc = false
    -- Else if nums[i] < nums[i+1] → violates decreasing order → dec = false
3. After traversal:
    -- If either condition still survives (inc || dec) → return true
    -- Otherwise return false

📌 Equal Elements
nums[i] == nums[i+1] does not affect either flag because equal elements are valid in both non-decreasing and non-increasing arrays.
*/
bool isMonotonic1(vector<int>& nums) {
    int n = nums.size();
    bool inc = true, dec = true;

    for (int i = 0; i < n-1; i++) {
        if (nums[i] > nums[i+1]) inc = false;
        else if (nums[i] < nums[i+1]) dec = false;
    } 

    return inc || dec;
}

/*
Approach 2 — “Pattern Detection Approach”
💡 Intuition
An array is monotonic if it is either:
- Entirely non-decreasing (each element ≤ next), or
- Entirely non-increasing (each element ≥ next).

We check if increasing or decreasing pattern exist for any of the consecutive pair.
If the array contains both increasing & decreasing pattern consecutive pairs, this means the array isn't monotonic,
since, the monotonic array can only have either increasing pattern or decreasing pattern.

⚙️ Algorithm
1. Initialize two boolean flags:
    -- inc → becomes true if any nums[i] < nums[i+1], i.e., if any consecutive pair is increasing
    -- dec → becomes true if any nums[i] > nums[i+1], i.e., if any consecutive pair is decreasing
2. Traverse the array once and update the flags.
3. If both inc and dec become true at any point → not monotonic → return false.
4. Otherwise → monotonic → return true.

<< Equal condition (nums[i]==nums[i+1]) isn't considered because equal elements are both montonic increasing/dereasing >>
*/
bool isMonotonic2(vector<int>& nums) {
    int n = nums.size();
    bool dec = 0, inc = 0;

    for (int i=0; i<n-1; i++) {
        if (nums[i] < nums[i+1]) inc = 1;
        else if (nums[i] > nums[i+1]) dec = 1;

        if (inc && dec) return false;
    }

    return true;
}

/*
Approach 1:- 
This initially consider the array to be both increasing and decreasing (both falgs true) and then 
changes the flag if any violation is found. 
If we find any pair which is not non-increasing, it means increasing must become false.
Similarly, if we find any pair which is not non-decreasing, it means decreasing must become false.
Now, for a monotonic array, the array can either be non-increasing or non-decreasing.
So, for the monotonic array, one of the two flags must be true.

The approach is implemented in such a way that inc becomes false if the array is not non-decreasing 
and dec becomes false if the array is not non-increasing.
We just need to return true for monotonic if any of the two flags (inc or dec) is true.

Approach 2:-
We don't consider the whole array state to be increasing or decreasing here.
For a monotonic array, it must either have all non-decreasing (increasing) consecutive pairs
or all non-increasing (decreasing) consecutive pairs.
We check for the presence of these pairs.
inc represents the presence of increasing (non-decreasing pair) i.e., pair such that nums[i] < nums[i+1].
dec represents the presence of decreasing (non-increasing pair) i.e., pair such that nums[i] > nums[i+1].
Initially, both inc & dec are false and these are changed to true once their respective patterns are found.
Now, if the array contains both type of pairs, it means the array is not monotonic, 
since monotonic array should only either contain all increasing pairs or all decreasing pairs.
So, for this approach, the two flags must not become true. If both flags become true then the array is not monotonic.
*/

int main() {

    return 0;
}