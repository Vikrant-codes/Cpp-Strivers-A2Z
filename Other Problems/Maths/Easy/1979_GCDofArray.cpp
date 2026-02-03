/*
Leetcode - 1979. Find Greatest Common Divisor of Array : Easy

Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.
The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

Examples :-

Input: nums = [2,5,6,9,10] __ Output: 2
Explanation:
The smallest number in nums is 2.
The largest number in nums is 10.
The greatest common divisor of 2 and 10 is 2.

Input: nums = [7,5,6,8,3] __ Output: 1
Explanation:
The smallest number in nums is 3.
The largest number in nums is 8.
The greatest common divisor of 3 and 8 is 1.

Input: nums = [3,3] __ Output: 3
Explanation:
The smallest number in nums is 3.
The largest number in nums is 3.
The greatest common divisor of 3 and 3 is 3.

Constraints :- 2 <= nums.length <= 1000 __ 1 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// find GCD of a & b such that b >= a
int GCD(int a, int b)
{
    int rem = b % a;
    while (rem != 0)
    {
        b = a;
        a = rem;
        rem = b % a;
    }
    return a;
}

int findGCD(vector<int> &nums)
{
    int mn = 9999, mx = 0;
    for (int x : nums)
    {
        mn = min(x, mn);
        mx = max(x, mx);
    }
    return GCD(mn, mx);
}

int main()
{
    vector<int> nums = {2, 5, 6, 9, 10};
    cout << findGCD(nums) << endl;
    return 0;
}