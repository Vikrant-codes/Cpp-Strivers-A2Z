/*
Leetcode - 3471. Find the Largest Almost Missing Integer : Easy

You are given an integer array nums and an integer k.
An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
Return the largest almost missing integer from nums. If no such integer exists, return -1.
A subarray is a contiguous sequence of elements within an array.

Examples :-

Input: nums = [3,9,2,1,7], k = 3 __ Output: 7
Explanation:
1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
3 appears in 1 subarray of size 3: [3, 9, 2].
7 appears in 1 subarray of size 3: [2, 1, 7].
9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
We return 7 since it is the largest integer that appears in exactly one subarray of size k.

Input: nums = [3,9,7,2,1,7], k = 4 __ Output: 3
Explanation:
1 appears in 2 subarrays of size 4: [9, 7, 2, 1], [7, 2, 1, 7].
2 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
3 appears in 1 subarray of size 4: [3, 9, 7, 2].
7 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
9 appears in 2 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1].
We return 3 since it is the largest and only integer that appears in exactly one subarray of size k.

Input: nums = [0,0], k = 1 __ Output: -1
Explanation:
There is no integer that appears in only one subarray of size 1.

Constraints :-
• 1 <= nums.length <= 50
• 0 <= nums[i] <= 50
• 1 <= k <= nums.length
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach: Time Complexity : O(n + 51) __ Space Complexity : O(51) ~ O(1)
/*
>> Observations
Let n = nums.size()
We need to find maximum element which appears in only 1 subarray of size k.
This k can be in the range [1, n].
Depending on the value of k, a single index can be a part of more than 1 subarray.
Also, since array might have duplicates as well,
some element might exist in more than one subarray, due to presence of its duplicate.

Ex- assume arr = [a, b, c, d, e, f, g], k = 3
If we consider the index '2', 
this index is a part of 3 different subarrays of size 3, 
these subarrays are [a,b,c], [b,c,d] & [c,d,e].

This happens because the same index can act as the start or middle or ending in different subarrays.
This holds true for all elements except the first & last elements (indices 0 & n-1).
The first index can only act as the start in a subarray and thus only exists in one subarray 
Similarly, the last index can only act as the end in a subarray and thus it also only exists in one subarray.
(we are talking about index existence not value).

-> Now, lets observe what happens when k == 1?
When k = 1, all individual elements form separate subarrays and total 'n' subarrays exists for the 'n' elements.
In that case all indices are part of separate subarrays are thus exists each index exists in a separate subarray.
arr = [a, b, c, d, e, f, g], k = 1
The subarrays are : [a], [b], [c], [d], [e], [f], [g].
So, in this case, not just the first and last indices, but all indices appears in exactly one subarray.
So, we should just return the maximum value in the array, right? 
No, this is due to the fact that array can have duplicates as well. assume the above array contains g twice or more.
Then, even though a single index can exist in only one subarray, 
g would still appear in more than one subarray due to its duplicate.
So, we need to return the maximum element whose frequency is equal to 1.

-> What if k == n?
In this case, all elements must be selected to form a subarray and one a single subarray exists which is the array itself.
Since, only a single subarray exists, all array elements are thus part of one a single subarray no matter their index or 
presence of duplicates.
So, in this case, we must return the maximum value of the array no matter its frequency.

-> General case 1 < k < n:
In this case, all indices of range [1, n-2] are part of more than 1 subarray, 
so their elements are also part of more than 1 subarray.
Only the 0th & (n-1)th index are the ones which belong to only 1 subarray.
But, due to the presence of duplicates, even the elements at these indices might appear in more than 1 subarray.
So, we consider some sub-conditions like:
- If both nums[0] & nums[n-1] are distinct (have no duplicates) : return the max. of the two values
- If one of them occurs more than once, we can return the other
- If both of them occurs more than once, then no almost missing integer exists and we need to return -1.

>> Approach / Idea
- Initialize a frequency vector of size 51 (for elements 0 to 50)
- Iterate nums array and store frequency of each element of nums
- Depending on the value of k, there might be three conditions:
    - Case 1 : k == 1: 
        - all indices are part of different 1-sized subarrays, 
        but a single element can still exist in more than 1 subarray due to the presence of duplicates.
        - So, we return the maximum element whose frequency is 1 (If no such element, return -1).
    - Case 2 : k == n:
        - only a single subarray exists, so all elements also exists in this single subarray
        So, return the maximum array element
    - case 3 : 1 < k < n: 
        - The first & last index elements are the ones which might potentially exist in a single subarray
        - This depeneds on the frequency of the two elements
            - If both the elments occur only once: return the maximum of the two values
            - If one of them occurs more than once, we can return the other
            - If both of them occurs more than once, then no almost missing integer exists and we need to return -1.
*/
int largestInteger(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> freq(51);

    for (int x : nums) 
        freq[x]++;
    
    // if k is 1, all indices of nums can be part of only 1 subarray, so return the max. element with freq 1 
    if (k == 1) {
        for (int i = 50; i >= 0; i--) {
            if (freq[i] == 1) {
                return i;
            }
            // if no element with freq 1 exists, we need to return 1
        }
    }

    // if k is equal to n, it means we want to form subarr with size equal to array itself,
    // it means we need to select the whole array, so only 1 subarray exists for this condition
    // thus all elements are part of this one subarray now, so we need to return the maximum element 
    else if (k == n) {
        for (int i = 50; i >= 0; i--) {
            // if current element exists in the array, return it (this way the maximum value will be returned)
            if (freq[i] != 0)
                return i;
        }
    }

    // else, only the 0th and (n-1)th indices are part of exactly 1 subarrays,
    // due to duplicates, even the first and last element can appear in more than one subarray
    // so we need to consider their freq and return accordingly
    else {
        // if both the first & last element has the frequency 1, return the maximum of two
        if (freq[nums[0]] == 1 && freq[nums[n-1]] == 1)
            return max(nums[0], nums[n-1]);
        // else if only the first element has frequency 1, return it
        if (freq[nums[0]] == 1) return nums[0];
        
        // else if only the last element has frequency 1, return it
        if (freq[nums[n-1]] == 1) return nums[n-1];
        // else neither the first element nor the last element has the frequency 1, so we need to return -1
    }
    
    return -1;
}

int main() {
    return 0;
}