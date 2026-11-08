/*
Leetcode - 53. Maximum Subarray : Medium

Given an integer array nums, find the subarray with the largest sum, and return its sum.

Examples :-

Input: nums = [-2,1,-3,4,-1,2,1,-5,4] __ Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Input: nums = [1] __ Output: 1
Explanation: The subarray [1] has the largest sum 1.

Input: nums = [5,4,-1,7,8] __ Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.

Constraints :-
• 1 <= nums.length <= 10^5
• -10^4 <= nums[i] <= 10^4

Follow up: If you have figured out the O(n) solution, 
try coding another solution using the divide and conquer approach, which is more subtle.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Naive Approach — Generate All Subarrays 

Since we need to find the maximum sum among all possible contiguous subarrays, 
the straightforward approach is to generate every possible subarray and calculate its sum.

We use two loops to decide the starting and ending indices of a subarray:
- The outer loop fixes the starting index i.
- The inner loop extends the ending index j from i to n-1.
For every subarray [i...j], we calculate its sum and update the maximum sum found so far.

We can use a third loop to calculate the sum of each subarray from scratch.
Or, We can eliminate the third loop by maintaining a running sum.

For every starting index i, initialize sum = 0. 
Then extend the subarray by moving j forward and adding nums[j] to the current sum.

>> Complexity Analysis
- Time: O(n²) — Two nested loops, with constant-time sum updates.
- Space: O(1).
*/
int maxSubArrayNaive(vector<int>& nums) {
    int n = nums.size();
    int maxi = INT_MIN;

    for (int i = 0; i < n; i++) {
        int sum = 0;

        for (int j = i; j < n; j++) {
            sum += nums[j];
            maxi = max(maxi, sum);
        }
    }

    return maxi;
}

// Optimal Approach (Kadane's Algorithm) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal Approach — Kadane's Algorithm

The key observation behind Kadane's Algorithm is:
If the sum of the previous subarray is negative, 
including it in our current subarray will only decrease the overall sum.

So, whenever our running sum becomes negative, 
we discard the previous subarray and start a new one from the next element.

Let's understand this.
Suppose we are traversing the array and maintaining a sum representing the sum of the current subarray.

For every element:
1. Add the current element to sum.
2. Update maxi with the maximum sum found so far.
3. If sum becomes negative, reset it to zero because extending this subarray further would be disadvantageous.

>> Why do we reset to zero?
Consider: [-2, 1, -3, 4, -1, 2, 1, -5, 4]

When we process -2, our running sum becomes negative. 
Keeping -2 while considering the next elements would only reduce their sum.
So, we discard it and start fresh from 1.

Similarly, when we reach -3, the running sum becomes negative again, so we discard that subarray as well.
Eventually, we get: [4, -1, 2, 1] = 6, which is the maximum subarray.

Important: We update maxi before resetting sum. 
This is necessary to handle arrays containing only negative elements, such as [-3, -2, -5]. 
In that case, the answer should be -2, not 0.

>> Complexity Analysis
- Time: O(n) — We traverse the array only once.
- Space: O(1) — Only two variables are maintained.
*/
int maxSubArray(vector<int>& nums) {
    int n = nums.size();

    int sum = 0, maxSum = INT_MIN;

    for(int i = 0; i < n; i++) {
        sum += nums[i];

        maxSum = max(maxSum, sum);

        if(sum < 0)
            sum = 0;
    }

    return maxSum;
}

//? Follow up solution (Divide and Conquer Approach): Time Complexity : O(N log N) __ Space Complexity : O(log N)
/*
This approach is a little more subtle because instead of building the maximum subarray incrementally, 
we divide the problem into smaller subproblems.

>> Intuition

Consider an array divided into two halves using the middle index.

The maximum subarray must belong to one of these three categories:
1. Entirely in the left half: The maximum subarray lies completely before or at the middle index.
2. Entirely in the right half: The maximum subarray lies completely after the middle index.
3. Crosses the middle: The maximum subarray starts somewhere in the left half and ends somewhere in the right half.

These are the only three possibilities.

Three possibilities for the maximum subarray

Case 1 — Left half
[ 2, -1, -3, 0, 1, 5 ]
Maximum subarray lies completely in the left half.

Case 2 — Right half
[ 1, 5, -1, -3, 0, 2 ]
Maximum subarray lies completely in the right half.

Case 3 — Crossing the middle
[ 1, 5, -1, -1, 3, -3]
The maximum subarray crosses the midpoint. Here, [1, 5, -1, -1, 3] has sum 7.

So, we recursively find:
- maxLeft: Maximum subarray sum in the left half.
- maxRight: Maximum subarray sum in the right half.
- maxCross: Maximum subarray sum crossing the midpoint.

Our answer will be: 
    max(maxLeft, maxRight, maxCross)

>> How do we calculate the crossing sum?
This is the important part.
For a subarray to cross the midpoint, it must include:
- A suffix of the left half (ending at mid).
- A prefix of the right half (starting at mid + 1).

Therefore, we calculate:

-> Maximum suffix sum of the left half:
Start from mid and traverse backwards towards low, maintaining a running sum and maximum.

-> Maximum prefix sum of the right half:
Start from mid + 1 and traverse forwards towards high, maintaining a running sum and maximum.

Add these two maximum sums to get maxCross. 
    maxCross = maxLeftSuffix + maxRightPrefix

>> Complexity Analysis

-> Time Complexity: O(N log N)
At every recursive level, we divide the array into two halves.
For every call, calculating the crossing sum takes time proportional to the size of that subarray.

The recurrence is: T(N) = 2T(N/2) + O(N)
Using the Master Theorem: T(N) = O(N log N)

-> Space Complexity: O(log N)
The recursion depth is O(log N), as the array is divided into halves at every level. 
The auxiliary variables use constant space per recursive call.
*/

int maxCrossingSum(vector<int>& nums, int low, int mid, int high) {
    int sum = 0;
    int leftSum = INT_MIN;

    // Maximum suffix sum in the left half
    for(int i = mid; i >= low; i--) {
        sum += nums[i];
        leftSum = max(leftSum, sum);
    }

    sum = 0;
    int rightSum = INT_MIN;

    // Maximum prefix sum in the right half
    for(int i = mid + 1; i <= high; i++) {
        sum += nums[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

int solve(vector<int>& nums, int low, int high) {
    // Base case: only one element
    if(low == high)
        return nums[low];

    int mid = low + (high - low) / 2;

    int maxLeft = solve(nums, low, mid);
    int maxRight = solve(nums, mid + 1, high);

    int maxCross = maxCrossingSum(nums, low, mid, high);

    return max({maxLeft, maxRight, maxCross});
}

int maxSubArrayDivConquer(vector<int>& nums) {
    return solve(nums, 0, nums.size() - 1);
}

int main() {
    return 0;
}