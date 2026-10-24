/*
Leetcode - 1752. Check if Array Is Sorted and Rotated : Easy

Given an array nums, return true if the array was originally sorted in non-decreasing order, 
then rotated some number of positions (including zero). Otherwise, return false.

There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that 
B[i] == A[(i+x) % A.length] for every valid index i.

Examples :-

Input: nums = [3,4,5,1,2] __ Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].

Input: nums = [2,1,3,4] __ Output: false
Explanation: There is no sorted array once rotated that can make nums.

Input: nums = [1,2,3] __ Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.

Constraints :-
• 1 <= nums.length <= 100
• 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

Let's try to visualize sorted arrays and sorted & rotated arrays to understand the solution.

Think of the array as a 2D co-ordinate plot graph where:
• x-axis = index
• y-axis = value

Now, lets see what does the plotting looks like

>> For sorted arrays
For a sorted (non-decreasing) array, the graph never goes down.

Example: [1, 2, 2, 4, 5]

Index:  0  1  2  3  4
Value:  1  2  2  4  5

5               *
4            *
3  
2      *  *
1   *
  +------------------>
As we move from left to right, every point is at the same height or higher than the previous one.
So there are 0 drops.

>> For sorted & rotated arrays
Suppose we rotate the sorted array.
Sorted:   [1,2,3,4,5]
Rotate:   [3,4,5,1,2]

Plot it:

Value

5             *
4          *
3       *
2                      *
1                   *

    +---------------------------->
        0   1   2   3   4

Notice:
3 → 4 ↑
4 → 5 ↑
5 → 1 ↓ ← one drop
1 → 2 ↑
After the drop, the graph starts increasing again.

This is exactly what rotation does.

Think of rotation as cutting a sorted array at one position and swapping the two parts.
Original: [1 2 | 3 4 5]
After rotation: [3 4 5 | 1 2]
There is only one cutting point, so there can only be one place where a larger value is immediately followed by a smaller value.

>> Why do we compare the last element with the first?
A rotation wraps around.
After reaching the last element, we should continue to the first.
That's why we check:
    nums[i] > nums[(i + 1) % n]

Assume, arr = [3, 4, 1, 2, 5]
Graphically: 
5                *
4        *
3     *
2             *
1          *

The graph goes -> up -> down -> up -> up
If we don't consider the comparison of last element (5) with first (3), 
we would consider the drop count to be 1, and assume that the array is sorted and rotated,
but this would be wrong, as [3, 4, 1, 2, 5] is not sorted & rotated.
So, we need to consider the comparison of last element with first as well and count the drops accordingly.

>> Why can't there be two drops?
Consider : [3,4,1,5,2]
Comparisons:
3 -> 4  ↑
4 -> 1  ↓   (drop #1)
1 -> 5  ↑
5 -> 2  ↓   (drop #2)
2 -> 3  ↑

Graphically:
5               *
4        *
3     *
2                    *
1          *

The graph goes : up -> down -> up -> down
There are two valleys.
A sorted array, after one rotation, is just one increasing sequence that has been cut once.
Two drops would mean you would need two cuts, which is impossible with a single rotation.

>> Another way to think about it
Imagine the sorted array is a circular ring:
1 -> 2 -> 3 -> 4 -> 5
^                   |
|___________________|
Walking around the ring:
- values always increase,
- except when you go from the largest element back to the smallest element.
There is exactly one place where the value decreases.

Rotation simply changes where you start walking on this ring.
No matter where you start, you'll encounter that decreasing edge at most once.

>> Approach 
So, we just need to check consecutive pair elements (arr[i] & arr[(i + 1) % n]), and count the drops.
For the array to be sorted & rotated, the drop count must be smaller than 2.
We use arr[(i + 1) % n] because we need to compare last element with the first as well
*/
bool check1(vector<int>& nums) {
    int n = nums.size();
    int drop = 0;

    for (int i=0; i<n; i++) {
        if (nums[i] > nums[(i + 1) % n])
            drop++;
    }

    return drop <= 1;
}

// Early exit condition: if while traversing, the drop count exceeds 1, we can directly return false
bool check(vector<int>& nums) {
    int n = nums.size();
    int drop = 0;

    for(int i=0; i<n; i++){
        if(nums[i] > nums[(i+1)%n]) 
            drop++;

        if(drop>1) 
            return false;
    }

    return true;
}

int main() {
    return 0;
}