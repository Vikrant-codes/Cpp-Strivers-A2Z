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
And in both pick/not-pick decision, we move to the next index, since an index can only be chosen once.

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
    ds.pop_back();

    // not pick the current element
    findCombinations(arr, ind + 1, k, ans, ds);
}
vector<vector<int>> combinationSum2Naive(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    set<vector<int>> ans;
    vector<int> ds;

    findCombinations(candidates, 0, target, ans, ds);

    // insert the valid combinations from the set into a result vector
    vector<vector<int>> res(ans.begin(), ans.end());
    return res;
}

// Optimal Approach
// To avoid duplicate combinations, we try to avoid exploring equivalent duplicate branches.

// Optimal Approach (Striver's Solution): Time Complexity: O(n logn + 2^n + KL) __ Space Complexity: O(n + KL)
/*
>> Intuition

The main difference compared to Combination Sum I (LeetCode 39) is that:
- Each element can be used at most once, so after choosing an element we must move to the next index.
- The input may contain duplicate values, but the result must contain only unique combinations.

A straightforward solution would be to generate all subsets and use a set to remove duplicates. 
However, this generates many duplicate combinations that are eventually discarded. 
Instead, we would like to avoid generating duplicates in the first place.

To achieve this, we first sort the array. 
Sorting brings equal values together, which makes it easy to detect and skip duplicates during recursion.

Suppose: candidates = [1, 1, 2, 5, 6], target = 8
Think:
We are going to generate subsequences using the for → choose → recurse → backtrack pattern, 
but only keep the subsequences whose sum equals the target.

For every index i starting from ind, we can choose arr[i] as the next element, add it to the current combination, 
and recursively search for the remaining target using only the elements that come after it.
| getCombinations(arr, i + 1, target - arr[i], ans, ds);
Notice that we recurse with i + 1, not i. This ensures that each element is used at most once.

At every recursive state, we have:
• ds = current combination
• target = remaining sum
• ind = where we are allowed to choose from

The for loop asks: Which element can I choose as the next element?
Once I choose arr[i], recursion starts from i + 1 because the same element cannot be reused.

For example:
        []
      /  |  \
     1   2   5
    / \
  1   2

If we choose: [1, 2, 5]
we've used those particular elements, so we can only continue with elements after 5.

-> When do we have an answer?
Unlike the ordinary subsequence problem, not every recursive state is an answer.
We only have an answer when: remaining target == 0

For example: target = 8
[1, 1, 6] → 1 + 1 + 6 = 8 → valid combination

>> How to deal with duplicates?
Because the array can contain duplicates: [1, 1, 2, 3]
we might otherwise generate:
[1(first), 2]
[1(second), 2]
which are the same combination [1,2].

The loop can choose either the first 1 or the second 1.
If we start a branch with the first 1 and another branch with the second 1, 
both branches will explore exactly the same possibilities and eventually generate the same combinations. 
(First 1 picked -> this then explores, second 1 picked & not-picked)
(Second 1 picked -> this will explore and generate the same combinations as the First 1 picked second 1 not-picked)
Therefore, exploring both is redundant.

To avoid this, whenever we encounter a value that is the same as the previous value at the same recursion level, we skip it:
| if (i > ind && arr[i] == arr[i - 1]) continue;
The condition i > ind is important because we only want to skip duplicates at the current level.

For example: [1, 1, 2]
The combination [1,1,2] is valid and should still be generated. 
After choosing the first 1, the recursive call moves to the next level, 
where choosing the second 1 is perfectly allowed. 
We only skip the second 1 when it would start a new branch at the same level as the first 1.

So, to handle the duplicates, we sort the array and apply: 
| At the same recursion level, if we've already tried a particular value, don't try the same value again.
But duplicates at different levels are allowed.

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

// Recursive helper function
void getCombinations(vector<int>& arr, int ind, int target, vector<vector<int>>& ans, vector<int>& ds) {
    // Base case: If the target becomes 0, we found a valid combination
    if (target == 0) {
        ans.push_back(ds);      // Add the current combination to the result
        return;
    }

    // if (ind == arr.size()) return;
    // this return check is not needed as when ind == arr.size(), 
    // the for loop won't run and the recursive function will automatically return, after ending

    // Loop from index 'ind' to end, considering each element as the next element of combination, and exploring its branch
    for (int i = ind; i < arr.size(); i++) {
        // Skip duplicates at the same level, to avoid repeating combinations 
        if (i > ind && arr[i] == arr[i-1]) continue;
    
        // If the current element > remaining_target, break out of the loop (we can also return directly)
        if (arr[i] > target) return;
    
        ds.push_back(arr[i]);       // choose
        getCombinations(arr, i+1, target - arr[i], ans, ds);  // recursively explore the branches for current choice
        ds.pop_back();              // undo choice & backtrack
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());         // Sort the candidates to handle duplicates
    vector<int> ds;                                     // Stores current combination 
    vector<vector<int>> ans;                            // Stores all valid combinations 
    getCombinations(candidates, 0, target, ans, ds);   
    return ans;                                         // return all the valid combinations
}

// Implementation using Pick/Not-pick Pattern: Time Complexity : O(n logn + 2^n + KL) __ Space Complexity : O(n + KL)
/*
>> Intuition
From the for → choose → recurse → backtrack solution, 
we learned that the main problem with duplicates is at the same decision level.

For example, after sorting: [1a, 1b, 1c, 2, 3]
Suppose we're at 1a.
• If we pick 1a, we recurse forward and can still pick 1b/1c later. 
    This is necessary because [1,1] is a valid combination.
• But if we don't pick 1a, then moving to 1b and considering it as a fresh choice 
    would generate the same combinations that we could already generate by picking 1a.

So the important deduction is:
| We only need to skip duplicates when making the NOT-PICK decision.

That is exactly what the for-loop solution was doing with:
| if (i > ind && arr[i] == arr[i - 1])
|     continue;

The for loop was implicitly handling the not-pick decisions for us. 
Now we can make those decisions explicitly using the standard pick/not-pick recursion.

So, if we use the pick/not-pick recursion, we need to handle the duplicates during the not-pick decision.
i.e., if we decide to not-pick an element, then we must move to the next distinct element for the pick/not-pick choice.
So, at index `ind`, when making the not-pick choice, we don't recursively call the function for `ind+1`, 
instead we find the next distinct element's and then make the recursive call using this index.

We can use a simple while loop to find the index of the next distinct element (which is not equal to arr[ind])
|   int j = ind + 1;
|   while (j < arr.size() && arr[j] == arr[ind]) j++;

and directly recurse from j:
|   findCombinations(arr, j, target, ans, ds);

Suppose: 1a  1b  1c  2
         ↑
        ind
If we decide not to pick 1a, we don't move just to 1b, because 1b has the same value.
Instead, the while loop skips:  1a → 1b → 1c → 2
                                               ↑
                                               j
and we recurse from 2.

So we're saying:
"I've decided not to use this value 1 at this decision level, 
so skip all its duplicate occurrences and move to the next distinct value."
Meanwhile, the pick branch only moves by ind + 1, so duplicates can still be picked at deeper levels:
pick 1a
   ↓
pick 1b
   ↓
[1,1]

That's why this approach correctly allows repeated values when they come from different occurrences, 
while preventing duplicate combinations from being generated.

>> Early returns 
Because the array is sorted and all candidates are positive, so if arr[ind] > target, 
we can't pick any further elements, so simply return
| if (ind == arr.size() || arr[ind] > target)
|     return;

Similarly, when we try to find the next distinct element, j might go out of bounds of array size, 
or maybe j might point to some element which is greater than target itself.
In these conditions, we can also return instead of making the recursive call,
although, even if we made the recursive call, the call would have returned, so this return is not that meaningful.
| if (j == arr.size() || arr[j] > target)
|     return;

>> Overall Idea
Use pick/not-pick recursion, but when not-picking an element, 
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
The recursion is still based on pick / not-pick, so in the worst case it can explore exponentially many states: O(2^n)
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
    // if target == 0, we have got a valid combination
    if (target == 0) {
        ans.push_back(ds);
        return;
    }

    // If array has been fully traversed or current element > target, return
    if (ind == arr.size() || arr[ind] > target) return;

    // pick current element
    ds.push_back(arr[ind]);
    findCombs(arr, ind + 1, target - arr[ind], ans, ds);
    ds.pop_back();
    
    // not-pick current element
    
    // skip all duplicates and move to the next distinct element, make the recursive call for this next distinct element index
    int j = ind+1;
    while (j < arr.size() && arr[j] == arr[ind]) j++;
    // j now points at the next distinct element
    
    // if j == array size, or, the jth element > target, no need for further recursive calls, return
    if (j == arr.size() || arr[j] > target) return;
    // although, this return is not that meaningful, since even if avoided, the recursive call would itself return

    findCombs(arr, j, target, ans, ds);     // recursive call for the next distinct element
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