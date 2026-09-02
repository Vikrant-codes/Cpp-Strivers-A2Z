/*
>> Power Set — general Set Theory

A power set is a new set that contains every possible subset of a given set, 
including the empty set and the original set itself.

For a set `S`, its power set, denoted by `P(S)` or `2^S`, is the set containing every subset of `S`, including:
- the empty set ∅
- `S` itself
- every possible combination of its elements

For example: S = {a,b,c}
Then:
P(S) = { ∅ , {a} , {b} , {c} , {a,b} , {a,c} , {b,c} , {a,b,c} }

If S has n elements, its power set has: 2^n elements.
Why? Each element has exactly 2 choices: include it OR don't include it.
So with n elements: 2 × 2 × ⋯ × 2 = 2^n

>> Power Set of an Array / String

In programming / DSA, when people say "generate the power set of an array", they usually mean:
| Generate all possible subsets/subsequences of the elements.

For example: arr = [1, 2, 3]
Its power set is: [ [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3] ]

For a string: s = "abc"
the subsequences/power set are: [ "", "a", "b", "c", "ab", "ac", "bc", "abc" ]

-> Important distinction: subset vs subsequence
For an array/set, we generally talk about subsets.
For a string/array where order matters, DSA problems often call them subsequences.

For "abc":
"ac" is a subsequence because we select a and c while maintaining their original order.
But: "ca" is not a subsequence because it changes the order.

So when generating subsequences, each element again has two choices:
         element
         /     \
    include    exclude

For "abc":

                ""
            /          \
          a              ""
       /    \          /    \
     ab      a        b      ""
    / \     / \      / \     / \ 
  abc ab   ac  a    bc  b   c   ""

Conceptually, this is why subsequence generation is a binary recursion tree and produces 2^n possibilities.
*/

#include <bits/stdc++.h>
using namespace std;

// The power set have two implementations -- using Recursion & Bit Manipulation

// Leetcode - 78. Subsets
/*
Leetcode - 78. Subsets : Medium

Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Examples :-

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Input: nums = [0]
Output: [[],[0]]

Constraints :-
• 1 <= nums.length <= 10
• -10 <= nums[i] <= 10
• All the numbers of nums are unique.
*/

// Recursive Implementation : Time Complexity : O(2^n . L) __ Space Complexity : O(2^n . L)
/*
We can use the standard pick/not-pick recursion for each element to generate all possible subsets.

>> Complexity Analysis
Let,
• n = no. of elements
• L = average length of subsets

-> Time Complexity
The whole recursive subset generation takes O(2^n) time, or we can say that there are 2^n recursive leaf nodes.
These 2^n recursive leaf nodes generates all the possible subsets (2^n subsets).
And each of this subset are added to the result.
Assuming the average length of subset is L, this subset insertion to result vector takes O(L) for each insertion.
Thus, for 2^n subsets, the insertion would take O(2^n . L)
and hence, total time = O(2^n . L)

-> Space Complexity 
The recursion depth is `n`, so the recursive stack space is O(n)
But we are storing the subsets into an output vector.
This vector stores 2^n subsets.
Considering average subset length is `L`, the space required for output vector is O(2^n . L)

Thus, auxiliary space considering the output vector is : O(2^n . L)
without considering the output vector, O(n)
*/
void recurseSubsets(vector<int>& nums, int ind, vector<int>& ds, vector<vector<int>>& powerSet) {
    if (ind == nums.size()) {
        powerSet.push_back(ds);
        return;
    }

    ds.push_back(nums[ind]);
    recurseSubsets(nums, ind + 1, ds, powerSet);

    ds.pop_back();
    recurseSubsets(nums, ind + 1, ds, powerSet);
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> powerSet;
    vector<int> ds = {};

    recurseSubsets(nums, 0, ds, powerSet);
    
    return powerSet;
}

// GFG - All Subsequences of a String
/*
GFG - All Subsequences of a String : Medium

Given a string s, generate all possible subsequences of the string (including the empty subsequence) 
and return them in lexicographical order.

A subsequence is obtained by deleting zero or more characters from the string 
without changing the relative order of the remaining characters.

Examples :-

Input : s = "abc"
Output: ["","a", "ab", "abc", "ac", "b", "bc", "c"]
Explanation: There are a total of 8 non-empty subsequences for the given string. 
These subsequences are listed above in lexicographical order.

Input: s = "aa"
Output: ["", "a", "a", "aa"]

Constraints :-
• 1 ≤ n ≤ 16
• s consists of lowercase English letters.
*/

// Time Complexity : O(n ∙ 2ⁿ) + O(n² ∙ 2ⁿ) __ Space Complexity : O(n ∙ 2ⁿ)
/*
>> Complexity Analysis
Let n = s.size().

1. Recursion / generating subsequences
At every character, we have 2 choices:
- exclude it
- include it

So the recursion tree has: 2ⁿ leaf nodes, i.e. 2ⁿ subsequences.
But at each leaf, we do:
| ans.push_back(subSeq);

Copying subSeq takes up to O(n) time.
Therefore, generating + storing all subsequences takes: O(n ∙ 2ⁿ)

2. Sorting

We have:
| sort(ans.begin(), ans.end());

There are 2ⁿ strings being sorted.
A comparison between two strings can take O(n) in the worst case.
Therefore: O(2ⁿ log(2ⁿ) ∙ n)
Since: log(2ⁿ)=n
we get: O(2ⁿ n ∙ n) = O(n² ∙ 2ⁿ)

3. Total time complexity
Combining both: O(n ∙ 2ⁿ) + O(n² ∙ 2ⁿ)
The sorting dominates:  O(n² ∙ 2ⁿ)

-> Space complexity
There are 2ⁿ subsequences, each potentially of length n.
So storing ans requires: O(n ∙ 2ⁿ)
Additionally, recursion depth is only n: O(n)
and subSeq uses at most O(n) space.
Thus, including the output: O(n ∙ 2ⁿ)
Auxiliary space excluding ans: O(n)
*/
void fun(string& s, int ind, string& subSeq, vector<string>& ans) {
    if (ind == s.size()) {
        ans.push_back(subSeq);
        return;
    }
    
    // Exclude the current character
    fun(s, ind + 1, subSeq, ans);
    
    // Include the current character
    subSeq.push_back(s[ind]);
    fun(s, ind + 1, subSeq, ans);
    
    subSeq.pop_back();
}

vector<string> powerSet(string &s) {
    vector<string> ans;
    string subSeq = "";
    
    fun(s, 0, subSeq, ans);
    
    sort(ans.begin(), ans.end());
    
    return ans;
}

int main() {
    return 0;
}