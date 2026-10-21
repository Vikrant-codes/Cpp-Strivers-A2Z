#include <bits/stdc++.h>
using namespace std;

// GFG Variant
/*
GFG - Array Leaders : Easy

You are given an array arr of positive integers. Your task is to find all the leaders in the array. 
An element is considered a leader if it is greater than or equal to all elements to its right. 
The rightmost element is always a leader.

Examples :-

Input: arr = [16, 17, 4, 3, 5, 2]
Output: [17, 5, 2]
Explanation: Note that there is nothing greater on the right side of 17, 5 and, 2.

Input: arr = [10, 4, 2, 4, 1]
Output: [10, 4, 4, 1]
Explanation: Note that both of the 4s are in output, as to be a leader an equal element is also allowed on the right side.

Input: arr = [5, 10, 20, 40]
Output: [40]
Explanation: When an array is sorted in increasing order, only the rightmost element is leader.

Input: arr = [30, 10, 10, 5]
Output: [30, 10, 10, 5]
Explanation: When an array is sorted in non-increasing order, all elements are leaders.

Constraints :-
• 1 ≤ arr.size() ≤ 10^6
• 0 ≤ arr[i] ≤ 10^6
*/

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1) 
/*
>> Intuition
For every element, check all the elements to its right. 
If any element is greater than it, then it cannot be a leader 
because a leader must not be less than any element to (it should be greater than or equal to every element on) its right.
If no such element exists, add it to the answer.
The rightmost element automatically qualifies because there are no elements to its right.

>> Complexity Analysis:
-> Time: O(n²) — For each element, we may traverse all the elements to its right. 
   In the worst case, this results in approximately n * (n-1) / 2 comparisons.

-> Space: O(1) auxiliary space, excluding the output vector. 
   The output itself requires O(n) space in the worst case.
*/
vector<int> leadersBrute(vector<int>& arr) {
    int n = arr.size();

    vector<int> ans;
    
    for (int i = 0; i < n; i++) {
        bool isGreater = true;
    
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                isGreater = false;
                break;
            }
        }
    
        if (isGreater) ans.push_back(arr[i]);
    }
    
    return ans;
}

// Optimal Approach: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

An element is a leader if it is greater than or equal to every element to its right. 
Instead of checking all those elements repeatedly, we can keep track of the maximum element encountered so far 
while traversing from right to left.

- Initialize maxi = INT_MIN.
- Traverse the array from right to left.
- If nums[i] >= maxi, it is a leader because it is greater than / equal to every element to its right.
  Add it to res and update maxi.
- Otherwise, skip it because an element to its right is greater than it.

Since we traverse from right to left, leaders are collected in reverse order. 
Reverse res at the end to restore their original array order.

>> Complexity Analysis:
-> Time: O(n) — One traversal takes O(n), and reversing the result takes at most O(n).
-> Space: O(1) auxiliary space, excluding the output vector. The output requires O(n) space in the worst case.
*/
vector<int> leaders(vector<int>& arr) {
    int n = arr.size();
    
    vector<int> res;
    
    int mxm = INT_MIN;
    
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] >= mxm) {
            res.push_back(arr[i]);
            mxm = arr[i];
        }
    }
    
    reverse(res.begin(), res.end());
    
    return res;
}


// TUF Variant
/*
TUF - 512. Leaders in an Array

Given an integer array nums, return a list of all the leaders in the array.

A leader in an array is an element whose value is strictly greater than all elements to its right in the given array. 
The rightmost element is always a leader. 
The elements in the leader array must appear in the order they appear in the nums array.

Examples :-

Input: nums = [1, 2, 5, 3, 1, 2]
Output: [5, 3, 2]
Explanation:
2 is the rightmost element, 3 is the largest element in the index range [3, 5], 
5 is the largest element in the index range [2, 5]

Input: nums = [-3, 4, 5, 1, -4, -5]
Output: [5, 1, -4, -5]
Explanation:
-5 is the rightmost element, -4 is the largest element in the index range [4, 5], 
1 is the largest element in the index range [3, 5] and 5 is the largest element in the range [2, 5]

Constraints :-
• 1 <= nums.length <= 10^5
• -10^4 <= nums[i] <= 10^4
*/

/*
The TUF Variant is similar to GFG one, but in this variant, 
the leader needs to be strictly greater than all the elements to the right of it.\
So, we can use similar approaches just by slightly changing the leader condition (strict greater check).
*/

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1) 
vector<int> leadersTUFBrute(vector<int>& nums) {
    int n = nums.size();

    vector<int> ans;
    
    for (int i = 0; i < n; i++) {
        bool isStrictGreater = true;
    
        for (int j = i + 1; j < n; j++) {
            if (nums[j] >= nums[i]) {       // not a leader even if some element is equal to it
                isStrictGreater = false;
                break;
            }
        }
    
        if (isStrictGreater) ans.push_back(nums[i]);
    }
    
    return ans;
}

// Optimal Approach: Time Complexity : O(n) __ Space Complexity : O(1)
vector<int> leadersTUF(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> res;
    int maxi = INT_MIN;
    
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] > maxi) {       // if strictly greater
            res.push_back(nums[i]);
            maxi = nums[i];
        }
    }
    
    reverse(res.begin(), res.end());
    
    return res;
}

int main() {
    return 0;
}