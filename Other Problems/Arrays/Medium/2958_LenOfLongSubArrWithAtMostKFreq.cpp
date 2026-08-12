/*
Leetcode - 2958. Length of Longest Subarray With at Most K Frequency : Medium

You are given an integer array nums and an integer k.
The frequency of an element x is the number of times it occurs in an array.
An array is called good if the frequency of each element in this array is less than or equal to k.
Return the length of the longest good subarray of nums.
A subarray is a contiguous non-empty sequence of elements within an array.

Examples :-

Input: nums = [1,2,3,1,2,3,1,2], k = 2
Output: 6
Explanation: 
The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3 occur at most twice in this subarray. 
Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
It can be shown that there are no good subarrays with length more than 6.

Input: nums = [1,2,1,2,1,2,1,2], k = 1
Output: 2
Explanation: 
The longest possible good subarray is [1,2] since the values 1 and 2 occur at most once in this subarray. 
Note that the subarray [2,1] is also good.
It can be shown that there are no good subarrays with length more than 2.

Input: nums = [5,5,5,5,5,5,5], k = 4
Output: 4
Explanation: 
The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in this subarray.
It can be shown that there are no good subarrays with length more than 4.
 

Constraints :-
• 1 <= nums.length <= 10^5
• 1 <= nums[i] <= 10^9
• 1 <= k <= nums.length
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^3) __ Space Complexity : O(n)
/*
The idea is to consider every possible subarray and 
check whether it satisfies the condition that no element occurs more than k times.

We can generate the subarrays using two for loops, and for every subarray, we can check if it is valid.
If yes, we can find its length and track the maximum length of the valid subarray.
While creating subarray, when subarray becomes invalid, we don't extend it any further as doing so will not make it valid.
Instead, once a subarray becomes invalid, we move to consider the next starting index for subarrays.

>> Complexity Analysis
Let n = nums.size().

Worst-case time: O(n³)
• There are O(n²) possible (i, j) subarrays.
• For each subarray, validSubArr() can take O(n) time to scan subArr.
• Therefore: O(n²) × O(n) = O(n³)
The early break can improve practical performance, but worst-case remains O(n³).

Space: O(n)
• subArr can contain up to n elements.
• freq can contain up to n distinct elements.
• So auxiliary space is O(n).
*/ 

// helper function: checks if current subarray is valid or not
bool validSubArr(vector<int>& subArr, int k) {
    unordered_map<int, int> freq;
    int mx_freq = 0;

    for (int x : subArr) {
        freq[x]++;
        mx_freq = max(mx_freq, freq[x]);
    }

    return mx_freq <= k;
}

int maxSubarrayLengthBrute(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        vector<int> subArr;
        for (int j = i; j < n; j++) {
            subArr.push_back(nums[j]);

            if (!validSubArr(subArr, k)) break;

            ans = max(ans, j - i + 1);
        }
    }

    return ans;
}

// Better Approach : Time Complexity : O(n^2) __ Space Complexity : O(n)
/*
Instead of constructing every subarray and then scanning it again with validSubArr(), 
we maintain the frequency map while extending the subarray.

For each starting index i:
• Start with an empty frequency map.
• Move j forward and add nums[j] to the frequency map.
• If freq[nums[j]] > k, the current subarray has become invalid, so we can immediately break.
• Otherwise, update the maximum length.

The key improvement is that we don't repeatedly scan the entire subarray to check its validity. 
We already know which element was just added, so we only need to check its frequency.

>> Complexity Analysis
Let n = nums.size().

Time: O(n²) average
• The outer loop runs n times.
• For each i, the inner loop can run up to n times.
• Each unordered_map operation is O(1) average.
• Therefore: O(n × n) = O(n²)

Space: O(n)
• The frequency map can contain up to n distinct elements for a particular starting index.
*/
int maxSubarrayLengthBetter(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        unordered_map<int, int> freq;
        
        for (int j = i; j < n; j++) {
            freq[nums[j]]++;
            if (freq[nums[j]] > k) break;
    
            ans = max(ans, j - i + 1);
        }
    }

    return ans;
}

// Optimal Approach (Sliding Window) : Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Intuition
We can maintain a sliding window [i, j] that always represents a valid subarray, i.e. no element occurs more than k times.
We expand the window by moving j forward and adding the newly encountered element to the frequency map.

The important observation comes when adding the new element makes the window invalid.
Suppose the window was valid before adding x. Therefore, every element was already occurring at most k times. 
After adding x, if the window becomes invalid, x must be the element that caused the violation:
    freq[x] = k + 1

Now, to make the window valid again, we need to remove elements from it such that the maximum freq will again become <= k.
Instead of blindly removing elements and checking validity after each removal we can optimize it.
The invalidity occurred due to addition of the element `x` which caused the maximum frequency to go beyond the allowed limit k.
Since, x is what made the current window invalid, removing other elements won't have much effect and 
we need to remove one occurrence of `x` to make the window valid again.
So we know exactly what needs to be fixed: one occurrence of x has to be removed from the window.
So, we remove elements from the left, and simply keep shrinking the window until we encounter 
and remove the first occurrence of x in the current window.
After that:
    freq[x] = k
and the window is valid again.

The important optimization is that we don't need to check the validity of the entire window after every removal.

>> Why?
Because the window was valid before adding x, and adding x was the only change that made it invalid. 
Therefore, removing one occurrence of that same x is guaranteed to restore validity.
So the shrinking process is targeted:
    Valid window
         ↓
    Add x
         ↓
    x occurs k+1 times → invalid
         ↓
    Remove from left
         ↓
    Keep removing until first x is removed
         ↓
    x occurs k times → valid again
This allows us to maintain the window efficiently while both pointers only move forward.

>> Complexity 
Time: O(n) average
Although there is a shrinking loop inside the expanding loop, i can move from 0 to n-1 only once in total.
Therefore:
• j moves at most n times → O(n)
• i moves at most n times → O(n)
Total: O(n) average time

Space: O(n) in the worst case for the frequency map.
*/
int maxSubarrayLength(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;

    unordered_map<int, int> freq;
    
    int i = 0, j = 0;
    while (j < n) {
        int x = nums[j];
        freq[x]++;
    
        // if this newly added element has made the current subarray window invalid, 
        // remove elements from the window till one occurrence of this x is removed 
        // (so to balance out the increment which caused to make the window invalid)
        if (freq[x] > k) {
            /*
            while (true) {
                int y = nums[i];

                freq[y]--;
                i++;
                
                // if 'x' has been removed from current window, stop the removal of further window members
                if (y == x) break;
            }
            */

            while (freq[x] > k) {
                freq[nums[i]]--;
                i++;
            }
        }
    
        ans = max(ans, j - i + 1);
        j++;
    }
    
    return ans;
}

// concise implementation
int maxSubarrayLength2(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;

    int i = 0, ans = 0;
    
    for (int j = 0; j < n; j++) {
        freq[nums[j]]++;
    
        while (freq[nums[j]] > k) {
            freq[nums[i]]--;
            i++;
        }
    
        ans = max(ans, j - i + 1);
    }

    return ans;
}

int main() {
    return 0;
}