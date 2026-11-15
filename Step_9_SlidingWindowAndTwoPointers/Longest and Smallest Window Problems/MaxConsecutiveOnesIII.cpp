/*
Leetcode - 1004. Max Consecutive Ones III : Medium

Given a binary array nums and an integer k, 
return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Examples :-

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10

Constraints :-
• 1 <= nums.length <= 10^5
• nums[i] is either 0 or 1.
• 0 <= k <= nums.length
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Simplified problem statement

We are given a binary array and an integer k. We can flip at most k zeroes into ones.
Essentially, the problem is asking:
Find the length of the longest subarray containing at most k zeroes.
Why? Because we can flip those zeroes to ones, making the entire subarray consecutive ones.
*/

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Brute Force — Generate all subarrays

- Consider every possible starting index i.
- From i, keep extending the subarray by moving j.
- Maintain a count of zeroes in the current subarray.
- If the zero count is at most k, update maxLen.
- If the zero count exceeds k, break immediately.

Why break?
Once the number of zeroes exceeds k, extending the subarray further can never reduce the zero count. 
So no longer subarray starting at the same i can be valid.
*/
int longestOnesBrute(vector<int>& nums, int k) {
    int n = nums.size();
    int maxLen = 0;

    for(int i = 0; i < n; i++) {
        int zeroes = 0;

        for(int j = i; j < n; j++) {
            if(nums[j] == 0)
                zeroes++;

            if(zeroes > k)
                break;

            maxLen = max(maxLen, j-i+1);
        }
    }

    return maxLen;
}

// Sliding Window: Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Intuition

We can optimize the brute-force approach using a sliding window.

Instead of generating every subarray independently, we maintain a window [l, r] and expand it by moving r.
1. Expand the window by moving r to the right.
2. If nums[r] == 0, increment the zero count.
3. If the number of zeroes exceeds k, the window becomes invalid.
4. To make it valid again, keep shrinking the window from the left by moving l until the zero count becomes at most k.
5. Update maxLen with the current valid window length.

The key idea is that we always maintain a valid window before updating the answer.

>> Complexity
- Time: O(2n) = O(n). Both pointers traverse the array at most once.
- Auxiliary Space: O(1)
*/
int longestOnesOpt1(vector<int>& nums, int k) {
    int n = nums.size();

    int maxLen = 0;
    int l = 0, r = 0;
    int zeroes = 0;

    while(r < n) {
        if(nums[r] == 0)
            zeroes++;

        while(zeroes > k) {
            if(nums[l] == 0)
                zeroes--;

            l++;
        }

        maxLen = max(maxLen, r-l+1);
        r++;
    }

    return maxLen;
}

// Optimized Sliding Window: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

In the naive approach, whenever the window becomes invalid, we keep shrinking it until it becomes valid again.
But do we actually need to do that?

Remember, we are only interested in finding the longest valid subarray.
Suppose we have already found a valid window of length maxLen.
Now, when we expand the window by moving r:
- If the window remains valid, its length increases by one. We can update maxLen.
- If the window becomes invalid, we already have a valid subarray of length maxLen. 
  We don't need to shrink the window completely.
- Instead, simply move l one position forward. This maintains the window's previous length.

Why is this sufficient?
At the point where the window becomes invalid, its length is maxLen + 1. 
Moving l once reduces it back to maxLen.
We are essentially maintaining a window of the maximum length found so far, 
rather than always trying to make the window valid.
And if this window becomes valid again later, we can potentially increase its length and update our answer.

>> Complexity:
- Time: O(n). Both pointers move only forward, and each traverses the array at most once.
- Auxiliary Space: O(1)
*/
int longestOnesOpt2(vector<int>& nums, int k) {
    int n = nums.size();

    int maxLen = 0;
    int l = 0, r = 0;
    int zeroes = 0;

    while(r < n) {
        if(nums[r] == 0)
            zeroes++;

        if(zeroes > k) {
            if(nums[l] == 0)
                zeroes--;

            l++;
        }

        if(zeroes <= k) {
            maxLen = max(maxLen, r-l+1);
        }

        r++;
    }

    return maxLen;
}

int main() {
    return 0;
}