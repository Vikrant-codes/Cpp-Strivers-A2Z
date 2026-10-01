/*
Leetcode - 216. Combination Sum III : Medium

Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
• Only numbers 1 through 9 are used.
• Each number is used at most once.

Return a list of all possible valid combinations. 
The list must not contain the same combination twice, and the combinations may be returned in any order.

Examples :-

Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, 
there are no valid combination.

Constraints :-
• 2 <= k <= 9
• 1 <= n <= 60
*/

#include <bits/stdc++.h>
using namespace std;

// My solution : Time Complexity : O(2^9 ∙ k) __ Space Complexity : O(R ∙ k)
/*
>> Intuition

We need to find all combinations of exactly k distinct numbers from 1 to 9 whose sum is exactly n.
Since every number can either be selected or skipped, we can model the problem as a binary decision at every index.
We can create an array of digits 1-9 and apply the pick / not-pick standard recursive approach on [1,2,3,4,5,6,7,8,9]
For each number arr[ind], we have two choices: either pick it or not-pick it.

Instead of maintaining separate variable to represent the current picked numbers count and their sum, 
we can use the variable `k` and `n` themselves, and decrement them, so we don't need any other extra variables.

states of the recursive function 
`findCombinations(vector<int>& arr, int ind, int k, int n, vector<vector<int>>& ans, vector<int>& ds)`:
    arr → array of 1-9 digits [1, 2, 3, 4, 5, 6, 7, 8, 9]
    ind → which number we're currently considering
    k   → how many more numbers we need
    n   → how much sum is still required
    ds  → numbers chosen so far

-> Pick arr[ind]
• Add it to the current combination.
• Decrease k because we need one fewer number.
• Decrease n by arr[ind] because we need a smaller remaining sum.
• Move to ind + 1 because each number can be used at most once.

-> Don't pick arr[ind]
• Leave the current combination unchanged.
• Keep k and n unchanged since no number was picked.
• Move to ind + 1.

Thus, the recursion explores all possible subsets of {1,2,...,9}, 
while keeping track of how many numbers and how much sum are still required.

>> Base case
When k == 0, we have selected exactly the required number of elements.
At this point, the combination is valid only if n == 0.
|    if (k == 0) {
|        if (n == 0)
|            ans.push_back(ds);
|        return;
|    }

>> Pruning
We can stop exploring a branch early when it can no longer produce a valid combination:
|    if (ind == arr.size() || n < 0 || k > (arr.size() - ind))
|        return;

ind == arr.size() → no numbers remain, array has been fully traversed.
n < 0 → the current sum has already exceeded the target. Since all numbers are positive, we cannot recover.
k > (arr.size() - ind) → there aren't enough remaining numbers to select k elements.

Since the numbers are considered in increasing order and we always move to ind + 1, 
every number is used at most once and every combination is generated only once.

>> Summary
We use backtracking to enumerate all subsets of the numbers 1 through 9. 
At each index, we either pick the current number or skip it. 
When a number is picked, we decrease both the remaining count k and remaining sum n.
Because we always move to the next index, each number is used at most once. 
We prune branches when the remaining sum becomes negative, when there are not enough numbers left to satisfy k, 
or when all numbers have been processed. 
A combination is added to the result only when exactly k numbers have been selected and the remaining sum is zero.

>> Complexity Analysis

There are only 9 numbers, and for each number we have two choices: pick or not pick.
Therefore, without pruning, the recursion explores at most: 2^9 subsets.
So the time complexity for exploring the search space is: O(2^9)
Since 9 is a constant, this is effectively O(1) for this particular problem.

However, when we find a valid combination, we copy k elements into ans, 
so more precisely we can write: O(2^9 ∙ k) in the worst case.
Since k ≤ 9, this is still effectively constant for LeetCode 216.

-> Space Complexity
The recursion depth can be at most 9.
The temporary vector ds can contain at most k ≤ 9 elements.
Therefore, auxiliary space is: O(9) = O(1), excluding the output.
If we include the space required to store the returned combinations, then the output space is:
O(R ∙ k)
where R is the number of valid combinations.
*/
void findCombinations(vector<int>& arr, int ind, int k, int n, vector<vector<int>>& ans, vector<int>& ds) {
    if (k == 0) {
        if (n == 0) {
            ans.push_back(ds);
        }
        return;
    }

    // if ind has reached array end / n has become negative / not enough characters to pick anymore 
    if (ind == arr.size() || n < 0 || k > (arr.size() - ind)) 
        return;
    
    // pick the current element
    ds.push_back(arr[ind]);
    findCombinations(arr, ind + 1, k - 1, n - arr[ind], ans, ds);

    ds.pop_back();
    
    // not-pick the current element
    findCombinations(arr, ind + 1, k, n, ans, ds);
}

vector<vector<int>> combinationSum3(int k, int n) {
    if (n > 45) return {};  // sum of all 1-9 digits is 45, so if n > 45, no valid combination exists

    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<vector<int>> ans;
    vector<int> ds;

    findCombinations(arr, 0, k, n, ans, ds);

    return ans;
}

// Other Solution (Striver's sheet & ChatGPT): Time Complexity : O(2^9 ∙ k) __ Space Complexity : O(R ∙ k)
/*
>> Intuition
We need to find all combinations of exactly k distinct numbers from 1 to 9 whose sum is equal to n.
We can build each combination incrementally using backtracking.
At any point, suppose we have already selected some numbers. We need to decide which number should be selected next.
To ensure that:
• numbers are selected only once, and
• the same combination isn't generated in different orders,
we maintain a start value.

For every recursive call, we try every number from start through 9:
|   for (int i = start; i <= 9; i++)

If we choose i, we:
• add i to the current combination,
• decrease k by 1,
• decrease the remaining sum n by i,
• and recursively search starting from i + 1.

|   curr.push_back(i);
|   solve(i + 1, k - 1, n - i);
|   curr.pop_back();

Starting the next search from i + 1 ensures that we never reuse i and that numbers always appear in increasing order.
For example, if we choose 2, the next number can only be: 3, 4, 5, ..., 9 and never 1 or 2.
This means combinations such as: [2, 5, 7]
are generated only once, rather than also generating: [5, 2, 7], [7, 5, 2] ...

>> Base Case
When k == 0, we have selected exactly the required number of elements.
The combination is valid only when the remaining sum is also zero:
|   if (k == 0) {
|       if (n == 0)
|           ans.push_back(curr);
|       return;
|   }

>> Pruning
Because all numbers are positive, if the current number is greater than the remaining sum:
|   if (i > n)
|       break;
then all subsequent numbers will also be greater than n, so none of them can produce a valid combination.
We can therefore stop the loop immediately.

We also stop when:
|   if (start > 9)
|       return;
because there are no numbers left to consider.

>> Complexity Analysis
There are only 9 possible numbers.
The backtracking algorithm explores combinations of these numbers. 
In the worst case, the search space is bounded by the number of subsets of 9 elements: O(2^9)

For every valid combination, we copy k elements into the result, so including the cost of producing the output: O(2^9 ∙ k)
Since k ≤ 9, this is effectively O(1) for this specific problem.

-> Space Complexity
The recursion depth can be at most 9, and curr can contain at most k ≤ 9 elements.
Therefore, the auxiliary space is: O(9) = O(1), excluding the output.
If we include the output, the space complexity is: O(R ∙ k), where R is the number of valid combinations.
*/
void fun(int start, int k, int n, vector<int>& curr, vector<vector<int>>& ans) {
    // Valid combination found (length `k` and sum `n`)
    if (k == 0) {
        if (n == 0)
            ans.push_back(curr);
        return;
    }

    // No numbers left to pick
    if (start > 9) return;

    for (int dig = start; dig <= 9; dig++) {
        // if current digit `dig` exceeds `n`, we can't pick it or any further digits
        // as adding them to combination would only make the sum exceed n (n becomes -ve), so break/return
        if (dig > n) 
            break;
        
        curr.push_back(dig);
    
        fun(dig + 1, k - 1, n - dig, curr, ans);
    
        curr.pop_back();     
    }
}

vector<vector<int>> combinationSum3X(int k, int n) {
    vector<int> curr;
    vector<vector<int>> ans;
    
    fun(1, k, n, curr, ans);
    
    return ans;
}

int main() {
    return 0;
}