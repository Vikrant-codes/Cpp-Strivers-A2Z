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

// The power set problem have two solutions -- using Recursion (Backtracking) & Bit Manipulation

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

// Pick/Not-pick subsequence generation
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

    ds.push_back(nums[ind]);                       // pick current element
    recurseSubsets(nums, ind + 1, ds, powerSet);   // explore pick branch
    ds.pop_back();                                 // undo choice

    recurseSubsets(nums, ind + 1, ds, powerSet);   // explore not-pick branch 
}

// For-loop based subsequence generation 
/*
>> Intuition — For-loop based subsequence generation 

Suppose: nums = [1, 2, 3]
Instead of thinking:
| "For every element, should I pick it or not?"
we think:
| "I have built a subsequence so far. What element can I choose as the NEXT element?"

Initially: ds = []
From here, any element can be the first element: 1 2 3
So we get:
        []
     /  |  \
    1   2   3

Now suppose we chose 1.
We've built: [1]
The next element can only come after 1, so we try: 2 3
giving:
            []
         /  |  \
        1   2   3
       / \
     1,2 1,3

Similarly, from [2], we can choose 3:
            []
         /  |  \
        1   2   3
       / \   \
    1,2  1,3  2,3

And from [1,2], we can choose 3:

                 []
           /     |     \
         [1]     [2]    [3]
        /   \      \
     [1,2] [1,3]  [2,3]
       |
    [1,2,3]

These are exactly all 8 subsequences.

-> So what is the for loop doing?
At every recursive call:
The for loop tries every possible choice for the next position in the subsequence.
And recursion says:
"Okay, I chose this element. Now find what can come after it."

That's why the pattern is:
| for each possible next element
|         ↓
|       choose
|         ↓
|       recurse
|         ↓
|       undo

*>> Why is every recursive state itself a subsequence?
The important thing to understand is that we are not making an explicit not-pick recursive call.
In the standard pick/not-pick approach, for every element we explicitly decide: pick OR not-pick
But in the for-loop approach, the loop traversal implicitly handles those not-pick decisions.

Suppose: nums = [1, 2, 3]
At the root: ind = 0
The loop considers:
    i = 0 → pick 1
    i = 1 → pick 2
    i = 2 → pick 3

Now look at what happens when we choose 3.
    [1, 2, 3]
     ↑  ↑  ↑
    not not pick

By reaching i = 2 and choosing 3, we have implicitly decided:
| Don't pick 1 and don't pick 2 as elements of this subsequence. Pick 3.
We didn't make explicit recursive calls saying: don't pick 1 & don't pick 2

The for loop's movement from `ind` toward `i` effectively represents those decisions.
So:
    [] 
     |
    choose 3
     |
    [3]
[3] is already a complete, valid subsequence.

-> Now suppose we first choose 1
We get: [1]
Then recursion starts from the next index:
[1, 2, 3]
    ↑
   ind
The loop can choose: 2 3

If it chooses 3, we get: [1, 3]
Here, choosing 3 means: 2 was considered not-picked, and 3 was picked.
Again, there was no explicit "not-pick 2" recursive call. The loop simply moved past 2 and chose 3.

So the recursion tree becomes
                 []
           /      |      \
          1       2       3
        /   \      \
      1,2  1,3     2,3
       |
     1,2,3

Look at each node:
    []
    [1] [2] [3]
    [1,2] [1,3] [2,3]
    [1,2,3]

Every node is already a valid subsequence.

Why?
Because whenever we arrive at a node, all the elements before the chosen element 
that weren't selected have already been implicitly not-picked by the loop traversal.
Therefore, unlike pick/not-pick where we usually care about the leaf nodes, here:
Every recursive state represents one complete subsequence.
That's why we do: `powerSet.push_back(ds);` at the beginning of every recursive call.

>> How is this different from pick/not-pick?

-> Pick / Not-Pick: The question at every element is:
              element
             /     \
          PICK    DON'T PICK

For [1,2,3]:
-------------------------------------------------
                         []
                    /          \
                [1]                 []
              /    \             /      \
         [1,2]        [1]       [2]      []
        /    \       /   \      /  \    /   \
 [1,2,3]   [1,2]  [1,3]  [1] [2,3] [2] [3]   []
-------------------------------------------------

It's a binary decision tree.
We reach a leaf only after making a pick/not-pick decision for every element.
So the leaf represents a complete subsequence.

-> For-loop approach
Instead of making a binary decision for every element, we directly say: "Which element should I choose next?"
-------------------------------------
                []
          /      |      \
        [1]     [2]     [3]
       /   \      \
   [1,2] [1,3]   [2,3]
      |
   [1,2,3]
-------------------------------------
It's a variable-branching tree, and every node is already a complete subsequence.

>> The important connection
The for loop is essentially compressing the "don't pick" decisions.
For example, at: []
instead of explicitly saying: "don't pick 1 → don't pick 2 → pick 3", we simply choose 3 as the next element.

|    Pick / Not-Pick:
|    explicitly make both decisions
|            ↓
|    leaf = complete subsequence

|    For-loop:
|    loop movement implicitly represents not-pick decisions
|            ↓
|    each recursive state = complete subsequence

-------------------------------------------------------------------------------
>> Work Analysis
For n elements:

-> For-loop based generation
• Recursion-tree nodes: exactly 2ⁿ
• Each node represents a subsequence
• Traversal work: proportional to 2ⁿ
• Output copying: O(n · 2ⁿ)
• Total: O(n · 2ⁿ)
So, roughly: Work ≈ 2^n recursive states
	​
-> Pick / Not-Pick generation
It creates a complete binary tree of depth n.
• Leaf nodes: 2ⁿ
• Internal nodes: 2ⁿ - 1
• Total nodes: 2ⁿ + (2ⁿ - 1) = 2ⁿ⁺¹ − 1
• Traversal work: proportional to 2ⁿ⁺¹ − 1
• Output copying: O(n · 2ⁿ)
• Total: O(n · 2ⁿ)
So, roughly: Work ≈ 2ⁿ⁺¹ recursive states

-> The practical comparison

For-loop: ~ 2ⁿ states
Pick/Not-Pick: ~ 2 × 2ⁿ states

For example, with n = 20:
For-loop:       1,048,576 states
Pick/not-pick:  2,097,151 states
So yes, the for-loop approach does less recursive-tree work — roughly half as many states.

But asymptotically: O(2ⁿ⁺¹ − 1) = O(2(2ⁿ) - 1) = O(2ⁿ)

so we still write:
Both → O(2ⁿ) traversal
Both → O(n · 2ⁿ) including output

>> The takeaway
| Same Big-O does NOT mean same amount of work.
The for-loop approach has a smaller recursion tree and less constant-factor overhead, 
so it can be faster in practice, while both have the same asymptotic complexity 
because both grow exponentially at the same rate.
*/

void generate(vector<int>& nums, int ind, vector<int>& ds, vector<vector<int>>& powerSet) {
    powerSet.push_back(ds);         // at every step, ds represents a subsequence
    // thus for every recursive call, we simply add the current subset `ds` to result 

    for (int i = ind; i < nums.size(); i++) {
        ds.push_back(nums[i]);                    // choose
        generate(nums, i + 1, ds, powerSet);      // recurse
        ds.pop_back();                            // undo
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> powerSet;
    vector<int> ds = {};

    // recurseSubsets(nums, 0, ds, powerSet);
    generate(nums, 0, ds, powerSet);
    
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