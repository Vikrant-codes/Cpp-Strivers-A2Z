/*
Leetcode - 410. Split Array Largest Sum

Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
Return the minimized largest sum of the split.
A subarray is a contiguous part of the array.

Examples :-

Input: nums = [7,2,5,10,8], k = 2 __ Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

Input: nums = [1,2,3,4,5], k = 2 __ Output: 9
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
 
Constraints :- 1 <= nums.length <= 1000 __ 0 <= nums[i] <= 10^6 __ 1 <= k <= min(50, nums.length)
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Binary Search): Time Complexity : O(n * log(sum- max)) __ Space Complexity : O(1)
/*
Approach :- 
The approach to this problem is similar to the Book Allocation Problem :- Allocate Minimum Pages 

Here, we need to find the minimum largest sum among k subarray splits. Like we did in Book Allocation Problem, here also for some sum limit 'lim' 
we check whether we can split the array into k (or less) parts such that the maximum subarray split sum among them is 'lim'. 

The function isPossible(vector<int>& nums, int k, int lim) checks this. It checks if we consider 'lim' as the maximum sum limit of any split
then how many splits are required. 'cnt' variable keeps count of these required_splits, if this cnt exceeds k that means for the sum limit 'lim'
we need more than k splits, hence 'lim' is not feasible.

We keep low as max(nums) since this is the least maximum sum we can have in any subarray, and high as sum(nums) since this is the most we can have.
We use binary search to check feasibility of mid = (low + high) / 2.
If mid is feasible, we eliminate right half using high = mid - 1. Else eliminate left half using low = mid + 1.
*/

bool isPossible(vector<int>& nums, int k, int lim) {
    int sum = 0, cnt = 1;
    for (int x : nums) {
        if (sum + x > lim) {
            cnt++;
            sum = x;
        }
        else sum += x;
    }
    return cnt <= k;
}

int splitArray(vector<int>& nums, int k) {
    int max = *max_element(nums.begin(), nums.end());
    int sum = accumulate(nums.begin(), nums.end(), 0);

    if (k == 1) return sum;
    if (k == nums.size()) return max;

    int low = max, high = sum;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(nums, k, mid)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> nums = {7, 2, 5, 10, 8};
    int k = 2;
    cout << splitArray(nums, k) << endl;  // Output: 18
    return 0;
}