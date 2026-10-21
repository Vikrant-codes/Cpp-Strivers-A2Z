/*
Leetcode - 169. Majority Element : Easy

Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. 
You may assume that the majority element always exists in the array.

Examples :-

Input: nums = [3,2,3] __ Output: 3

Input: nums = [2,2,1,1,1,2,2] __ Output: 2

Constraints :-
• n == nums.length
• 1 <= n <= 5 * 10^4
• -10^9 <= nums[i] <= 10^9
• The input is generated such that a majority element will exist in the array.

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
For every element, count how many times it appears in the entire array. 
If its frequency is greater than `n / 2`, it is the majority element, so return it.

Complexity Analysis:
-> Time: O(n²) — For each of the n elements, we traverse the entire array to count its occurrences.
-> Space: O(1) — We use only a few variables (n, i, j, and cnt), regardless of the input size.
*/
int majorityElementBrute(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        int cnt = 0;
    
        for (int j = 0; j < n; j++) {
            if (nums[j] == nums[i])
                cnt++;
        }
    
        if (cnt > n / 2) return nums[i];
    }

    return -1;
}

// Better Approach (Using Hashmap): Time Complexity : O(n) __ Space Complexity : O(n)
/*
Store the frequency of each element in an unordered_map. 
Traverse the array once to count occurrences, then iterate through the map to find the element whose frequency exceeds n/2.

Complexity Analysis:
-> Time: O(n) — Building the frequency map takes O(n) on average, and iterating through the map takes at most O(n).
-> Space: O(n) — In the worst case, all elements are distinct, so the map stores n entries.
*/
int majorityElementMap(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, int> freq;
    
    for (int& x : nums) 
        freq[x]++;
    
    for (auto& [num, cnt] : freq) 
        if (cnt > n / 2)
            return num;
    
    return -1;
}

// Optimal Approach (Boyer–Moore Voting Algorithm): Time Complexity : O(n) __ Space Complexity : O(1)
/*
| Boyer–Moore Voting Algorithm

>> Intuition
The key idea is that we can cancel out different elements against each other, 
because the majority element appears more than `n/2` times and 
therefore cannot be completely eliminated by all the other elements combined.

We maintain two variables:
- ans: The current candidate for the majority element.
- cnt: The candidate's vote count.

For every element x:
- If x == ans, increment cnt because it supports our current candidate.
- Otherwise, decrement cnt because it cancels out one vote for the current candidate.
- If cnt becomes 0, our current candidate has been completely cancelled out, 
  so we select the current element x as the new candidate and reset cnt = 1.

>> Why does this work?

Think of every pair of different elements as cancelling each other out. 
Since the majority element occurs more than `n/2` times, 
there are fewer non-majority elements than majority elements. 
Thus, even after cancellation, the majority element cannot be eliminated entirely and will remain the final candidate.

-- Important: 
This guarantees the correct answer only when a majority element is guaranteed to exist, as in LeetCode 169. 
If no majority element is guaranteed, the algorithm still produces a candidate, 
but that candidate might not be the majority element. 
In that case, we must count the occurrences of ans in a second pass and verify that its frequency is greater than `n/2`.

>> Complexity Analysis:
- Time: O(n) — We traverse the array once to find the candidate. 
  If verification is required, a second traversal is still O(n).
- Space: O(1) — We use only the candidate and vote count, regardless of array size.
*/
int majorityElement(vector<int>& nums) {
    int candidate = nums[0], cnt = 0;

    for (int& x : nums) {
        if (x == candidate) cnt++;

        else cnt--;
        
        if (cnt == 0) {
            candidate = x;
            cnt = 1;
        }
    }

    return candidate;       // It is guaranteed that the nums vector always have a majority element
}

// GFG Variant
/*
GFG - Majority Element : Medium

Given an array arr[]. Find the majority element in the array. If no majority element exists, return -1.
Note: A majority element in an array is an element that appears strictly more than arr.size()/2 times in the array.

Examples :-

Input: arr[] = [1, 1, 2, 1, 3, 5, 1] __ Output: 1
Explanation: Since, 1 is present more than 7/2 times, so it is the majority element.

Input: arr[] = [7] __ Output: 7
Explanation: Since, 7 is single element and present more than 1/2 times, so it is the majority element.

Input: arr[] = [2, 13] __ Output: -1
Explanation: Since, no element is present more than 2/2 times, so there is no majority element.

Constraints :-
• 1 ≤ arr.size(), arr[i] ≤ 10^5
*/

// Optimal Approach (Boyer–Moore Voting Algorithm): Time Complexity : O(n) __ Space Complexity : O(1)
/*
In the GFG Variant, the array may or may not have the majority element.
So, after applying the Boyer–Moore Voting Algorithm, 
we must verify whether the candidate is actually a majority element or not.

If the candidate's frequency is more than n/2, we return it as the answer. Else we return -1.
*/
int majorityElementGFG(vector<int>& arr) {
    int n = arr.size();
    
    int candidate = arr[0], cnt = 0;
    
    for (int& x : arr) {
        if (x == candidate) cnt++;
        else cnt--;
        
        if (cnt == 0) {
            candidate = x;
            cnt = 1;
        }
    }
    
    // count the freq of candidate to verify if it actually is the majority element
    int freq = 0;
    for (int& x : arr) 
        if (x == candidate)
            freq++;
            
    return (freq > n / 2) ? candidate : -1;
}

int main() {
    return 0;
}