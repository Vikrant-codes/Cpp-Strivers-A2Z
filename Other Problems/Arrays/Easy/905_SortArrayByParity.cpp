/*
Leetcode - 905. Sort Array By Parity : Easy

Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
Return any array that satisfies this condition.

Examples :-

Input: nums = [3,1,2,4] __ Output: [2,4,3,1]
Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

Input: nums = [0] __ Output: [0]

Constraints : 1 <= nums.length <= 5000 __ 0 <= nums[i] <= 5000
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointer Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔑 Intuition
We want all even numbers first and all odd numbers later.
1. If the left pointer is already at an even number → it’s in the correct place, move right.
2. If the right pointer is already at an odd number → it’s in the correct place, move left.
3. If we find an odd number on the left and an even number on the right, they’re misplaced → swap them.

📝 Approach
1. Initialize two pointers: i = 0 (start of array), j = n - 1 (end of array).
2. While i < j:
-- Move i forward until you find an odd number.
-- Move j backward until you find an even number.
-- If i < j, swap nums[i] and nums[j] (put the even number to the front and the odd number to the back).
-- Move both pointers (i++, j--).
3. Continue until all evens are before all odds.
4. Return the array.
*/

vector<int> sortArrayByParity(vector<int> &nums) {
    int n = nums.size();
    int i = 0, j = n - 1;
    while (i < j) {
        while (i < n && nums[i] % 2 == 0)
            i++; // increment i till we find an odd element
        while (j >= 0 && nums[j] % 2 != 0)
            j--; // decrement j till we find an even element
        if (i > j)
            break;
        swap(nums[i], nums[j]);
        i++;
        j--;
    }
    return nums;
}

int main() {
    return 0;
}