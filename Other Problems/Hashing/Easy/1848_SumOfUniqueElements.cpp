/*
Leetcode - 1748. Sum of Unique Elements : Easy

You are given an integer array nums. The unique elements of an array are the elements that appear exactly once in the array.
Return the sum of all the unique elements of nums.

Examples :-

Input: nums = [1,2,3,2] __ Output: 4
Explanation: The unique elements are [1,3], and the sum is 4.

Input: nums = [1,1,1,1,1] __ Output: 0
Explanation: There are no unique elements, and the sum is 0.

Input: nums = [1,2,3,4,5] __ Output: 15
Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.

Constraints :-
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

int sumOfUnique1(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int x : nums)
        freq[x]++;
    
    int sum = 0;
    for (int i = 1; i <= 100; i++) 
        if (freq[i] == 1)
            sum += i;
    
    return sum;
}

int sumOfUnique(vector<int>& nums) {
    vector<int> freq(101);

    for(int x : nums) 
        freq[x]++;

    int sum = 0;
    for (int i = 0; i < 101; i++)
        if (freq[i] == 1)
            sum += i;

    return sum;
}

int main() {
    return 0;
}