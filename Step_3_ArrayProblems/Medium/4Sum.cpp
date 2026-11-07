/*
Leetcode - 18. 4Sum : Medium

Given an array nums of n integers, 
return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

- 0 <= a, b, c, d < n
- a, b, c, and d are distinct.
- nums[a] + nums[b] + nums[c] + nums[d] == target

You may return the answer in any order.

Examples :-

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

Constraints :-
• 1 <= nums.length <= 200
• -10^9 <= nums[i] <= 10^9
• -10^9 <= target <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(N⁴ log M) __ Space Complexity : O(M)
/*
>> Intuition

Since we need to find four elements whose sum equals the target, 
the most straightforward approach is to consider every possible combination of four indices.

We use four nested loops to select four elements, ensuring that their indices are distinct (i < j < k < l). 
For every combination, calculate the sum and check whether it equals the target.

However, the problem asks for unique quadruplets, not unique index combinations. 
So, even if different combinations produce the same quadruplet, we must include it only once. 
We can sort each valid quadruplet and use a set to avoid duplicates.

>> Complexity Analysis
- Time: O(N⁴ log M), where M is the number of unique quadruplets, due to set insertion. The four loops take O(N⁴).
- Space: O(M) for storing unique quadruplets.
*/
vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;

    for(int i = 0; i < n - 3; i++) {
        for(int j = i + 1; j < n - 2; j++) {
            for(int k = j + 1; k < n - 1; k++) {
                for(int l = k + 1; l < n; l++) {

                    long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];

                    if(sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }

                }
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}

// Better Approach (Using Hashing): Time Complexity : O(N³) __ Space Complexity : O(N + M)
/*
>> Intuition

We can reduce one nested loop by using hashing.
Instead of explicitly searching for all four elements, we fix the first two elements 
and then search for the remaining two using a hash set.

Suppose we have fixed nums[i] and nums[j]. We need two more elements whose sum is:
  remaining = target - nums[i] - nums[j]

Now, we iterate through the remaining elements using k. 
For every nums[k], we calculate the value we need to complete the quadruplet:
  required = remaining - nums[k]

If required already exists in our hash set, we have found a valid quadruplet. 
Otherwise, we insert nums[k] into the set so that it can be used as the required element for a future iteration.

To handle duplicates, we sort the resulting quadruplet and store it in a set of vectors. 
This ensures that every unique quadruplet is included only once.

>> Complexity Analysis
- Time: Average O(N³) for the loops and hash lookups, plus the cost of set insertions.
- Space: O(N + M) for the hash set and unique quadruplets.
*/
vector<vector<int>> fourSumHashSet(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;

    for(int i = 0; i < n - 3; i++) {
        for(int j = i + 1; j < n - 2; j++) {

            unordered_set<long long> hashSet;
            long long remaining = (long long)target - nums[i] - nums[j];

            for(int k = j + 1; k < n; k++) {

                long long required = remaining - nums[k];

                if(hashSet.count(required)) {
                    vector<int> temp = { nums[i], nums[j], nums[k], (int)required };

                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }

                hashSet.insert(nums[k]);
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}

// Optimal Approach (Sorting + Two Pointers): Time Complexity : O(N³) __ Space Complexity : O(1)
/*
>> Intuition

The key observation is that sorting the array allows us to use the two-pointer technique 
to find the remaining two elements efficiently.

First, sort the array. Then, instead of using four nested loops, 
we fix the first two elements using two loops (i and j) and 
use two pointers (k and l) to find the remaining two elements.

For every fixed pair nums[i] and nums[j], we need: nums[k] + nums[l] = target - nums[i] - nums[j]

We initialize k = j + 1 and l = n - 1, and calculate the sum of all four elements.

- If the sum is smaller than the target, we need a larger sum, so we move k forward.
- If the sum is greater than the target, we need a smaller sum, so we move l backward.
- If the sum equals the target, we have found a valid quadruplet. 
  Store it and move both pointers while skipping duplicate values.

>> Handling duplicates :-

Since we need unique quadruplets, we skip duplicate values at every level:
1. Skip duplicate values for i.
2. Skip duplicate values for j.
3. After finding a valid quadruplet, skip duplicate values for both k and l.

This works because the array is sorted, so duplicate values are adjacent.

>> Complexity Analysis
- Time: O(N³). Sorting takes O(N log N), and the two fixed loops combined with the two-pointer traversal take O(N³).
- Space: O(1) auxiliary space, excluding the output and sorting implementation's stack space.
*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());

    for(int i = 0; i < n - 3; i++) {
        // avoid the duplicates while moving i
        if(i > 0 && nums[i] == nums[i - 1])
            continue;

        for(int j = i + 1; j < n - 2; j++) {
            // avoid the duplicates while moving j
            if(j > i + 1 && nums[j] == nums[j - 1])
                continue;

            int k = j + 1;
            int l = n - 1;

            while(k < l) {
                long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];

                if(sum < target) k++;
                else if(sum > target) l--;
                else {
                    ans.push_back({nums[i], nums[j], nums[k], nums[l]});

                    k++; l--;

                    //skip the duplicates
                    while(k < l && nums[k] == nums[k - 1]) k++;
                    while(k < l && nums[l] == nums[l + 1]) l--;
                }
            }
        }
    }

    return ans;
}

int main() {
    return 0;
}