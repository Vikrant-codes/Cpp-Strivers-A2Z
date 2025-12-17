/*
Leetcode - 2824. Count Pairs Whose Sum is Less than Target : Easy

Given a 0-indexed integer array nums of length n and an integer target, return the number of pairs (i, j) 
where 0 <= i < j < n and nums[i] + nums[j] < target.

Examples :-

Input: nums = [-1,1,2,3,1], target = 2 __ Output: 3

Input: nums = [-6,2,5,-2,-7,-1,3], target = -2 __ Output: 10

Constraints :-
-> 1 <= nums.length == n <= 50
-> -50 <= nums[i], target <= 50
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force :- Time Complexity : O(n^2) __ Space Complexity : O(1)
// Check the sum of all possible pairs of nums and count those whose sum is smaller than target.
int countPairsBrute(vector<int>& nums, int target) {
    int n = nums.size();
    int cnt = 0;
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (nums[i] + nums[j] < target) cnt++;
        }
    }
    return cnt;
}

// Sorting + Binary Search :- Time Complexity : O(n * log n) + O(n * log n) __ Space Complexity : O(1)
/*
⭐ Approach 1 — Sorting + Binary Search

✅ Problem Summary
Given an array nums and a target, count all pairs (i, j) such that: i < j  AND  nums[i] + nums[j] < target

✅ Intuition
Sort the array and then for each element nums[i], we want to count (i, j) pairs such that 
num[i] + nums[j] < target, or, nums[j] < target - nums[i].
Let x = target - nums[i]. So, we need to find those elements which are smaller than x, since only they can form pairs.
So, we need to count all those elements to the right of nums[i] which are smaller than x.
This is a classic find last index < X problem → suited for binary search.
So, using Binary Search we find the last index 'k' such that nums[k] < X and nums[k+1] >= X.
If binary search finds the last such index k, then: count of valid pairs = k - i

🧠 Algorithm 
1. Sort the array.
2. Initialize n = nums.size(), cnt = 0.
2. For each index i in range [0, n-1):
    • Compute x = target - nums[i]. 
    • Use Binary Search to find the largest element < X in the right half and count the pairs.
    • If this count_pairs is 0, means nums[i] don't form any valid pairs and also all the larger elements left in the array 
    won't form the pairs also. So, break
    • add count_pairs to cnt. i.e., cnt += count_pairs
3. Return total count : cnt.

🧠 Algorithm for Binary Search :- pairs(vector<int>& nums, int i, int n, int x) 
1. Initialize low = i+1, high = n-1.
2. while (low <= high) :
    • compute mid = (low + high) / 2
    • if (nums[mid] >= x): high = mid - 1. (Since we want smaller element)
    • else: low = mid + 1.
3. Return high - i. (After loop ends, high will point to the largest element < X. so count pairs = high - i).

⏱️ Time & Space Complexity
| Step                          | Complexity                   |
| ----------------------------- | ---------------------------- |
| Sorting                       | `O(n log n)`                 |
| For each index, binary search | `O(n log n)`                 |
| **Total**                     | **O(n log n)**               |
| Space                         | `O(1)` (if sorting in-place) |
*/
int pairs(vector<int>& nums, int i, int n, int x) {
    int low = i+1, high = n-1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] >= x) high = mid - 1;
        else low = mid + 1;
    }
    return high - i;
}

int countPairsBinary(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int cnt = 0;
    for (int i=0; i<n-1; i++) {
        int x = target - nums[i];
        int count_pairs = pairs(nums, i, n, x);
        if (count_pairs == 0) break;
        cnt += count_pairs;
    }
    return cnt;
}

// Optimal Approach (Sorting + Two Pointers) :- Time Complexity : O(n * log n) + O(n) __ Space Complexity : O(1) 
/*
⭐ Approach 2 — Sorting + Two Pointers (Optimal)

🎯 Intuition
Sort the array and use two pointers i & j. Initialize i = 0, j = n - 1.
Now, we see that 
If nums[i] + nums[j] >= target, then we need to reduce the sum, So move j left as left contains smaller elements/

If nums[i] + nums[j] < target, then ALL elements between i+1 to j also form valid pairs with nums[i].
So instead of counting one pair, you can count (j - i) pairs at once.

🧠 Algorithm
1. Sort the array.
2. Initialize two pointers: i=0, j=n-1.
3. While i < j:
    • If nums[i] + nums[j] < target:
        • All elements between i & j also form pair with i.
        • Add (j - i) to count.
        • Move i++ to explore next base element.
    • Else:
        • Sum too big → move j-- to decrease sum.
4. Return the total count.

⏱️ Time & Space Complexity
| Step              | Complexity     |
| ----------------- | -------------- |
| Sorting           | `O(n log n)`   |
| Two-pointer sweep | `O(n)`         |
| **Total**         | **O(n log n)** |
| Space             | `O(1)`         |

<<< Two-pointers is faster in practice because it removes the log factor from the loop. >>>
*/
int countPairs(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int cnt = 0;
    int i = 0, j = n - 1;
    while (i < j) {
        int sum = nums[i] + nums[j];
        if (sum < target) {
            cnt += (j - i);
            i++;
        }
        else j--;
    }
    return cnt;
}

/*
📌 Summary Table
| Approach             | Technique                                 | Time           | Space  | Notes             |
| -------------------- | ----------------------------------------- | -------------- | ------ | ----------------- |
| **1. Binary Search** | Sort + for each element use binary search | `O(n log n)`   | `O(1)` | Good but slower   |
| **2. Two Pointers**  | Sort + sweep                              | **O(n log n)** | `O(1)` | Best and simplest |
*/

int main() {
    return 0;
}