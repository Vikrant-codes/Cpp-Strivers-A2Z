/*
Leetcode - 39. Combination Sum : Medium

Given an array of distinct integers candidates and a target integer target, 
return a list of all unique combinations of candidates where the chosen numbers sum to target. 
You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. 
Two combinations are unique if the frequency of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations 
that sum up to target is less than 150 combinations for the given input.

Examples :-

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Input: candidates = [2], target = 1
Output: []

Constraints :-
• 1 <= candidates.length <= 30
• 2 <= candidates[i] <= 40
• All elements of candidates are distinct.
• 1 <= target <= 40
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach

/*
The key idea is to make two choices at every index: either include the current candidate in the combination or skip it.
• Pick: Add arr[ind] to the current combination and stay at the same index because an element can be chosen unlimited times.
    • Reduce the remaining target: k - arr[ind].
• Not Pick: Don't include arr[ind] and move to the next index.

So the recursion forms a decision tree like:
            arr[ind]
           /        \
        PICK       NOT PICK
         |            |
    use again      move ahead

The important distinction from the usual subsequence pattern is:
| Pick → stay at ind
| Not Pick → move to ind + 1

For example, with [2,3] and target 7:

    Pick 2 → [2]
        Pick 2 → [2,2]
            Pick 2 → [2,2,2] ...
            Not pick → consider 3
        Not pick → consider 3
    Not pick 2 → consider 3

The base case checks whether we've reached the end, 
if so check if current combination sum equals k (or, k == 0) and add it to result.

And because candidates are positive, we can safely avoid the pick branch when: arr[ind] > k
since picking it would make the remaining sum negative.
*/

// Complexity Analysis
/*
The complexity is a little more subtle than simply saying O(2^n), because picking does not advance ind.

Let:
• n = number of candidates
• T = target
• m = minimum candidate
• M = ⌊T/m⌋ = maximum possible length of a combination
• K = number of valid combinations produced

Since candidates are positive, if the smallest candidate is m, then: M = M = ⌊ T / m ​⌋ i.e., floor (T / m)
ex- T = 40, m = 2, 2 can be choosen at most 20 times resulting in a valid combination (2, 2, ..., 2) of length 20.
Thus, M = 20 = (40 / 2)

>> Time Complexity: O(2 ^ (n + M) + KM)

1. Recursive Search
At every state we have up to two choices:
• pick     -> findCombination(ind, k - arr[ind], ...)
• not pick -> findCombination(ind + 1, k, ...)

Because picking can happen repeatedly, the recursion depth is not bounded by n; it can be as large as T / min(candidate).

A useful way to describe the worst-case search complexity is: O(2 ^ (n+M) )
where, M = T / min(candidate)

This captures the fact that along a path we can make up to `M` pick decisions and up to `n` not-pick decisions.
(since picking up an element more than M consecutive times would just make the combination sum exceed k (k becomes negative)).

2. ans.push_back(ds)
There's also the cost of: ans.push_back(ds);
When a valid combination is found, `ans.push_back(ds)` is executed and ds has to be copied into res.
If the combination contains at most M elements, each insertion costs: O(M)
If there are K valid combinations, total output-copying cost is: O(KM)
So, in total this statement takes O(KM) time.

So, total time taken will be O(number of explored states + total size of output)

| Final Time Complexity: O(2 ^ (n + M) + KM)

>> Space Complexity: O(n + M), excluding the output
There are three different things to consider.

1. Recursion stack
The maximum recursion depth is: O(n+M)
because along one path we can:
• make up to M picks of the smallest candidate
• then make up to n not-pick decisions
So: O(n+M) stack space.

2. ds
The current combination can contain at most M elements: O(M)

3. ans
This is the output itself and should generally be counted separately:
O(total number of elements stored in all combinations)
If there are K combinations and each has at most M elements: O(KM)

| Component                        |                                   Complexity |
| -------------------------------- | -------------------------------------------: |
| Time                             | Exponential; roughly `O(2^(n+M))` worst-case |
| Recursion stack                  |                                   `O(n + M)` |
| Current `ds`                     |                                       `O(M)` |
| Output `ans`                     |                                      `O(KM)` |
| Auxiliary space excluding output |                                   `O(n + M)` |

where, M = ⌊ T / min(candidates) ​⌋, K = number of valid combinations produced
*/

// Striver's solution
void findCombination(vector<int>& arr, int ind, int k,  vector<vector<int>>& ans, vector<int>& ds) {
    if (ind == arr.size()) {
        if (k == 0) 
            ans.push_back(ds);

        return;
    }

    // pick current element, only if picking it won't make the combination sum exceed k
    if (arr[ind] <= k) {
        ds.push_back(arr[ind]);
        findCombination(arr, ind, k - arr[ind], ans, ds);
        ds.pop_back();
    }
    
    // not pick current element and move to consider the next element
    findCombination(arr, ind + 1, k, ans, ds);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> ds;

    findCombination(candidates, 0, target, ans, ds);

    return ans;
}

// With early exit conditions : taking advantage of problem constraints
/*
Depending on the value of k, we might have some early exit conditions
• k == 0 → We have formed a valid combination whose sum equals the target. 
  Store it and return because there is no need to add anything further.
• i == arr.size() → We've considered all candidates. If k is still non-zero, 
  no valid combination can be formed from the remaining elements.
• k < 0 → Since all candidates are positive, once the remaining target becomes negative, 
  the current path can never produce a valid combination. So we can immediately stop exploring it.

The important part is that k < 0 is only safe because candidates are positive. 
If negative numbers were allowed, exceeding the target wouldn't necessarily mean the path is impossible.
*/
void findCombination2(vector<int>& arr, int i, int k,  vector<vector<int>>& res, vector<int>& ds) {
    // array don't have negatives & zero, so we can do early return when sum of ds becomes k or exceeds k
    if (k == 0) {
        res.push_back(ds);
        return;
    }

    if (i == arr.size() || k < 0) {
        return;
    }

    // pick current element, even if picking it makes k negative, it would be handled by the early exit condition
    ds.push_back(arr[i]);
    findCombination2(arr, i, k - arr[i], res, ds);
    ds.pop_back();
    
    // not pick current element and move to consider the next element
    findCombination2(arr, i + 1, k, res, ds);
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res = {};
    vector<int> ds = {};

    findCombination2(candidates, 0, target, res, ds);

    return res;
}

// Why the constraints are designed to have '2 <= candidates[i] <= 40' ?
/*
The constraints are designed to ensure that the search space is finite and manageable.

• Why no 0?
If 0 were allowed and even one valid combination existed, we could append 0 indefinitely:
    [7]
    [7,0]
    [7,0,0]
    [7,0,0,0]
    ...
This creates infinitely many valid combinations.

• Why no negative numbers?
Negative numbers can allow us to keep adding elements while keeping the same sum. For example, with 2 and -2:
    [2, -2]              → sum = 0
    [2, -2, 2, -2]       → sum = 0
    [2, -2, 2, -2, ...]  → sum = 0
So we could construct infinitely many combinations with the same target.

• Why not allow 1?
1 doesn't cause an infinite number of combinations, but it can make the search space much larger. 
Since candidates can be reused, reaching target T could require up to T picks:
So the maximum combination length M can become T (M = ⌊ T / min(candidates) ​⌋ = ⌊ T / 1 ⌋ = T).
The T can have value upto 40, and time = 2 ^ (n + M) would give us 2 ^ (n + 40), which is a lot.
Thus, 1 could have increased the search space and recursive depth a lot.

With current constraints, minimum value is 2, so: M <= T / 2. This keeps the recursion depth & search space smaller. 

The lower bound of 2 prevents zero/negative-related issues and also limits how many times the pick branch can repeat. 
This keeps the search space significantly more manageable.
*/

int main() {
    return 0;
}