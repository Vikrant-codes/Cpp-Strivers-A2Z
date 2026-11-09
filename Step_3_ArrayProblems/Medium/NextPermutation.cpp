/*
Leetcode - 31. Next Permutation : Medium

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
For example, for arr = [1, 2, 3], the following are all the permutations of arr: 
[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].

The next permutation of an array of integers is the next lexicographically greater permutation of its integer. 
More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, 
then the next permutation of that array is the permutation that follows it in the sorted container. 
If such arrangement is not possible, the array must be rearranged as the lowest possible order 
(i.e., sorted in ascending order).
Examples:
The next permutation of arr = [1, 2, 3] is [1, 3, 2].
The next permutation of arr = [2, 3, 1] is [3, 1, 2].
The next permutation of arr = [3, 2, 1] is [1, 2, 3] because [3, 2, 1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

Examples :-

Input: nums = [1,2,3] __ Output: [1,3,2]

Input: nums = [3,2,1] __ Output: [1,2,3]

Input: nums = [1,1,5] __ Output: [1,5,1]

Constraints :-
• 1 <= nums.length <= 100
• 0 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach
/*
>> Intuition
We can generate all possible permutations of the given array in lexicographical order, using recursion (backtracking).
Once all permutations are generated, we linearly search for the current permutation and 
return the permutation immediately following it.
If the current permutation is the last one, we return the first permutation.

Complexity Analysis:
- Time: O(n × n!) — There are at most n! permutations, and generating each permutation takes O(n) time. 
  Searching for the current permutation also takes O(n × n!) in the worst case.
- Space: O(n × n!) — To store all permutations. Recursion also requires O(n) stack space.

The time and space complexity for this approach are too high make this approach compeletely infeasible.
*/


// Optimal Approach: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

The key is to find the smallest possible rearrangement that is strictly greater than the current permutation.

Let's understand this using: nums = [2, 1, 5, 4, 3, 0, 0]
We can solve this in three steps.

-- Step 1: Find the Breakpoint

Traverse the array from right to left and find the first index i such that: 
    nums[i] < nums[i+1]

-> Why do we do this?
We are looking for the position where we can make the smallest possible increase in the current permutation.
Notice that the suffix to the right of this position is in descending order.

For our example:
[2, 1, 5, 4, 3, 0, 0]
    ^
  Breakpoint
Here, 1 is the breakpoint because 1 < 5.

-> Why do we search from right to left?
The suffix is already in descending order, which means it represents the largest possible arrangement of those elements.
We cannot make the permutation greater by rearranging only this suffix. We must change an element before it.
To get the next permutation rather than some much larger permutation, we want to change the rightmost possible element. 
Hence, we find the first breakpoint from the right.

-- Step 2: Find the Next Greater Element and Swap

Once we find the breakpoint, we need to replace it with the smallest element that is strictly greater than it.
Since the suffix is in descending order, we traverse from the right and find the first element greater than nums[i].
For our example:
[2, 1, 5, 4, 3, 0, 0]
    ^           ^
    1           3
The first element from the right that is greater than 1 is 3.

Swap them: [2, 3, 5, 4, 1, 0, 0]

-> Why the first greater element from the right?
Because the suffix is in descending order, the first element greater than the breakpoint is the 
smallest available element that can replace it while making the permutation greater.
This ensures that we increase the permutation by the smallest possible amount at this position.

-- Step 3: Reverse the Suffix

After swapping, we need to make the remaining suffix as small as possible.
Remember, our objective is to find the next permutation, not just any greater permutation.
The suffix was originally in descending order. After the swap, it is still in descending order.
To obtain the smallest possible arrangement of that suffix, we would need to sort the suffix elements.
Since, the suffix is already in decreasing order, we can simply reverse it into ascending order.

Before reversing:
[2, 3, 5, 4, 1, 0, 0]
       └───────────┘
       Descending

After reversing: [2, 3, 0, 0, 1, 4, 5]

The resulting array is the immediate next lexicographical permutation.

>> What if the array is arranged in the largest permutation order , i.e., arranged in decreasing (non-increasing) order ?

Consider: [5, 4, 3, 2, 1]
The entire array is in non-increasing (descending) order, and thus, 
is already the largest possible permutation of the given elements.

Therefore, its next permutation should be the smallest possible permutation, 
which is the array sorted in non-decreasing (ascending) order.

Since the array is already in descending order, we can simply reverse it to obtain the smallest permutation.
[5, 4, 3, 2, 1] → [1, 2, 3, 4, 5]

For such cases, no breakpoint will be found as the entire array is in non-increasing (descending) order.
So, if breakpoint isn't found, we can simply reverse the entire array to get the next permutation (smallest one).

>> Complexity Analysis

-> Time: O(n)
- Finding the breakpoint takes O(n).
- Finding the next greater element takes O(n).
- Reversing the suffix takes O(n).

-> Space: O(1) — All operations are performed in-place.
*/

void nextPermutation1(vector<int>& nums) {
    int n = nums.size();
    int ind = -1;

    // Step 1: Find the breakpoint
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            ind = i;
            break;
        }
    }
    
    // if breakpoint doesn't exist, this means nums is already arranged in largest permutation order.
    // so, we reverse it to get the smallest permutation order (sorted order), and return
    if (ind == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }
    
    // Step 2: Find the next greater element and swap
    for (int i = n - 1; i > ind; i--) {
        if (nums[i] > nums[ind]) {
            swap(nums[i], nums[ind]);
            break;
        }
    }

    // Step 3: Reverse the suffix
    reverse(nums.begin() + ind + 1, nums.end());
}

void nextPermutation2(vector<int>& nums) {
    int n = nums.size();
    int idx = -1;

    // Step 1: Find the breakpoint
    for(int i = n - 2; i >= 0; i--) {
        if(nums[i] < nums[i + 1]) {
            idx = i;
            break;
        }
    }

    // Step 2: Find the next greater element and swap
    if(idx != -1) {
        for(int i = n - 1; i > idx; i--) {
            if(nums[i] > nums[idx]) {
                swap(nums[i], nums[idx]);
                break;
            }
        }
    }

    // Step 3: Reverse the suffix
    reverse(nums.begin() + idx + 1, nums.end());
}

// Using C++ STL built-in method
/*
`next_permutation` is a built-in function in the C++ Standard Template Library (<algorithm>) 
that rearranges elements into the lexicographically next greater permutation. 
If it finds one, it returns true; if none exists, it returns false.

If the array is already sorted in descending order (e.g., {3, 2, 1}), it represents the largest possible permutation. 
In this case:
- next_permutation rearranges the array back to the smallest (ascending) order (i.e., {1, 2, 3}).
- It returns false, which can be used to terminate loops.
*/
void nextPermutation(vector<int>& nums) {
    next_permutation(nums.begin(), nums.end());
}

int main() {
    return 0;
}