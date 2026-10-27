/*
Leetcode - 15. 3Sum : Medium

Given an integer array nums, 
return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, 
and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Examples :-

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

Constraints :-
• 3 <= nums.length <= 3000
• -10^5 <= nums[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n³ log m) __ Space Complexity : O(m)
/*
>> Intuition

We can use three nested loops to check every possible combination of three elements and find triplets whose sum is 0. 
We run j from i + 1 and k from j + 1, ensuring that i < j < k so we don't 
reuse the same element or check the same combination of indices repeatedly.

Since we need distinct triplets, we can use a set to store the triplets and avoid duplicates. 
However, there's a catch: the same triplet could be encountered in different orders. 
For example, [-1, 2, -1] and [-1, -1, 2] would be treated as different vectors by the set.

To handle this, whenever we find a triplet whose sum is 0, we sort the triplet before inserting it into the set. 
This ensures every triplet is stored in a consistent order, allowing the set to recognise and eliminate duplicates.

Finally, we convert the set into a vector and return the answer.

>> Complexity Analysis

- Time: O(n³ log m), where `m` is the number of unique triplets stored in the set. 
  The three nested loops take O(n³), and each set insertion takes O(log m). 
  Sorting each triplet takes O(1) because it contains only three elements.

- Space: O(m) for storing unique triplets in the set, excluding the output vector.
*/
vector<vector<int>> threeSumBrute(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    sort(temp.begin(), temp.end());     // sort the triplet so same triplets can be easily distinguished
                    // since temp is only of size 3, this sorting takes very less time, can be considered as O(1)
                    st.insert(temp);
                }
            }
        }
    }
    
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Better Approach (Using Hashing): Time Complexity : O(n² log m) __ Space Complexity : O(n + m)
/*
>> Intuition

Instead of using three nested loops to check every possible triplet, 
we can reduce the problem to finding two elements for each fixed element using a hash set.

We use an outer loop to fix the first element nums[i]. 
Then, for each nums[j] after it, we calculate the required complement:
    comp = -(nums[i] + nums[j])

If this complement exists in the hash set, it means we have already encountered 
an element that completes the triplet with nums[i] and nums[j], making their sum 0.

Whenever we find such a triplet, we sort it and insert it into a set, 
just like in the brute-force approach, to ensure that duplicate triplets are not stored.

The hash set stores elements encountered during the current inner-loop traversal. 
We insert nums[j] after checking for the complement, ensuring that we don't use the same element twice. 
We create a fresh hash set for each fixed nums[i].

Finally, we convert the set of unique triplets into a vector and return it.

Complexity Analysis:
-> Time: O(n² log m) 
    O(n²) average for the nested loops and hash lookups, plus O(log m) for each insertion into the set. 
    Overall, O(n² log m), where m is the number of unique triplets.

-> Space: O(n + m) — The hash set can store up to O(n) elements, and the set stores m unique triplets.
*/
vector<vector<int>> threeSumHashing(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;

    for (int i = 0; i < n - 2; i++) {
        unordered_set<int> hashset;
    
        for (int j = i + 1; j < n; j++) {
    
            int comp = - (nums[i] + nums[j]);
    
            if (hashset.find(comp) != hashset.end()) {
                vector<int> temp = {nums[i], nums[j], comp};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
    
            hashset.insert(nums[j]);
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Optimal Approach (Sorting + Two Pointers): Time Complexity : O(n log n) + O(n²) __ Space Complexity : O(1) 
/*
>> Intuition

First, sort the array so we can use the ordering of elements to efficiently find triplets. 
Then, use a loop to fix the first element nums[i]. 
For each fixed element, initialize two pointers: j = i + 1 and k = n - 1.

Calculate the sum of the three elements and adjust the pointers accordingly:
- If sum < 0: Move j right to increase the sum.
- If sum > 0: Move k left to decrease the sum.
- If sum == 0: We have found a valid triplet, so add it to the answer and move both pointers to search for other triplets.

Since we need distinct triplets, we must skip duplicate values in three places:

1. Skip duplicates for i:
    if (i > 0 && nums[i] == nums[i - 1])
        continue;

Because the array is sorted, duplicate values are adjacent. 
If nums[i] equals the previous element, we've already considered that value as the first element, so we skip it.

2. Skip duplicates for j:
    do {
        j++;
    } while (j < k && nums[j] == nums[j - 1]);

After finding a valid triplet, we move j forward at least once, 
then keep moving while its value equals the previous value. 
This prevents us from using the same second element value again.

3. Skip duplicates for k:
    do {
        k--;
    } while (j < k && nums[k] == nums[k + 1]);

Similarly, we move k backward at least once, then keep moving while its value equals the next value, 
avoiding repeated third element values.

The do-while loops guarantee that both pointers move at least once, while j < k ensures they don't cross.

By sorting the array, using two pointers, and skipping duplicates, 
we find all unique triplets without checking every possible combination.

>> Complexity Analysis:

- Time: O(n log n) + O(n²) — Sorting takes O(n log n), and the outer loop with the two-pointer traversal takes O(n²).
- Space: O(1) auxiliary space, excluding the output. 
  Sorting may use additional stack space depending on the implementation.
*/
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; i++) {
        // skip duplicates
        if (i > 0 && nums[i] == nums[i - 1]) continue;
    
        int j = i + 1, k = n - 1;
    
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
    
            if (sum < 0) j++;       // if sum < 0, we need to increase the sum, so move j
            else if (sum > 0) k--;  // if sum > 0, we need to decrease the sum, so move k
            // else, sum == 0
            else {
                vector<int> temp = {nums[i], nums[j], nums[k]};
                ans.push_back(temp);
                // move j & k to the next distinct values (skip duplicates)
                do {
                    j++;
                } while(j < k && nums[j] == nums[j - 1]);
                do {
                    k--;
                } while(j < k && nums[k] == nums[k + 1]);
            }
        }
    }

    return ans;
}

/*
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; i++) {
        // skip duplicates
        if (i > 0 && nums[i] == nums[i - 1]) continue;
    
        int left = i + 1, right = n - 1;
        int target_sum = -(nums[i]);
    
        while (left < right) {
            int sum = nums[left] + nums[right];
    
            if (sum < target_sum) left++;       // if sum < target_sum, we need to increase the sum, so move left
            
            else if (sum > target_sum) right--;  // if sum > target_sum, we need to decrease the sum, so move right
            
            // else, sum == target_sum
            else {
                vector<int> temp = {nums[i], nums[left], nums[right]};
                ans.push_back(temp);
                
                // move left & right to the next distinct values (skip duplicates)
                left++;
                while (left < right && nums[left] == nums[left - 1]) left++;
                right--;
                while(left < right && nums[right] == nums[right + 1]) right--;
            }
        }
    }

    return ans;
}
*/

int main() {
    return 0;
}