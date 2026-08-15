/*
Leetcode - 561. Array Partition : Easy

Given an integer array nums of 2n integers, 
group these integers into n pairs (a1, b1), (a2, b2), ..., (an, bn) 
such that the sum of min(ai, bi) for all i is maximized. 
Return the maximized sum.

Examples :-

Input: nums = [1,4,3,2] __ Output: 4
Explanation: All possible pairings (ignoring the ordering of elements) are:
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
So the maximum possible sum is 4.

Input: nums = [6,2,6,5,1,2] __ Output: 9
Explanation: The optimal pairing is (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6, 6) = 1 + 2 + 6 = 9.

Constraints :-
• 1 <= n <= 10^4
• nums.length == 2 * n
• -10^4 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Greedy + Sorting) : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
We want to group the 2n integers into n pairs, such that the sum of minimum of each pair is maximized.

Since, we are taking minimum of each pair, so the greater value among the pair will be sacrificed due to smaller one.
Ex- nums = [1, 4, 3, 2]

The possible pairs can be formed in the following 3 ways -
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4

As we observe the greater values are being left out and smaller ones are being taken, but we want to maximize our sum.
So, we must think of a way to select greater values when taking the min.
The larger array elements can only be picked only when they are paired with elements with more large values.
Like, among the pairs, pair (3, 4) gave us 3 a large value.
So, we should group smaller elements together in one pair and larger in second pair.

So, we can sort the array.
sorted_nums = [1, 2, 3, 4]
then we can form groups by picking elements in the sorted order.
pairs = (1, 2), (3, 4).
This way the sum can be maximized.
*/
int arrayPairSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    int res = 0;
    
    for (int i = 0; i < nums.size(); i+=2) 
        res += nums[i];
    
    return res;
}

int main() {
    return 0;
}