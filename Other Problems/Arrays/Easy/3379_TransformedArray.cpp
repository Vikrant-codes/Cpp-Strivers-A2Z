/*
Leetcode - 3379. Transformed Array : Easy

You are given an integer array nums that represents a circular array. 
Your task is to create a new array result of the same size, following these rules:

For each index i (where 0 <= i < nums.length), perform the following independent actions:
- If nums[i] > 0: Start at index i and move nums[i] steps to the right in the circular array. 
  Set result[i] to the value of the index where you land.
- If nums[i] < 0: Start at index i and move abs(nums[i]) steps to the left in the circular array. 
  Set result[i] to the value of the index where you land.
- If nums[i] == 0: Set result[i] to nums[i].
Return the new array result.

Note: Since nums is circular, moving past the last element wraps around to the beginning, 
and moving before the first element wraps back to the end.

Examples :-

Input: nums = [3,-2,1,1]
Output: [1,1,1,3]
Explanation:
For nums[0] that is equal to 3, If we move 3 steps to right, we reach nums[3]. So result[0] should be 1.
For nums[1] that is equal to -2, If we move 2 steps to left, we reach nums[3]. So result[1] should be 1.
For nums[2] that is equal to 1, If we move 1 step to right, we reach nums[3]. So result[2] should be 1.
For nums[3] that is equal to 1, If we move 1 step to right, we reach nums[0]. So result[3] should be 3.

Input: nums = [-1,4,-1]
Output: [-1,-1,4]
Explanation:
For nums[0] that is equal to -1, If we move 1 step to left, we reach nums[2]. So result[0] should be -1.
For nums[1] that is equal to 4, If we move 4 steps to right, we reach nums[2]. So result[1] should be -1.
For nums[2] that is equal to -1, If we move 1 step to left, we reach nums[1]. So result[2] should be 4.

Constraints :-
1 <= nums.length <= 100
-100 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(n)
vector<int> constructTransformedArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        int ind = i;
        if (nums[i] > 0)
            ind = (i + nums[i]) % n;
        else if (nums[i] < 0) {
            int absVal = abs(nums[i]);
            int stepsBack = absVal % n;
            ind = (i + n - stepsBack) % n;
        }
        
        ans[i] = nums[ind];     
    }
    
    return ans;
}

/*
| ind = ((i + nums[i]) % n + n) % n
The above formula works for both positive (forward movement) & negative (backward movement)

### How & Why it works ?
1️⃣ What are we trying to do?
You are at index i in a circular array of size n.
You want to move:
- forward if nums[i] > 0
- backward if nums[i] < 0
So mathematically, the new index should be: new_index = i + nums[i]
But this value can go: beyond n-1 or below 0
Example:
n = 5
i = 3
nums[i] = 4
new_index = 7   ❌ invalid index
Since the array is circular, index 7 should wrap around.

2️⃣ Circular movement = modulo
Modulo gives wrap-around behaviour.
7 % 5 = 2
So, new_index = (i + nums[i]) % n
works for positive overflow.
Example: (3 + 4) % 5 = 2 ... Correct.

3️⃣ Problem with negative numbers in C++
This is the key issue.
In mathematics: -1 mod 5 = 4
But in C++: -1 % 5 = -1
Example: 
i = 1
nums[i] = -3
n = 5
(1 - 3) % 5 = -2   ❌ invalid index
We need index 3, not -2.

4️⃣ How do we fix negative modulo?
Observation: Adding n does not change the position in a circular array.
Example: -2 + 5 = 3
Both represent the same circular position.
So we shift the result into positive range: (i + nums[i]) % n + n
Now: -2 + 5 = 3
But this might exceed n-1 in positive cases.
Example:
3 % 5 = 3
3 + 5 = 8   ❌ too large

5️⃣ Final step: bring back into range
So we apply % n again: ((i + nums[i]) % n + n) % n
Now the result is always: 0 ≤ index < n

6️⃣ Intuition
Think of it as:
| Move normally → wrap once → shift into positive range → wrap again.

(valid circular index) = (original movement wrapped) shifted into [0, n-1]
*/
vector<int> constructTransformedArray2(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        int ind = ((i + nums[i]) % n + n) % n;
        ans[i] = nums[ind];     
    }

    return ans;
}

int main() {

    return 0;
}