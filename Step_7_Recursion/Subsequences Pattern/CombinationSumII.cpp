/*
Leetcode - 40. Combination Sum II : Medium

Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.

Examples :-

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [ [1,1,6], [1,2,5], [1,7], [2,6] ]

Input: candidates = [2,5,2,1,2], target = 5
Output: [ [1,2,2], [5] ]

Constraints :-
• 1 <= candidates.length <= 100
• 1 <= candidates[i] <= 50
• 1 <= target <= 30
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n logn + 2^n + K L logK + K L) __ Space Complexity : O(n + KL)
/*
>> Intuition
Unlike LeetCode 39, where an element can be picked unlimited times, here each element can be picked at most once. 
Therefore, the pick/not-pick recursion simply explores all subsets whose sum is target.

However, the array can contain duplicate values. This means different subsets of indices can produce the same combination, 
so whenever we find a valid combination, we store it in a set to keep only unique combinations.

We sort the array first so that duplicate values are adjacent and every combination is generated in the same sorted order. 
Otherwise, combinations such as [1,2,1] and [1,1,2] could be considered different by the set, 
even though they represent the same combination.

Sort → generate all subsets using pick/not-pick → store valid combinations in a set to eliminate duplicates.

----------------------------------------------------------------------------
>> Complexity Analysis

For this naive Combination Sum II solution, there are two important differences from `LeetCode 39 - Combination Sum`:
- Every element can be picked at most once, so recursion depth is at most n.
- We're using a set<vector<int>>, so inserting a valid combination involves both copying the vector and set insertion cost.

Let:
• n = number of candidates
• K = number of unique valid combinations
• L = maximum length of a valid combination (L ≤ n)

-> Time Complexity: O(n logn + 2^n + K L logK + K L)

1. Sorting: sort(candidates.begin(), candidates.end()); → `O(n logn)`

2. Recursive search
At every element, we have two choices: pick & not pick, 
and unlike Combination Sum I, we can only pick an element once and always move to ind + 1.
Therefore, in the worst case, the recursion explores essentially all subsets: `O(2^n)`
The work done at each recursive call is O(1), apart from the valid-combination insertion discussed below.

3. ans.insert(ds)
When k == 0: ans.insert(ds);
There are two costs here.
- Copying ds 
    A combination can contain up to L elements, so: O(L)
- Inserting into set
    set is typically a balanced BST, so finding the insertion position costs: O(log S)
    where S is the current number of vectors in the set.
    But comparing two vector<int> objects is not necessarily O(1). In the worst case, vector comparison can take O(L).
    Therefore: O(L logS), for a set<vector<int>> insertion.
    With K unique valid combinations, total insertion cost:  O(K L logK).

4. Converting set → vector
vector<vector<int>> res(ans.begin(), ans.end());
There are K vectors, each potentially containing L elements: O(K L)

# Final Time Complexity
Combining everything : O(n logn + 2^n + K L logK + K L)
Since KL is dominated by KL log K when K > 1: O(n logn + 2^n + K L logK)

-> Space Complexity: O(n + KL)
1. Recursion stack:- Since every recursive call advances ind: O(n)
2. ds:- At most n elements: O(n)
3. set<vector<int>> ans:- There can be K unique combinations, each of length at most L: O(KL)
4. Final res:- We create another copy of all K combinations (the actual result vector): O(KL)

So total space: O(n + KL)

>> Final Complexity summary
| Component        |                        Complexity |
| ---------------- | --------------------------------: |
| Sorting          |                      `O(n log n)` |
| Recursive search |                          `O(2^n)` |
| `set.insert(ds)` |                     `O(KL log K)` |
| Set → vector     |                           `O(KL)` |
| **Total Time**   | **`O(n log n + 2^n + KL log K)`** |
| Recursion stack  |                            `O(n)` |
| `ds`             |                            `O(n)` |
| Set storage      |                           `O(KL)` |
| **Space**        |                   **`O(n + KL)`** |
*/
void findCombinations(vector<int>& arr, int ind, int k, set<vector<int>>& ans, vector<int>& ds) {
    if (k == 0) {
        ans.insert(ds);
        return;
    }

    if (ind == arr.size() || k < 0) 
        return;
    
    // pick the current element
    ds.push_back(arr[ind]);
    findCombinations(arr, ind + 1, k - arr[ind], ans, ds);

    // not pick the current element
    ds.pop_back();
    findCombinations(arr, ind + 1, k, ans, ds);
}
vector<vector<int>> combinationSum2Naive(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    set<vector<int>> ans;
    vector<int> ds;
    findCombinations(candidates, 0, target, ans, ds);
    vector<vector<int>> res(ans.begin(), ans.end());
    return res;
}

// Optimal Approach
// To avoid duplicate combinations, we try to avoid exploring equivalent duplicate branches.

// Optimal Approach-1 (Striver's Solution): Time Complexity: O(n logn + 2^n + KL) __ Space Complexity: O(n + KL)
/*
>> Intuition

The main challenge compared to Combination Sum I (LeetCode 39) is that:
- Each element can be used at most once, so after choosing an element we must move to the next index.
- The input may contain duplicate values, but the result must contain only unique combinations.

A straightforward solution would be to generate all subsets and use a set to remove duplicates. 
However, this generates many duplicate combinations that are eventually discarded. 
Instead, we would like to avoid generating duplicates in the first place.

To achieve this, we first sort the array. 
Sorting brings equal values together, which makes it easy to detect and skip duplicates during recursion.

Now, rather than using an explicit pick/not-pick recursion for every element, we think of the problem as:
    | "At the current recursion level, which element should I choose as the next element of my combination?"

This is naturally implemented using a for loop. 
For every index i starting from ind, we can choose arr[i] as the next element, add it to the current combination, 
and recursively search for the remaining target using only the elements that come after it.
    | getCombinations(arr, i + 1, target - arr[i], ans, ds);
Notice that we recurse with i + 1, not i. This ensures that each element is used at most once.

>> Why do we skip duplicates?
Consider: arr = [1, 1, 2, 3]
At the top level (ind = 0), the loop can choose either the first 1 or the second 1.
If we start a branch with the first 1 and another branch with the second 1, 
both branches will explore exactly the same possibilities and eventually generate the same combinations. 
Therefore, exploring both is redundant.
To avoid this, whenever we encounter a value that is the same as the previous value at the same recursion level, we skip it:
    | if (i > ind && arr[i] == arr[i - 1]) continue;
The condition i > ind is important because we only want to skip duplicates at the current level.

For example: [1, 1, 2]
The combination [1,1,2] is valid and should still be generated. 
After choosing the first 1, the recursive call moves to the next level, 
where choosing the second 1 is perfectly allowed. 
We only skip the second 1 when it would start a new branch at the same level as the first 1.

>> Why can we break when arr[i] > target?
Since the array is sorted, once we encounter an element larger than the remaining target:
    | if (arr[i] > target) break;
every element after it will also be larger.
Therefore, none of the remaining candidates can contribute to a valid combination, 
and we can stop exploring that recursion level immediately.

>> Overall Idea
1. Sort the array so duplicates become adjacent.
2. At each recursion level, try every possible candidate as the next element of the combination.
3. After choosing an element, recurse from i + 1 so that it cannot be reused.
4. Skip duplicate values at the same recursion level to avoid generating the same combination multiple times.
5. Stop early when the current candidate exceeds the remaining target.

Instead of generating all subsets and removing duplicates afterward, 
the algorithm uses sorting and duplicate-skipping to ensure that each valid combination is generated exactly once.
--------------------------------------------------------------------

>> Complexity Analysis

Let:
• n = number of candidates
• K = number of valid combinations
• L = maximum length of a valid combination, L ≤ n

-> Time Complexity

1. Sorting: O(nlogn)

2. Recursive search:
The recursion explores subsets of the candidates. In the worst case, there can be exponentially many possibilities: O(2^n)

3. Storing results: 
ans.push_back(ds); copies the current combination, costing O(L).
For K valid combinations: O(KL)

Therefore, total time: O(n logn + 2^n + KL)

-> Space Complexity

1. Recursion stack: Every recursive call moves from i to i + 1, so maximum depth: O(n)
2. Current combination ds: At most n elements: O(n)
3. Output: K combinations, each up to length L: O(KL)
Therefore, space complexity (including the output): O(n + KL)
*/

// Function to find all combinations of numbers that sum up to the target
void getCombinations(vector<int>& arr, int ind, int target, vector<vector<int>>& ans, vector<int>& ds) {
    // Base case: If the target becomes 0, we found a valid combination
    if (target == 0) {
        ans.push_back(ds);      // Add the current combination to the result
        return;
    }

    // if (ind == arr.size()) return;
    // this return check is not needed as when ind == arr.size(), 
    // the for loop won't run and the recursive function will automatically return

    // Loop through the elements starting from index 'ind'
    for (int i = ind; i < arr.size(); i++) {
        // Skip duplicates to avoid repeating combinations
        if (i > ind && arr[i] == arr[i-1]) continue;
    
        // If the current element is greater than the remaining target, break the loop
        if (arr[i] > target) break;
    
        // Include the current element in the combination
        ds.push_back(arr[i]);
        // Recur with the updated target and next index (i + 1 to avoid repetition)
        getCombinations(arr, i+1, target - arr[i], ans, ds);
        // Backtrack by removing the last added element
        ds.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());         // Sort the candidates to handle duplicates
    vector<int> ds;                                     // Stores current combination 
    vector<vector<int>> ans;                            // Stores all valid combinations 
    getCombinations(candidates, 0, target, ans, ds);   
    return ans;                                         // return all the valid combinations
}

// Optimal Approach 2: Time Complexity : O(n logn + 2^n + KL) __ Space Complexity : O(n + KL)
/*
>> Intuition
This solution uses the same pick / not-pick idea as the earlier approaches, 
but optimizes the not-pick branch to skip all duplicate values at once.

Since each element can be used at most once, when we pick arr[ind], we move to ind + 1:
    | findCombinations(arr, ind + 1, target - arr[ind], ans, ds);
So the current element cannot be picked again.

The interesting part is the not-pick branch.
Because the array is sorted, all occurrences of the current value are next to each other. Suppose we have:
    [1, 1, 1, 2, 3]
     ^
     ind
If we decide not to pick the current 1, there is no reason to try the other 1s individually as separate branches. 
Picking the second 1 as the first element of a branch would produce the same combinations as picking the first 1.

Therefore, we find the first index containing a different value:
    | int j = ind + 1;
    | while (j < arr.size() && arr[j] == arr[ind])
    |     j++;
and directly recurse from j:
    | findCombinations(arr, j, target, ans, ds);
So instead of doing:
- not pick 1 → try next 1
- not pick 1 → try next 1
- not pick 1 → try 2
we effectively do: not pick 1 → skip all 1s → try 2
This avoids generating duplicate branches without needing a set.

>> Why do we still allow duplicate values to be picked?
Consider: [1, 1, 2]
Suppose we pick the first 1:
ds = [1]
The recursive call goes to ind + 1, which points to the second 1. 
We are allowed to pick it because these are two different elements: [1, 1]
So duplicates are not globally skipped. 
We only skip them when they would create duplicate branches for the not-pick decision.

>> Why the early returns work? 
Because the array is sorted and all candidates are positive:
    | if (ind == arr.size() || arr[ind] > target)
    |     return;
If the current candidate is already greater than the remaining target, 
every candidate after it will also be greater, so there is nothing useful to explore.
Similarly, after skipping duplicates:
    | if (j == arr.size() || arr[j] > target)
    |     return;
there is no valid not-pick branch left to explore.

>> Overall Idea
Use pick/not-pick recursion, but when not picking an element, 
skip all of its duplicate occurrences and jump directly to the next distinct value. 
Since the array is sorted, this eliminates duplicate branches while still allowing 
duplicate values to be selected when they represent different elements.
--------------------------------------------------------------------------------

>> Complexity Analysis

Let:
• n = number of candidates
• K = number of valid combinations
• L = maximum length of a valid combination, with L ≤ n

-> Time Complexity: O(n logn + 2^n + KL)

1. Sorting :- sort(candidates.begin(), candidates.end()); -> O(n logn)

2. Recursive search
The recursion is still based on pick / not-pick, so in the worst case it can explore exponentially many states: 
    O(2^n)
However, the not-pick branch additionally does:
    | int j = ind + 1;
    | while (j < arr.size() && arr[j] == arr[ind])
    |     j++;
In the worst case, this while loop can take O(n) for a recursive state.
But the important thing is that the while loop is not an additional independent traversal of the search tree. 
It is specifically skipping duplicate choices.

Consider 
- Case 1: No duplicates
For an array like: [1, 2, 3, 4, 5]
the loop executes only once at each call:
    | j = ind + 1
    | arr[j] != arr[ind]
So that's effectively: O(1) per recursive node

- Case 2: Many duplicates
Suppose: [1, 1, 1, 1, 1, 2, 3]
If we're at the first 1 and choose not to pick it, the while loop jumps directly: 1 → 2
instead of recursively creating separate branches for:
    skip 1st 1
    skip 2nd 1
    skip 3rd 1
    skip 4th 1
    ...
Those duplicate branches are precisely what we're trying to eliminate.
So the cost of scanning duplicates is essentially being exchanged for avoiding recursive work.

Thus, we can consider that this while loop is not taking any extra time as the time taken will be exchanged
by avoiding the duplicate recurive branch calls. 
Thus, time for recurive search will practically remain: O(2^n)

3. Storing valid combinations
When: ans.push_back(ds); executes, ds is copied.
Each combination can have up to L elements, so one insertion costs: O(L)
For K valid combinations: O(KL)

| Final Time Complexity
Combining everything: O(n logn + 2^n + KL)
where KL represents the cost of actually producing the output

-> Space Complexity: O(n + KL)

1. Recursion stack: 
Each recursive call moves to a larger index: ind + 1, or jumps forward to j.
Therefore, maximum recursion depth is: O(n)

2. ds: At most n elements: O(n)
3. Output: The result contains K combinations of maximum length L: O(KL)

Therefore, total space including the output: O(n + KL)
*/

void findCombs(vector<int>& arr, int ind, int target, vector<vector<int>>& ans, vector<int>& ds) {
    // If target has become 0, add the current combination to result vector & return
    if (target == 0) {
        ans.push_back(ds);
        return;
    }
    // If array has been fully traversed/current element > target, then return
    if (ind == arr.size() || arr[ind] > target) return;

    // pick current element
    ds.push_back(arr[ind]);
    findCombs(arr, ind + 1, target - arr[ind], ans, ds);
    ds.pop_back();
    
    // not-pick current element -> skip all duplicates and move to the next distinct element for the pick/not-pick choice
    int j = ind+1;
    while (j < arr.size() && arr[j] == arr[ind]) j++;
    // j now points at the next distinct element
    
    // if j == array size, or, the jth element > target, no need for further recursive calls, return
    if (j == arr.size() || arr[j] > target) return;

    findCombs(arr, j, target, ans, ds);     // not-pick current element recursive call
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<int> ds;
    vector<vector<int>> ans;
    findCombs(candidates, 0, target, ans, ds);
    return ans;
}

int main() {
    return 0;
}