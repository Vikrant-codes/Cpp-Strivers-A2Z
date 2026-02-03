/*
Leetcode - 3349. Adjacent Increasing Subarrays Detection I : Easy

Given an array nums of n integers and an integer k, determine whether there exist two adjacent subarrays of length k 
such that both subarrays are strictly increasing. 
Specifically, check if there are two subarrays starting at indices a and b (a < b), where:
- Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
- The subarrays must be adjacent, meaning b = a + k.
Return true if it is possible to find two such subarrays, and false otherwise.

Examples :- 

Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3 __ Output: true
Explanation:
The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
These two subarrays are adjacent, so the result is true.

Input: [19,5], k = 1 __ Output: true
Explanation: [19] & [5] are two strictly increasing adjacent subarrays of size 1.

Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5 __ Output: false

Constraints :- 
2 <= nums.length <= 100
1 < 2 * k <= nums.length
-1000 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force : Time Complexity : O(n x k) __ Space Complexity : O(1)
/*
Brute force — check every possible pair of adjacent subarrays
🧠 Intuition
The problem asks whether there exist two consecutive subarrays (one right after the other), each of length k, 
that are strictly increasing.
So, the idea is:
- Slide a window of size 2k across the array — starting at every valid i (i from 0 to n - 2k).
- For each position:
--> Check if the subarray [i, i + k - 1] is strictly increasing.
--> Check if the next subarray [i + k, i + 2k - 1] is strictly increasing.
- If both are increasing for any position i, return true.
The helper function isIncreasing() does the check for a given subarray in O(k) time.

⏱️ Complexity Analysis
Outer loop runs: O(n − 2k + 1) ≈ O(n)
Each isIncreasing() call: O(k)
Two such calls per iteration → O(2k)
✅ Total Time Complexity: O(n×k)
✅ Space Complexity: O(1) - (only a few variables used; no extra data structures)
*/
bool isIncreasing(vector<int> arr, int start, int k) {
    for (int i=start+1; i<start+k; i++) {
        if (arr[i] <= arr[i-1]) return false;
    }
    return true;
}
bool hasIncreasingSubarraysBrute(vector<int>& nums, int k) {
    int n = nums.size();
    for (int i = 0; i <= n-2*k; i++) {
        if (isIncreasing(nums, i, k) && isIncreasing(nums, i+k, k)) 
            return true;
    }
    return false;
}

// Naive Approach (Slightly better than Brute) :- Time Complexity : O(n x k) __ Space Complexity : O(1)
/*
Naive Approach :-
For each strictly increasing subarray of size k, check whether its adjacent k-sized subarray is strictly increasing or not.
If yes, return true.

🧠 Intuition
1. Iterate through the array and maintain cnt — the length of the current strictly increasing streak.
- If nums[i] > nums[i - 1], increment cnt.
- Else, reset cnt to 1.
2. Whenever the streak length cnt becomes at least k, → it means the previous k elements form one valid increasing subarray.
3. Now, you check whether the next k elements (i.e., the adjacent subarray starting at i + 1) also form a 
strictly increasing sequence by running a short inner loop (cnt2).
4. If both satisfy the condition, return true.

⏱️ Complexity Analysis

- Outer loop → O(n)
- Inner loop (only runs when cnt ≥ k) → at most O(k) work (in the worst case, this happens many times)

✅ Worst-case Time Complexity: O(n x k)
✅ Average Case: If increasing runs are short, inner loop runs rarely → O(n) amortized in practice.

✅ Space Complexity: O(1)
*/ 
bool hasIncreasingSubarraysNaive(vector<int>& nums, int k) {
    int cnt = 0;    // count of continuously strictly increasing elements

    for (int i=0; i<nums.size()-k; i++) {
        if (i == 0 || nums[i] > nums[i-1]) cnt++;
        else cnt = 1;
        // if count >= k, check whether the adjacent subarray is strictly increasing or not
        if (cnt >= k) {
            int cnt2 = 0;
            for (int j=i+1; j <= i+k; j++) {
                if (j == i+1 || nums[j] > nums[j-1]) cnt2++;
            }
            if (cnt2 == k) return true;
        }
    }
    return false;
}

// Better Approach :- Time Complexity : O(n) __ Space Complexity : O(m)
/*
🧠 Intuition
Find and store all starting indices of strictly increasing subarrays of length k,
then check whether two such subarrays occur adjacent to each other.

Here’s what happens step by step:
1. Building increasing runs
- You use a counter cnt to track how long the current strictly increasing streak is.
- Whenever cnt >= k, it means there exists a k-length strictly increasing subarray ending at index i. 
  ⇒ So, its starting index = i - k + 1.
- You store this start index in a set st.
Example: nums = [1, 2, 3, 3, 4, 5], k = 3
→ Strictly Increasing Subarrays [1,2,3], [3,4,5] start at 0 and 3
→ So, we'll insert {0, 3} into the set.

2. Checking adjacency
- Two increasing subarrays are adjacent if their start indices differ by exactly k.
- So for every x in st, you just check if st also contains x + k.
- If yes → you found two adjacent strictly increasing subarrays of size k, return true.

⚙️ Time Complexity
- Single pass to build set: O(n)
- Checking adjacency (loop over set): each lookup is O(1) average (unordered_set) 
⇒ Total still O(n) overall.
✅ Final Time Complexity: O(n)
✅ Space Complexity: O(m), where m = number of increasing subarrays of length k (worst case ≤ n)

💡 Extra Notes
- The condition if (k == 1) return true; is correct — any two adjacent elements form valid subarrays.
- The use of unordered_set ensures O(1) lookups, which makes it truly linear in runtime.
*/
bool hasIncreasingSubarraysBetter(vector<int>& nums, int k) {
    if (k == 1) return true;
    unordered_set<int> st;
    int cnt = 1;
    for(int i=1; i<nums.size(); i++) {
        if (nums[i] > nums[i-1]) cnt++;
        else cnt = 1;
        if (cnt >= k) st.insert(i-k+1);
    }
    for (int x : st) {
        if (st.count(x+k)) return true;
    }
    return false;
}

// Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🧠 Intuition
We want two consecutive increasing subarrays of length k.
Instead of tracking all starts or ends:
1. Track currRun → length of the current strictly increasing streak.
2. Track prevRun → length of the previous strictly increasing streak (before the current break).
3. At each index:
- If currRun >= 2*k, it means the current streak alone is long enough to contain 
  two consecutive subarrays of length k → return true.
- If min(currRun, prevRun) >= k, it means the current streak and the previous streak together 
  can form two adjacent subarrays → return true.

⚙️ Algorithm Step-by-Step
1. Initialize currRun = 1 (first element starts a streak) and prevRun = 0.
2. Iterate from i = 1 to n-1:
- If nums[i] > nums[i-1], increment currRun.
- Else:
--> prevRun = currRun (store the last increasing streak)
--> currRun = 1 (reset for the new streak)
- Check:
--> If currRun >= 2*k → true
--> If min(currRun, prevRun) >= k → true
3. Return false if loop finishes without finding any valid pair.

⏱ Complexity Analysis
Time: O(n) — single pass through the array.
Space: O(1) — only two integer counters used.
*/
bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    int currRun = 1, prevRun = 0;
    
    for (int i=1; i<n; i++) {
        if (nums[i] > nums[i-1]) currRun++;
        // else when Increasing streak breaks
        else {
            prevRun = currRun;  // store the current streak as previous
            currRun = 1;        // reset the current streak
        }
        // if current streak >= 2k, it alone is sufficient enough to hold at least 2 subarrays of size k
        if (currRun >= 2*k) return true;
        // if both currRun & prevRun >= k, then we can find two adjacent k sized subarrays, so return true
        if (min(currRun, prevRun) >= k) return true;
    }

    return false;
}

int main() {
    vector<int> nums = {2,5,7,8,9,2,3,4,3,1};
    vector<int> nums2 = {-15,-13,4,7};
    int k = 3;
    int k2 = 2;
    cout << hasIncreasingSubarrays(nums2, k2);

    return 0;
}