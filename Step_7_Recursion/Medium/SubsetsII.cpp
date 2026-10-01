/*
Leetcode - 90. Subsets II : Medium

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Examples :-

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Input: nums = [0]
Output: [[],[0]]

Constraints :-
• 1 <= nums.length <= 10
• -10 <= nums[i] <= 10
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Using Set): Time Complexity : O(n logn + 2^n ⋅ L logK + KL) __ Space Complexity : O(n + KL)
/*
We can use the standard pick/not-pick recursive approach to generate the subsets.
But the problem of duplicacy remains due to the presence of duplicates.
For ex: for arr = [1, 2, 2]
all possible subsets of arr are: [], [1], [2], [2], [1, 2], [2, 2], [1, 2], [1, 2, 2]
the generated subsets have two [2] subsets and two [1, 2] subsets.
But we only want to have them once in the output vector (no duplicates).
So, we can simply use a set to store the subsets and remove duplicacy.

But there is still one issue, the array is not always sorted. 
Assume, arr = [2, 1, 2]
Now, all possible subsets of this array are: [], [2], [1], [2], [2, 1], [1, 2], [2, 2], [2, 1, 2]
These are the subsets that will be produced by the recursive implementation for this array.
Now, even if we use a set to store the subsets so to remove duplicacy, the set would remove a duplicate [2],
but the set would still store [1, 2] & [2, 1] both.
This is because it considers [1, 2] & [2, 1] as two different vectors, since [1, 2] != [2, 1]
But, in set terminology, [1, 2] == [2, 1], so the output should have had them once.

This happened because the elements (1 & 2) are in different order in the two vectors ([1, 2] & [2, 1]).
So, if we want to fully remove duplicacy, we want the set to consider the elements and not their order.
Or, we need to firstly order the elements before putting them in the set.
So, we sort the array, annd by doing so, we ensure that all generated subsets are also in sorted order,
and hence set will be able to efficiently skip the duplicate subsets.

>> Complexity Analysis

Let:
• n = number of elements
• K = number of unique subsets
• L = average subset length, so L ≤ n

-> Time Complexity

1. Sorting:- sort(nums.begin(), nums.end()); -> O(n logn)

2. Recursive subset generation
At every element we have two choices: pick & not-pick
Therefore, there are: 2^n possible subsets/leaf paths.
The recursive traversal itself is: O(2^n)
More precisely, the entire binary recursion tree contains O(2^n) nodes.

3. res.insert(subset)
At every leaf, we insert the generated subset into: set<vector<int>> res;
There are 2^n generated subsets, including duplicates.
For each insertion:
    - set lookup/insertion → O(log S), where S is the number of unique subsets currently in the set.
    - Comparing two vector<int> objects can cost up to O(L).
So one insertion can cost: O(L logS)
Since there are 2^n leaf subsets and S ≤ K: O(2^n ⋅ L logK)

Therefore, the total time is: O(n logn + 2^n ⋅ L logK)

4. Converting set → vector
    vector<vector<int>> ans(res.begin(), res.end());
There are K unique subsets, each of average length L: O(K L)
This is dominated by the set insertion cost in the usual worst case.

Final Time Complexity
| A precise output-aware expression is: O(n logn + 2^n ⋅ L logK + KL)

-> Space Complexity
1. Recursion stack:- The recursion goes one level deeper for every element: O(n)
2. Current subset:- At most n elements: O(n)
3. set<vector<int>> res:- The set stores K unique subsets, each of maximum length L: O(KL)
4. Final ans:- Another copy of the K unique subsets: O(KL)

Therefore, including the output: O(n + KL)

The auxiliary space excluding the returned output is still O(n + KL) 
because the intermediate set itself stores all unique subsets.
*/
void findSubsets(vector<int>& arr, int ind, vector<int>& subset, set<vector<int>>& res) {
    if (ind == arr.size()) {
        res.insert(subset);
        return;
    }

    // pick the current element
    subset.push_back(arr[ind]);
    findSubsets(arr, ind + 1, subset, res);
    subset.pop_back();

    // not-pick the current element
    findSubsets(arr, ind + 1, subset, res);
}

vector<vector<int>> subsetsWithDupNaive(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    vector<int> subset;
    set<vector<int>> res;
    
    findSubsets(nums, 0, subset, res);
    vector<vector<int>> ans(res.begin(), res.end());

    return ans;
}

// Optimal Approach

// Approach-1 : Time Complexity : O(n logn + 2^n + K L) or O(n . 2^n) in the worst case __ Space Complexity : O(n + KL)
/*
>> Intuition
The key idea is to use the usual pick / not-pick recursion, but avoid generating duplicate subsets in the first place.
First, we sort the array, so equal elements are placed next to each other.
At every index ind, we have two choices:
• Pick arr[ind] → include it in the current subset and move to ind + 1.
• Not pick arr[ind] → skip all consecutive duplicates of this value and move to the next distinct value.

>> The important question is: why do we skip duplicates only in the not-pick branch?
Consider:
arr = [1, 1, 2]
       ↑
      ind
Suppose we are deciding what to do with the first 1.

— Pick branch
If we pick the first 1: subset = [1]
we move to the next index:
[1, 1, 2]
    ↑
Now we are allowed to pick the second 1, giving: [1, 1]
This is important because these are two different occurrences of 1, and [1,1] is a valid and distinct subset.
So we must not skip the second 1 after picking the first one.

— Not-pick branch
Now suppose we don't pick the first 1.
If we simply moved to the second 1, we'd create another branch where we choose the second 1 as the first element:
not pick first 1
      ↓
choose second 1
      ↓
     [1]

But if we consider the branches when we picked the first 1,
it would have 
            Pick first 1
                ↓
        -----------------
        ↓               ↓
    Pick next 1       Skip next 1
        ↓               ↓
      [1, 1]           [1]

So, the Not pick first 1 -> Pick second 1 branch would produce exactly the same subsets as the 
branch where we had chosen the first 1 (or more precisely the branch Choose first 1 -> Not Choose Second 1).
In other words, these two branches:
pick first 1
and
skip first 1 → pick second 1
are equivalent from the perspective of the resulting subsets.

So, we we consider the picking case branch of a first occurrence of any number, 
then we are in a way also considering the skip current element, pick later dupliactes branch also.

Therefore, when we decide not to pick a value, we skip all its duplicates:
| int j = ind + 1;
| while (j < arr.size() && arr[j] == arr[ind])
|     j++;
and jump directly to the next distinct value.

>> Why this works
The two branches can therefore be thought of as:
                     1
                  /     \
               PICK    NOT PICK
                /          \
          use this 1    skip ALL 1s
              |             |
          next index    next distinct value

The pick branch preserves duplicates because we may want to use multiple occurrences of the same value.
The not-pick branch skips duplicates because starting a new branch with another identical value would generate the 
same subsets that the pick branch already covers (more precisely, the pick branch's next element not pick sub-branches).

>> So the core idea is:
Duplicates are skipped only when deciding not to take the current value, 
because taking multiple occurrences of the same value can produce genuinely different subsets such as [1,1]. 
But using a different identical occurrence as the starting point of a new branch would only 
reproduce subsets we've already generated.
This allows us to generate every unique subset exactly once, without needing a set.

>> Complexity Analysis

Let:
• n = number of elements
• K = number of unique subsets in the result
• L = maximum subset length, where L ≤ n

-> Time Complexity

1. Sorting:- sort(nums.begin(), nums.end()); -> O(n logn)

2. Recursive generation
Unlike the naive solution, we don't generate all 2^n subsets when duplicates exist.
The exact number of recursive states depends on the distribution of duplicates.
In the worst case, when all elements are distinct, the while loop always executes only once for each not-pick decision:
[1,2,3,4,...]
and the algorithm generates all possible subsets.
Therefore, worst-case: O(2^n)

The while loop does not add an extra O(n) factor in the overall worst-case analysis; when it scans duplicates, 
it is simultaneously skipping the recursive branches that those duplicates would have created.

3. Copying valid subsets
At the base case: res.push_back(subset); -> the current subset is copied.
If there are K unique subsets and each has at most L elements: O(K L)

Final Time Complexity
Therefore: O(n logn + 2^n + K L)
and in the worst case, where all elements are distinct: K = 2^n, L ≤ n
so the output itself can require: O(n.2^n) space/time to materialize.

Thus, if we want a worst-case bound that accounts for copying every generated subset, we can state: O(n.2^n)
because the output-generation cost dominates the O(2^n) traversal.

-> Space Complexity

1. Recursion stack:- The recursion can go at most n levels deep: O(n)
2. Current subset:- At most n elements: O(n)
3. Result:- There are K unique subsets, each of maximum length L: O(KL)
Therefore, auxiliary space including the output: O(n+KL)
*/
void findSubsets1(vector<int>& arr, int ind, vector<int>& subset, vector<vector<int>>& res) {
    if (ind == arr.size()) {
        res.push_back(subset);
        return;
    }

    // pick the current element
    subset.push_back(arr[ind]);
    findSubsets1(arr, ind + 1, subset, res);
    subset.pop_back();

    // not-pick the current element
    // skip duplicates
    int j = ind+1;
    while (j < arr.size() && arr[j] == arr[ind]) j++;

    findSubsets1(arr, j, subset, res);
}

vector<vector<int>> subsetsWithDup1(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    vector<int> subset;
    vector<vector<int>> res;
    
    findSubsets1(nums, 0, subset, res);

    return res;
}

// Approach-2 (Striver's Solution) : O(n logn + 2^n + K L) or O(n . 2^n) in the worst case __ Space Complexity : O(n + KL)
/*
>> Intuition

This approach uses the same fundamental idea as the previous solution—sort the array and 
avoid generating duplicate subsets—but expresses the recursion differently.

Instead of explicitly making a pick / not-pick decision, we use a for loop to decide which element should be picked next.

First, we sort the array so that duplicate values are adjacent: [1, 1, 2, 2, 3]

At every recursive call, ind represents the first index from which we are allowed to choose the next element.

Add the current subset first
| res.push_back(subset);
Every subset we currently have is already a valid answer.

For example: subset = [] is a valid subset, and from it we can choose:
    [1]
    [2]
    [3]
    ...
When we recursively choose 1, [1] is immediately added to the result, and from there we can construct:
    [1,1]
    [1,2]
    [1,3]
    ...
So every recursive call represents one unique subset, and we add that subset before deciding what element to append next.

The for loop chooses the next element
| for (int i = ind; i < arr.size(); i++)
At the current recursion level, the loop asks:
| Which element should I choose as the next element of my subset?

For example:
[1, 1, 2]
 ^
 ind
From this level, we can choose:
1 → recursively build subsets starting with [1]
1 → duplicate choice, skip
2 → recursively build subsets starting with [2]

After choosing arr[i], we recurse with:
| findSubsets(arr, i+1, subset, res);
so that we can only choose elements after i. This ensures that each array element is used at most once.

>> Why do we skip duplicates only at the same level?
This is the most important part:
| if (i != ind && arr[i] == arr[i-1])
|     continue;
Consider:
[1, 1, 2]
 ^
 ind
At this recursion level, choosing the first 1 and choosing the second 1 as the next element would create identical branches.
For example:
choose first 1 → [1]
choose second 1 → [1]
Both would subsequently generate exactly the same subsets, so we skip the second 1.

That's what: i != ind, ensures — we skip a duplicate only when it is a duplicate choice at the same recursion level.
However, after choosing the first 1, we recursively move to i + 1:
[1, 1, 2]
    ^
   next level
At this new recursion level, the second 1 is allowed to be chosen.
That's how we can still generate: [1,1], while avoiding duplicate branches.

>> Think of the recursion tree like this
For: [1, 1, 2]
we conceptually have:

                         []
                    /     |     \
                   1      1      2
                  /       X       \
                [1]     skipped   [2]
              /    \
             1      2
            /        \
         [1,1]      [1,2]

Notice one more thing, at each recursion level `i`, we are getting subsets of length `i-1` and 
are making recursive calls to find the later subsets.
Like in the above recursion tree, the root recursion level has the empty subset (length 0),
the 2nd recursion level has the 1-length subsets
the 3rd recursion level has the 2-length subsets and so on..

>> Complexity Analysis
Let:
• n = number of elements
• K = number of unique subsets
• L = maximum subset length, where L ≤ n

-> Time Complexity 

1. Sorting:- sort(nums.begin(), nums.end()); -> O(n logn)

2. Recursive generation
In the worst case, when all elements are distinct, there are exactly: 2^n unique subsets.
The recursion therefore generates O(2^n) subsets/calls.
However, there's an important detail: each recursive call does a for loop. 
We shouldn't simply multiply O(2^n) by O(n), because the loop iterations are distributed across the recursion tree.
The total loop work across the recursion tree is bounded by the number of subset-generation states, giving the usual:
O(2^n) for the traversal itself.

3. Storing the subsets
This line: `res.push_back(subset);` copies the current subset.
If a subset has length L, copying it costs: O(L)
Since there are K unique subsets: O(K L)

Therefore: O(n logn + 2^n + KL)
For the worst case where all elements are distinct: K = 2^n, L ≤ n
so simply materializing the output itself can cost:
O(n.2^n)
Thus, an output-aware worst-case bound is: O(n logn+ n.2^n)
and since n2^n dominates n log n: O(n.2^n)

-> Space Complexity
1. Recursion stack
Every recursive call moves to a larger index:
| findSubsets(arr, i + 1, ...)
Maximum depth: O(n)

2. Current subset:- At most n elements: O(n)
Therefore auxiliary space: O(n)

3. Output
The result contains K unique subsets, each up to length L: O(KL)
So space complexity including the output: O(n + KL)
*/
void findSubsets(vector<int>& arr, int ind, vector<int>& subset, vector<vector<int>>& res) {
    // Add the current subset to result
    res.push_back(subset);

    for (int i = ind; i < arr.size(); i++) {
        // skip duplicates
        if (i != ind && arr[i] == arr[i-1]) continue;

        subset.push_back(arr[i]);
        findSubsets(arr, i+1, subset, res);
        subset.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    vector<int> subset;
    vector<vector<int>> res;
    
    findSubsets(nums, 0, subset, res);
    return res;
}

int main() {
    return 0;
}