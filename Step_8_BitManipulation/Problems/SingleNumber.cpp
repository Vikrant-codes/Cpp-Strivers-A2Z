/*
Leetcode - 136. Single Number : Easy

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples :-

Input: nums = [2,2,1] __ Output: 1
Input: nums = [4,1,2,1,2] __ Output: 4
Input: nums = [1] __ Output: 1

Constraints :-
• 1 <= nums.length <= 3 * 10^4
• -3 * 10^4 <= nums[i] <= 3 * 10^4
• Each element in the array appears twice except for one element which appears only once.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Intuition
For each element, count how many times it appears in the array by comparing it with every other element. 
If its frequency is 1, we have found the element that occurs only once, so return it.

>> Complexity Analysis:
- Time: O(n²) — For each element, we traverse the entire array to count its frequency.
- Space: O(1) — Only a constant amount of extra space is used.
*/
int singleNumberBrute(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        int cnt = 0;

        for (int j = 0; j < n; j++) {
            if (nums[i] == nums[j])
                cnt++;
        }

        if (cnt == 1)
            return nums[i];
    }

    return -1;
}

// Better Approach (Hash Map): Time Complexity : O(n) __ Space Complexity : O( (n-1)/2 + 1)
/*
>> Intuition

Instead of manually counting the frequency of each element using nested loops, 
we can use a hash map to store each element and its frequency.

First, traverse the array and increment the frequency of each element in the map. 
Then, traverse the map and return the element whose frequency is 1.

Complexity Analysis:
- Time: O(n) average — Building the frequency map takes O(n) average time, followed by a traversal of the map.
- Space: O((n-1)/2 + 1) — Every array element appears twice except for one, so count of distinct elements is: (n-1)/2 + 1
*/
int singleNumberHashMap(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int num : nums)
        freq[num]++;

    for (auto it : freq) {
        if (it.second == 1)
            return it.first;
    }

    return -1;
}

// Optimal Approach (Using XOR): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

We can use the XOR (^) operator to find the single element without using extra space.

XOR has two important properties:
- a ^ a = 0 — XORing the same number with itself gives 0.
- a ^ 0 = a — XORing a number with 0 gives the number itself.

Considering this, we can take the XOR of all the elements in the array. 
Since every element except one appears twice, the duplicate elements cancel each other out when XORed, 
leaving only the element that appears once.

Complexity Analysis:
- Time: O(n) — We traverse the array once.
- Space: O(1) — Only one extra variable, xorr, is used.
*/
int singleNumber(vector<int>& nums) {
    int xorr = 0;

    for (int& num : nums)
        xorr ^= num;

    return xorr;
}

int main() {
    return 0;
}