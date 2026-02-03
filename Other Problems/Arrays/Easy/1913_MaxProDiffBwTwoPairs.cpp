/*
Leetcode - 1913. Maximum Product Difference Between Two Pairs : Easy

The product difference between two pairs (a, b) and (c, d) is defined as (a * b) - (c * d).
For example, the product difference between (5, 6) and (2, 7) is (5 * 6) - (2 * 7) = 16.
Given an integer array nums, choose four distinct indices w, x, y, and z such that the product difference between pairs 
(nums[w], nums[x]) and (nums[y], nums[z]) is maximized.
Return the maximum such product difference.

Examples :-

Input: nums = [5,6,2,7,4] __ Output: 34
Explanation: We can choose indices 1 and 3 for the first pair (6, 7) and indices 2 and 4 for the second pair (2, 4).
The product difference is (6 * 7) - (2 * 4) = 34.

Input: nums = [4,2,5,9,7,4,8] __ Output: 64
Explanation: We can choose indices 3 and 6 for the first pair (9, 8) and indices 1 and 5 for the second pair (2, 4).
The product difference is (9 * 8) - (2 * 4) = 64.

Constraints :-
- 4 <= nums.length <= 10^4
- 1 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

/*
✅ Intuition
(The array only has positive elements so there is no complication about negatives forming positive after multiplication)
We want to maximize the product difference of the two pairs. Assume the two pairs are (w,x) & (y,z).
So, our aim is to maximize (w * x) - (y * z). 
To do so we should choose the elements w,x,y,z such that (w * x) is maximum possible and (y * z) is minimum possible.
(w * x) would be maximum when w & x are the two maximum elements of the array,
similarly, (y * z) would be minimum when y & z are the two minimum elements of the array.
In this way, the product difference (w * x) - (y * z) would be maximum possible.
So, we just need to find the two maximum elements (max1 & max2) and two minimum elements (min1 & min2) 
and return (max1 * max2) - (min1 * min2). 
*/
int maxProductDifference(vector<int>& nums) {
    int mx1=0, mx2=0;
    int mn1=99999, mn2=99999;
    for (int x : nums) {
        if (x >= mx1) {
            mx2 = mx1;
            mx1 = x;
        }
        else if (x > mx2) mx2 = x;
        if (x <= mn1) {
            mn2 = mn1;
            mn1 = x;
        }
        else if (x < mn2) mn2 = x;
    }
    return (mx1 * mx2) - (mn1 * mn2);
}

int main() {
    return 0;
}