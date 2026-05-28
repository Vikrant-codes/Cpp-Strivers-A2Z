/*
Leetcode - 414. Third Maximum Number : Easy

Given an integer array nums, return the third distinct maximum number in this array. 
If the third maximum does not exist, return the maximum number.

Examples :-

Input: nums = [3,2,1] __ Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.

Input: nums = [1,2] __ Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.

Input: nums = [2,2,3,1] __ Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.

Constraints :-
• 1 <= nums.length <= 10^4
• -2^31 <= nums[i] <= 2^31 - 1

Follow up: Can you find an O(n) solution?
*/

#include<bits/stdc++.h>
using namespace std;

int thirdMax(vector<int>& nums) {
    long long max1 = -2147483649, max2 = -2147483649, max3 = -2147483649;
    for(int x : nums) {
        if (x > max1) {
            max3 = max2;
            max2 = max1;
            max1 = x;
        }
        else if (x > max2 && x < max1) {
            max3 = max2;
            max2 = x;
        }
        else if (x > max3 && x < max2) {
            max3 = x;
        }
    }
    if (max3 == -2147483649) return max1;
    return max3;
}

int main() {
    return 0;
}