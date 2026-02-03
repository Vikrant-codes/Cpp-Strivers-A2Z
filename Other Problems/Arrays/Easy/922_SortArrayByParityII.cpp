/*
Leetcode - 922. Sort Array By Parity II : Easy

Given an array of integers nums, half of the integers in nums are odd, and the other half are even.
Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
Return any answer array that satisfies this condition.

Examples :-

Input: nums = [4,2,5,7] __ Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], and [2,7,4,5] would also be accepted.

Input: nums = [2,3] __ Output: [2,3]

Constraints :-
- 2 <= nums.length <= 2 * 10^4
- nums.length is even.
- Half of the integers in nums are even.
- 0 <= nums[i] <= 1000

Follow Up: Could you solve it in-place?
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointer Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔑 Intuition
We know :
- Even indices → should contain even numbers.
- Odd indices → should contain odd numbers.
So, if an even index has an odd number and an odd index has an even number, they’re both misplaced → swap them.

📝 Approach
1. Start with two pointers: i = 0 (points to even indices), j = 1 (points to odd indices).
2. Traverse while i < n:
- Move i forward by 2 until you find an odd number at an even index.
- Move j forward by 2 until you find an even number at an odd index.
- If i < n, swap nums[i] and nums[j].
- Then move both pointers forward by 2.
3. Continue until all positions are fixed.
*/

vector<int> sortArrayByParityII(vector<int> &nums) {
    int n = nums.size();
    int i = 0, j = 1;
    while (i < n) {
        while (i < n && nums[i] % 2 == 0)
            i += 2;
        while (j < n && nums[j] % 2 != 0)
            j += 2;
        if (i < n)
            swap(nums[i], nums[j]);
        i += 2;
        j += 2;
    }

    return nums;
}

int main() {
    return 0;
}