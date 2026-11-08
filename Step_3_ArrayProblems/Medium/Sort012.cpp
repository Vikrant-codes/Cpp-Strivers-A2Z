// Sort an array of 0's, 1's and 2's
/*
Problem Statement
Given an array nums consisting only of 0, 1, and 2, sort the array in-place so that all 0s come first, 
followed by all 1s, and then all 2s.
You must solve the problem without using the library's sorting function.
*/

/*
Leetcode - 75. Sort Colors : Medium

You are given an array nums with n objects colored red, white, or blue, 
sort them in-place so that objects of the same color are adjacent, 
with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Examples :-

Input: nums = [2,0,2,1,1,0] __ Output: [0,0,1,1,2,2]
Explanation:
The array has two 0s, two 1s, and two 2s. Sorting them in-place places all 0s first, then all 1s, then all 2s.

Input: nums = [2,0,1] __ Output: [0,1,2]
Explanation:
The array has one each of 0, 1, and 2, arranged in-place in the order 0, 1, 2.

Constraints :-
• n == nums.length
• 1 <= n <= 300
• nums[i] is either 0, 1, or 2.

Follow up: Could you come up with a one-pass algorithm using only constant extra space?
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Naive Approach — Counting (Counting Sort Inspired)

Since the array contains only three distinct values (0, 1, and 2), 
instead of directly sorting the elements, we can simply count the frequency of each value.

After counting, we know exactly how many 0s, 1s, and 2s are present. 
We can then overwrite the original array in sorted order:
- Place count0 zeroes.
- Follow them with count1 ones.
- Finally, place count2 twos.

This is a counting-sort-inspired approach, where we count the frequency of each element and 
reconstruct the sorted array using those frequencies.

We can implement this using either three separate counter variables or a frequency array of size 3.

>> Complexity Analysis:
- Time: O(2n) — One traversal to count frequencies and another to rewrite the array.
- Space: O(1) — Three counter variables or a fixed-size frequency array of size 3.
*/

// Using three counters
void sortColors1(vector<int>& nums) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;

    for(int x : nums) {
        if(x == 0) cnt0++;
        else if(x == 1) cnt1++;
        else cnt2++;
    }

    int idx = 0;

    while(cnt0--)
        nums[idx++] = 0;

    while(cnt1--)
        nums[idx++] = 1;

    while(cnt2--)
        nums[idx++] = 2;
}

// Using a frequency array
void sortColors2(vector<int>& nums) {
    int freq[3] = {0};

    for(int x : nums)
        freq[x]++;

    int idx = 0;

    for(int i = 0; i < 3; i++) {
        while(freq[i]--)
            nums[idx++] = i;
    }
}

// Optimal Approach (Dutch National Flag Algo): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal Approach — Dutch National Flag Algorithm

The key idea of the Dutch National Flag algorithm is to divide the array into four regions using three pointers: 
low, mid, and high.

At any point during the algorithm, we maintain the following invariant:
0 to low-1       → All 0s
low to mid-1     → All 1s
mid to high      → Unsorted part
high+1 to n-1    → All 2s

Visual representation:

  0 0 0 0       1 1 1 1 1       0 1 2 0 2 1 1 0       2 2 2 2 2 2
  |     |       |       |       |             |       |         |
  0   low-1    low    mid-1     mid          high   high+1     n-1

Notice that the only unsorted region is from mid to high. 
Our objective is to process this region and move each element into its correct region.

Initially, the entire array is unsorted, so we initialize:
low = 0;
mid = 0;
high = n - 1;

We continue processing while mid <= high, depending on the value at nums[mid].

>> Case 1: nums[mid] == 0
We need to move this 0 into the region containing zeroes.
- Swap nums[mid] with nums[low].
- Increment both low and mid.

Why increment both? 
Because the element at low belongs to the region of 1s (or low == mid), so after swapping, 
the regions remain correctly maintained.

>> Case 2: nums[mid] == 1
The element is already in its correct region, so simply increment mid.

>> Case 3: nums[mid] == 2
We need to move this 2 into the region containing twos.
- Swap nums[mid] with nums[high].
- Decrement high.

We do not increment mid here because the element swapped from high belongs to the previously unsorted region. 
We haven't examined it yet, so we must process it before moving mid.

We stop when mid > high, meaning the unsorted region is empty. 
At that point, all four regions are correctly arranged, and the array is sorted.

>> Complexity Analysis
- Time: O(n) — Every iteration reduces the size of the unsorted region by at least one.
- Space: O(1) — Sorting is performed in-place using only three pointers.
*/
void sortColors(vector<int>& nums) {
    int n = nums.size();

    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if (nums[mid] == 1) {
            mid++;
        }
        else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

int main() {
    return 0;
}