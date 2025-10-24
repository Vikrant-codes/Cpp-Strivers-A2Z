/*
Leetcode - 611. Valid Triangle Number : Medium

Given an integer array nums, return the number of triplets chosen from the array that can make triangles 
if we take them as side lengths of a triangle.

Examples :-

Input: nums = [2,2,3,4] __ Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Input: nums = [4,2,3,4] __ Output: 4

Constraints : 1 <= nums.length <= 1000 __ 0 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Two Pointers Approach) : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
🔹 Intuition
- A triangle is valid if the sum of two smaller sides > largest side.
- After sorting the array:
  For any triplet (a, b, c) where a ≤ b ≤ c,
  the only inequality we need to check is a + b > c (other two will always hold after sorting).
- So the key problem reduces to:
  For each possible largest side c, count how many pairs (a, b) exist such that a + b > c.

Now, how to do this efficiently?
- Suppose we fix nums[k] as the largest side.
- We use two pointers (i starting from 0, j starting from k-1) to explore pairs.
- If nums[i] + nums[j] > nums[k], then:
-- Since the array is sorted, all numbers from i up to j-1 with nums[j] will also form valid pairs with nums[k].
-- So we can add (j - i) to our count in one shot, and then move j-- to explore the next smaller side.
- Otherwise (nums[i] + nums[j] ≤ nums[k]), nums[i] is too small → increment i to try a bigger number.

This avoids checking each pair explicitly and reduces the brute-force O(n³) to O(n²).

🔹 Algorithm
1. Sort the array nums in ascending order.
2. Initialize count = 0.
3. For k from n-1 down to 2:
   Let i = 0, j = k-1.
   While i < j:
      If nums[i] + nums[j] > nums[k]:
         Add (j - i) to count.
         Decrement j.
      Else: increment i.
4. Return count.

🔹 Complexity
Sorting: O(n log n)
Two-pointer scan for each k: O(n²)
Overall: O(n²) time, O(1) extra space.
*/
int triangleNumber(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    int n = nums.size();
    int cnt = 0;

    for (int k = n - 1; k > 1; k--) {
        int i = 0, j = k - 1;
        while (i < j) {
            if (nums[i] + nums[j] > nums[k]) {
                // all the numbers between nums[i] to nums[j] will also form pair with nums[j], so add these count and decrement j
                cnt += (j - i); 
                j--;
            }
            // if ith & jth doesn't sum more than kth then simply increment i
            else
                i++;
        }
    }
    return cnt;
}

int main()
{
    return 0;
}