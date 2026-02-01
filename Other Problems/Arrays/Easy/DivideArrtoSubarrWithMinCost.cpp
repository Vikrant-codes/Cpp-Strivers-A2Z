/*
Leetcode - 3010. Divide an Array Into Subarrays With Minimum Cost I : Easy

You are given an array of integers nums of length n.

The cost of an array is the value of its first element. 
For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

You need to divide nums into 3 disjoint contiguous subarrays.

Return the minimum possible sum of the cost of these subarrays.

Examples :-

Input: nums = [1,2,3,12]
Output: 6
Explanation: The best possible way to form 3 subarrays is: [1], [2], and [3,12] at a total cost of 1 + 2 + 3 = 6.
The other possible ways to form 3 subarrays are:
- [1], [2,3], and [12] at a total cost of 1 + 2 + 12 = 15.
- [1,2], [3], and [12] at a total cost of 1 + 3 + 12 = 16.

Input: nums = [5,4,3]
Output: 12
Explanation: The best possible way to form 3 subarrays is: [5], [4], and [3] at a total cost of 5 + 4 + 3 = 12.
It can be shown that 12 is the minimum cost achievable.

Input: nums = [10,3,1,1]
Output: 12
Explanation: The best possible way to form 3 subarrays is: [10,3], [1], and [1] at a total cost of 10 + 1 + 1 = 12.
It can be shown that 12 is the minimum cost achievable.

Constraints :-
- 3 <= n <= 50
- 1 <= nums[i] <= 50
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
We want to split the arrays into 3 subarrays such that the total cost of these subarrays is minimum possible.
The cost of an array/subarray is defined to be the value of the first element of that array/subarray.

Consider an array containing various values:- nums = [a, b, c, d, e, f]
Here the alphabets represent some random integer values.
There are multiple ways to divide the array into 3 subarrays like - 
{ [a], [b, c], [d, e, f] }, { [a, b], [c, d], [e, f] }, { [a, b, c], [d, e], [f] }
No matter how we split the subarrays, the first element (i.e. nums[0]) will definitely be the 1st element of the 1st subarray.
So, nums[0] will definitely contribute to the total cost of these 3 subarrays. 
Subarrays formed would be like this = { [a, ....], [....], [....] }

Total cost = nums[0] + x + y ... where x & y are some other elements from the array

Now, we want to minimize the cost of the other two subarrays.
To minimize their costs, we need to choose the two subarrays such that the 1st element of these subarrays is minimum possible.

Consider for the given array, the minimum elements are b, e & f (b <= e <= f)
Now the optimal way to form subarrays would be = { [a], [b, c, d], [e, f] }.

Thus, nums[0] will always be a part of the answer and 
we need to choose the two minimum elements from the rest of the array (index 1 to end).
These two minimums would be the 1st elements of the other 2 subarrays. 
*/

int minimumCost(vector<int>& nums) {
    int ans = nums[0];
    int mn1 = INT_MAX, mn2 = INT_MAX;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] <= mn1) {
            mn2 = mn1;
            mn1 = nums[i];
        }
        else if (nums[i] < mn2) {
            mn2 = nums[i];
        }
    }

    return ans + mn1 + mn2;
}

int main() {
    return 0;
}