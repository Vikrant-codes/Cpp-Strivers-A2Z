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

// Optimal Approach (Sliding Window) : Time Complexity : O(2n) ~ O(n) __ Space Complexity : O(n)
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

>> Complexity Analysis
Let n be the length of nums.

-> Time complexity: O(n)

The outer loop iterates through each element in the array exactly once, 
as indicated by the range from 0 to the length of nums in the for loop.

Inside this outer loop, the inner while loop with the start pointer performs a sliding window operation. 
However, note that the start pointer is increased and frequency[nums[start]] is decreased within this loop. 
The start pointer is never decreased after it is increased in the while loop. 
Hence, once an element is processed in the while loop, it will not be revisited. 
Therefore, each element is processed at most twice: once during the outer loop and at most once during the while loop.

In the worst case, the inner while loop could iterate through the entire length of the array during its lifetime. 
However, since each element is processed at most twice, the total number of iterations across all elements is linear, 
making the time complexity of the algorithm O(2n) ~ O(n).

-> Space: O(n) in the worst case for the frequency map.
*/
int maxSubarrayLength1(vector<int>& nums, int k) {
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

// Optimal Approach 2 (Sliding Window without nested loops) : Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Intuition
We have already discussed using sliding window and counting to solve this problem. 
Now let's develop an approach without nested loops.

Firstly, we initialize two pointers, one marking the start and the other marking the end of the window. 
As we iterate through the array, we gradually expand the window by moving the end pointer forward. 
At each step, we update a data structure to keep track of the frequency of elements within the current window. 
We also maintain an integer that signifies the count of characters with a frequency greater than k.

Now, here's the crucial insight for this approach: we never shrink the size of the window. 
Instead, we only expand or move it. 
Why? Because we aim to find the longest good subarray, meaning once we've encountered a good subarray, 
we want to keep exploring larger subarrays to maximize the length.

As we process the array, we expand the window by adding the next element; 
we update the frequency of this element, then we check if its frequency would become k + 1. 
Why do we do this? 
If the frequency of the current element were to exceed k, it means we're introducing a "bad" element 
into the window because the frequency of all elements must be less than or equal to k. 
If the frequency of the current element is equal to k + 1, 
we must increment the count of characters with a frequency greater than k.

If we detect a breach in the "goodness" condition (count of characters with a frequency greater than k > 0), 
we move the window from the start. 
As we process new elements, the same size window is slid, instead of expanded, with each iteration, 
until the window meets the "goodness" condition again. 
If the frequency of the element at start is equal to k after decrementing its frequency, 
we decrement the count of characters with a frequency greater than k. 
When this count is zero, we can continue as we did before we found a "bad" element, 
expanding the window with each new element. 
This process ensures that the size of our current window is equal to the largest "good" subarray encountered so far.

It's worth noting that since we don't decrease the size of the window, 
this doesn't guarantee that all explored subarrays of the current size are good. 
However, it does indicate that we've encountered at least one good subarray of that size in the past. 
And since our goal is to find the length of the longest good subarray, this information suffices.

>> Algorithm

1. Initialize n = nums.size(), map `freq` to store the frequency of elements, 
   `start` to mark the start position of subarray (initially start = 0),
   and `charsWithFreqOverK` to count the number of elements with frequency exceeding k.
2. Iterate through the array nums using a sliding window approach, 
   with start and end pointers to define the current subarray.
3. Increment the frequency of the element at index `end` in the frequency Counter.
4. If the frequency of the element at index end becomes equal to k + 1, 
   increment charsWithFreqOverK to track the count of elements exceeding frequency k.
5. If there are elements with frequency exceeding k (i.e., if charsWithFreqOverK is non-zero):
    • Decrement the frequency of the element at index start in the frequency counter as it moves out of the current window.
    • If the frequency of the element at index start becomes equal to k, 
      decrement charsWithFreqOverK as the element at index start no longer exceeds frequency k.
    • Increment the start pointer to move the window forward.
6. Continue the process until the entire array is traversed.
7. Return the length of the longest good subarray, 
   which is calculated by subtracting the start index from the total length of the array.

----
We just need the length of the longest good subarray, so while maintaining the window 
we keep expanding it till goodness is maintained, but once the current window becomes invalid, 
we don't shrink it to make it valid again, instead we just slide it down by moving the start pointer ahead.
Assume the length of window before it became invalid was `l`, 
now we know that the array nums has a good subarray of length l, 
and we want to check if it has any good subarray with length > l.
So, we don't shrink the window instead, we only slide it to the right by removing one element during each slide,
and we don't expand the window size unless it becomes valid again.
----

>> Dry Run
nums = [1,2,1,2,3,1,2,4,2], k = 2
n = nums.size() = 9

Initially, start = 0, freq = {}, charsWithFreqOverK = 0
window = []

Now, we start traversing using the end pointer 
- end = 0: element = 1
    window = [1] 2 1 2 3 1 2 4 2
    freq = {1: 1}
    start = 0, charsWithFreqOverK = 0

- end = 1: element = 2
    window = [1 2] 1 2 3 1 2 4 2
    freq = {1: 1, 2: 1}
    start = 0, charsWithFreqOverK = 0

- end = 2: element = 1
    window = [1 2 1] 2 3 1 2 4 2
    freq = {1: 2, 2: 1}
    start = 0, charsWithFreqOverK = 0

- end = 3: element = 2
    window = [1 2 1 2] 3 1 2 4 2
    freq = {1: 2, 2: 2}
    start = 0, charsWithFreqOverK = 0

- end = 4: element = 3
    window = [1 2 1 2 3] 1 2 4 2
    freq = {1: 2, 2: 1, 3: 1}
    start = 0, charsWithFreqOverK = 0

- end = 5: element = 1
    window = [1 2 1 2 3 1] 2 4 2
    freq = {1: 3, 2: 2, 3: 1}

    freq[curr_element] has become 3 (== k + 1), so we shouldn't expand the current window 
    instead slide the window itself by moving start.

    increment charsWithFreqOverK, since a bad element has been newly introduced (freq[curr_element] == k + 1)
        charsWithFreqOverK = 1
    
    since charsWithFreqOverK > 0 (we need to slide the window, so the longest window size is still maintained)
    move start ahead, decrement the freq of start element and shift the window

    window = 1 [2 1 2 3 1] 2 4 2
    freq = {1: 2, 2: 2, 3: 1},   freq of 1 has been decremented since it was thrown out of window
    Now, 1's freq. has now become equal to k after decrement, 
    which means it was a bad element which is thrown out, so we must also decrement the count of charsWithFreqOverK
    charsWithFreqOverK = 0, since freq[nums[start]] = freq[1] == k (= 2)
    start now points at 1

- end = 6: element = 2
    window = 1 [2 1 2 3 1 2] 4 2
    freq = {1: 2, 2: 3, 3: 1}

    this addition of `2` in the window has again made it invalid, so we can't expand the window more than its previous size
    so we must slide it again by moving start pointer ahead, decrementing freq at start and updating charsWithFreqOverK count.

    freq[nums[end]] == k + 1 (since freq[2] == 3): 
        charsWithFreqOverK++; -> charsWithFreqOverK = 1
    
    charsWithFreqOverK > 0: slide the window
        window = 1 2 [1 2 3 1 2] 4 2
        freq[nums[start]]--; -> freq = {1:2, 2: 2, 3: 1}
        freq[nums[start]] == k -> charsWithFreqOverK--; -> charsWithFreqOverK = 0. the window is valid again
        start++; -> start = 2
    
- end = 7: element = 4
    window = 1 2 [1 2 3 1 2 4] 2
    freq = {1: 2, 2: 2, 3: 1, 4: 1}
    this newly added `4` was not a bad element so no need to slide the window, expanding was enough
    start = 2, charsWithFreqOverK = 0

- end = 8: element = 2
    window = 1 2 [1 2 3 1 2 4 2]
    freq = {1: 2, 2: 3, 3: 1, 4: 1}

    this new element `2` has again made the window invalid, so we can't expand the window size, instead need to slide the window

    freq[nums[end]] == k + 1 
        charsWithFreqOverK++; -> charsWithFreqOverK = 1
        
    charsWithFreqOverK > 0: slide the window
        window = 1 2 1 [2 3 1 2 4 2]
        freq = {1: 1, 2: 3, 3: 1, 4: 1}
        freq[nums[start]] = freq[1] = 1, this means the element which was thrown out of window while sliding it,
        was not a bad element (bad element is 2), so count of charsWithFreqOverK is not decremented
        start = 3, charsWithFreqOverK = 1

loop ends, 
the length of current window tells us that there exists at least one good subarray with this length, 
although it is not necessary that the current subarray is the good one.
As we can see, the current subarray window is [2 3 1 2 4 2], with a length of 6,
but this window is not valid, this length 6 actually belongs to the subarray [1 2 3 1 2 4].
The approach works because we never shrink down window, 
we either expand it or slide it ahead, this behaviour guarantees that 
array has at least one good subarray with current window length but we can't say that current window is the valid one.

Longest good subarray length = n - start = 8 - 2 = 6
*/

int maxSubarrayLength(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    int start = 0;
    int charsWithFreqOverK = 0;

    for (int end = 0; end < n; end++) {
        freq[nums[end]]++;
    
        if (freq[nums[end]] == k + 1)
            charsWithFreqOverK++;
    
        if (charsWithFreqOverK > 0) {
            freq[nums[start]]--;

            if (freq[nums[start]] == k)
                charsWithFreqOverK--;
            
            start++;
        }
    }

    return n - start;
}

int main() {
    return 0;
}