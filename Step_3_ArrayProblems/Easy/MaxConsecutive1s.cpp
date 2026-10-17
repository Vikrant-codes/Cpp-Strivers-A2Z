/*
Leetcode - 485. Max Consecutive Ones

Given a binary array nums, return the maximum number of consecutive 1's in the array.

Examples :-

Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.

Input: nums = [1,0,1,1,0,1]
Output: 2 

Constraints :-
• 1 <= nums.length <= 10^5
• nums[i] is either 0 or 1.
*/

#include <bits/stdc++.h>
using namespace std;

int findMaxConsecutiveOnes(vector<int>& nums) {
    int n = nums.size();
    int cnt = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        if (nums[i] == 1) {
            cnt++;
            ans = max(ans, cnt);
        }
        else {
            cnt = 0;
        }
    }

    return ans;
}

int main() {
    return 0;
}