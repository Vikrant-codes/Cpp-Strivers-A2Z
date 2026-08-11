/*
Leetcode - 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum : Easy

You are given a 0-indexed array of integers nums.

A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. 
In particular, the prefix consisting only of nums[0] is sequential.

Return the smallest integer x missing from nums such that 
x is greater than or equal to the sum of the longest sequential prefix.

Examples :-

Input: nums = [1,2,3,2,5] __ Output: 6
Explanation: The longest sequential prefix of nums is [1,2,3] with a sum of 6. 
6 is not in the array, therefore 6 is the smallest missing integer greater than or 
equal to the sum of the longest sequential prefix.

Input: nums = [3,4,5,1,12,14,13] __ Output: 15
Explanation: The longest sequential prefix of nums is [3,4,5] with a sum of 12. 
12, 13, and 14 belong to the array while 15 does not. 
Therefore 15 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.

Constraints :-
• 1 <= nums.length <= 50
• 1 <= nums[i] <= 50
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Intuition
1. Find the longest sequential prefix
    • Start with nums[0].
    • Keep moving forward as long as:
        nums[i] == nums[i-1] + 1
    • As soon as this condition fails, the sequential prefix ends.
    • Add all elements of this prefix to get its sum.
For example:
nums = [3, 4, 5, 1, 12, 14, 13]
        └──────┘
     sequential prefix
The prefix is [3,4,5], not [1,12,14,13] or any other consecutive sequence, because a prefix must start from index 0.

Now the answer must be ≥ this sum.
So, we must find the smallest integer which is missing from the array, such that this number >= sum.

We can use hashset/frequency array to efficiently look up for the missing integer from the array.

>> Overall Idea
    Longest sequential prefix
              ↓
           calculate sum
              ↓
       start x = sum
              ↓
    Is x present in nums?
         ↓           ↓
       yes          no
        ↓            ↓
      x++          answer
*/
int missingInteger1(vector<int>& nums) {
    int n = nums.size();
    unordered_set<int> st;
    int sum = nums[0];

    for (int& num : nums) 
        st.insert(num);
    
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i-1] + 1)
            break;
        sum += nums[i];
    }

    int x = sum;
    /*
    while(true) {
        if (!st.count(x))
            return x;
        x++;
    }

    return 0;
    */

    while(st.count(x))
        x++;

    return 0;
}

// Using Frequency Array : Time Complexity : O(2n) __ Space Complexity : O(1)
/*
The previous approach used a set to easily look up for element existence.
For that we stored all the array elements in the set, so this set will take an extra O(n) space.
We can also use a frequency array of size 50 since the array elements are in the range [1, 50].
In this way, the extra space we are using is O(51) ~ O(1) 
and remain constant for all input cases whatever the length of nums be.
*/
int missingInteger2(vector<int>& nums) {
    int n = nums.size();
    vector<int> freq(51);
    int sum = nums[0];

    for (int& num : nums) 
        freq[num]++;

    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i-1] + 1)
            break;
        sum += nums[i];
    }

    int x = sum;
    while(true) {
        if (x > 50 || freq[x] == 0) return x;
        x++;
    }

    return 0;
}

int main() {
    return 0;
}