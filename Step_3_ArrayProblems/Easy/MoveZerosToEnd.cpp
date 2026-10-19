/*
Leetcode - 283. Move Zeroes : Easy

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
Note that you must do this in-place without making a copy of the array.

Examples :-

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Input: nums = [0]
Output: [0]
 
Constraints :-
• 1 <= nums.length <= 10^4
• -2^31 <= nums[i] <= 2^31 - 1

Follow up: Could you minimize the total number of operations done?
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(2n) __ Space Complexity : O(n)
/*
Intuition: 
Store all non-zero elements in a temporary vector, 
copy them back to the beginning of nums in their original order, 
then fill the remaining positions with zeros.

>> Complexity Analysis:
-> Time: 
    - Storing non-zero elements in temp vector: O(n)
    - Copying elements of temp vector in beginning of nums: O(k), where k = count of non-zero elements
    - Filling remaining positions with zeroes: O(n - k)
    - Total time: O(n) + O(k) + O(n - k) = O(2n)

-> Space: O(n) — The temporary vector can store up to n elements.
*/
void moveZeroesNaive(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> temp;     // temporary vector to store the non-zero elements
    // store all non-zero elements in temp vector
    for (int& x : nums) {
        if (x != 0) {
            temp.push_back(x);
        }
    }

    // place those stored non-zero elements in the starting positions of nums
    int i = 0;
    while (i < temp.size()) {
        nums[i] = temp[i];
        i++;
    }

    // re-write the later positions of nums with zeroes
    while (i < n) {
        nums[i] = 0;
        i++;
    }

    /*
    // copy elements from temp & fill first temp.size() indices of nums
    for (int i = 0; i < temp.size(); i++) 
        nums[i] = temp[i]; 

    // fill rest of the positions with 0
    for (int i = temp.size(); i < n; i++) 
        nums[i] = 0;       
    */
}

// Optimal Approach-1: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
The key observation is that instead of shifting elements or explicitly moving zeros to the end, 
we can swap each non-zero element into the earliest available zero position.

Consider nums = [0, 1, 3, 0, 4, 12].
- First, find the first zero. This is the earliest position that needs to be filled, so j = 0.
- Now scan the array from the next position using i. 
  Whenever we encounter a non-zero element, swap it with the element at j.

Let's see how this works:

Intially j = 0.
nums = [0, 1, 3, 0, 4, 12]

i starts iterating from index 1 & searches for non-zero element.

i = 1: nums[i] = 1, which is non-zero, so swap nums[i] with nums[j] and increment j.
nums becomes [1, 0, 3, 0, 4, 12]
j has now moved to 1 (as j is incremented from 0 to 1).

i = 2: nums[i] = 3, which is non-zero, so swap nums[i] with nums[j] and increment j.
nums becomes [1, 3, 0, 0, 4, 12]
j has now moved to 2.

i = 3: nums[i] = 0, skip and move to next index

i = 4: nums[i] = 4, which is non-zero, so swap nums[i] with nums[j] and increment j.
nums becomes [1, 3, 4, 0, 0, 12]
j has now moved to 3.

i = 5: nums[i] = 12, which is non-zero, so swap nums[i] with nums[j] and increment j.
nums becomes [1, 3, 4, 12, 0, 0]
j has now moved to 4.

iteration ends.
Final array: [1, 3, 4, 12, 0, 0]

The role of the pointers:
- i searches for the next non-zero element.
- j marks the next position that needs a non-zero element. 
  After a successful swap, j advances because that position is now fixed.
  
Since i encounters non-zero elements from left to right, their relative order is preserved.

>> Complexity Analysis:
-> Time: O(n)
    - Finding the first occurrence index of zero: O(x), where x is the first occurrence index of zero.
    - Iterating & swapping using variable i: O(n - x)
    - Total: O(x) + O(n - x) = O(n)

-> Space: O(1) — In-place modification.
*/
void moveZeroes1(vector<int>& nums) {
    int n = nums.size();
    
    int j = 0;      // first occurrence index of 0
    while (j < n && nums[j] != 0) j++;
    
    // if nums don't have any zeroes, j will become equal to n, we can return in that case (the for loop won't execute anyways)
    if (j == n) return;

    for (int i = j + 1; i < n; i++) {
        if (nums[i] != 0) {
            swap(nums[i], nums[j]); // swap the non-zero element to place it at its correct position
            j++;                    // move the j pointer ahead to mark the position where next non-zero element should come
        }
    }
}

// Optimal Approach-2: Time Complexity : O(n) __ Space Complexity : O(1)
/*
We know that the final array should have all non-zero elements at the beginning
and all zeros at the end, while maintaining the relative order of non-zero elements.

The first non-zero element should be at index 0, the second at index 1, and so on.

So, we consider ind = 0 as the index where the next non-zero element should be placed.

We then iterate through the array, and whenever we find a non-zero element, we swap
it with the element at index ind, placing it in its intended position.

We then increment ind to mark the next position where the next non-zero element
should be placed.

This way, all non-zero elements are moved to the beginning in their original order,
and all zeros naturally end up at the end.

>> Complexity Analysis:
-> Time: O(n)
-> Space: O(1) — In-place modification.
*/
void moveZeroes2(vector<int>& nums) {
    int n = nums.size();
    
    int ind = 0;

    for (int i = 0; i < n; i++) {
        if (nums[i] != 0) {
            swap(nums[i], nums[ind]);
            ind++;
        }
    }
}

int main() {
    return 0;
}