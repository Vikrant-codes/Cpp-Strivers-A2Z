/*
Leetcode - 131. Palindrome Partitioning : Medium

Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

Examples :-

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Input: s = "a"
Output: [["a"]]

Constraints :-
• 1 <= s.length <= 16
• s contains only lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Backtracking Solution: Time Complexity : O(2^n ∙ n) __ Space Complexity : O(n)
/*
>> Intuition — Palindrome Partitioning — Backtracking (My approach same as Striver's)
The goal is to divide the string into all possible partitions such that every substring in the partition is a palindrome.

For example, for: s = "aab"
we want to consider all possible ways of splitting the string:
    "a" | "a" | "b"
    "aa" | "b"
    "aab"

Then we keep only the partitions where every part is a palindrome:
    "a" | "a" | "b"    ✓
    "aa" | "b"        ✓
    "aab"             ✗

The natural way to explore all these possibilities is backtracking.

At any point, suppose we are at index ind. 
We need to decide how many partitions can start with this index, 
i.e., with ind as start, how many palindromic substrings exists.
These palindromic substrings would then act as separate possible partitions 
and we will need to recursively partition the remaining portion of string to get all the possible partitions.

So, we try every possible ending position i: s[ind ... i] and for each such substring:
• If it is not a palindrome, we skip it.
• If it is a palindrome, we add it to our current partition and 
  recursively find all possible palindromic partitions starting from i + 1.
• After the recursive call, we remove the substring so that we can try another possible starting substring (backtrack).

For example, for: s = "aab"
starting at index 0, we try:
    "a"    → palindrome → explore remaining "ab"
    "aa"   → palindrome → explore remaining "b"
    "aab"  → not palindrome → skip

The recursion continues doing the same thing for the remaining suffix, 
thereby exploring every possible combination of palindromic substrings.

>> The important recursive idea
Suppose we chose: "aa" from: "aab"
We've consumed indices 0...1.
The remaining part starts at index 2:
    aa | b
         ↑
        ind

So we recursively call: solve(s, i + 1, curr, ans);
This recursive call explores every possible way of partitioning the remaining string.

This means: " We've already decided that s[ind...i] is one palindrome. 
              Now find all possible palindromic partitions of the remaining string starting at i + 1."

And this is where the recursive exploration gives us all possible partitions.

>> Why does this try every possible partition?
At every starting index, we try every possible palindromic substring starting there.
For example: s = "aab"
Start at index 0:
    "a"  → recursively partition "ab"
    "aa" → recursively partition "b"
    "aab" → not palindrome, ignore

So, the branches "a" && "aa" are explored which gives us the following partitions.

                  "|aab"
                     |
            ---------------------------
            |            |            |
         "a|ab"        "aa|b"       "aab|"
         /    \          |            X ("aab" not a palindrome)
    "a|a|b"  "a|ab|"   "aa|b|"
        |       X         ✓
    "a|a|b|"
        ✓

"|" in the string represents the partition, at each index ind, we check all substrings starting from this index 
and explore the further branches considering that substring partition only if the substring is a palindrome.
For string s = "aab", we thus get the two partitions: ["a", "a", "b"] and ["aa", "b"]

To check for the palindromic substrings and recursive branch exploration, we use a for loop from 'ind' to end of string.
An important point is that we cannot break out of this loop when we encounter a non-palindromic substring. 
This is because a longer substring starting at the same index may still be a palindrome.

For example, with: s = "abba"

starting at index 0:
    "a"     → palindrome ✓
    "ab"    → not palindrome ✗
    "abb"   → not palindrome ✗
    "abba"  → palindrome ✓

Even though "ab" is not a palindrome, "abba" is. Therefore, we simply skip "ab" and continue trying longer substrings.

>> Base Case
When ind == s.size(), the entire string has been consumed. 
Since every substring chosen along that recursion path was a palindrome, the current partition is a valid answer, 
so we add it to ans.

>> Palindrome Checking
We can use a helper method which will help us know whether the current substring we are considering, is a palindrome.

>> Backtracking
We use a vector of strings `curr` or `path` which represents the partition we've constructed so far.
When we find a palindrome, we make that substring part of the current partition: `curr.push_back(str);`

Then we do the recursive call: `solve(s, i + 1, curr, ans);`
which explores every possible way of partitioning the remaining string.

After returning from recursion, we remove that choice: `curr.pop_back();`
Why? Because we now want to try a different partition at the current index.

For example:
    Choose "a"
        ↓
    explore everything beginning with "a"
        ↓
    remove "a"
        ↓
    choose "aa"
        ↓
    explore everything beginning with "aa"

This is the classic: choose → recurse → undo, backtracking pattern.

>> In short, the recursion follows this pattern:
|   Choose every possible substring starting at current index
|           ↓
|   Check if it is a palindrome
|           ↓
|   If yes → choose it → recurse on remaining string
|           ↓
|   Backtrack → remove it → try the next substring

This allows us to systematically explore all possible palindromic partitions without missing any valid combination.

>> Algorithm
1. Start the recursion from index 0.
2. At index ind, try every substring starting at ind.
3. Check whether the substring is a palindrome.
4. If it is:
    • add it to the current partition,
    • recursively partition the remaining suffix,
    • remove it afterward to backtrack.
5. When ind == n, add the current partition to the answer.


>> Complexity Analysis

Let n = s.length().

-> Number of possible partitions
There are n - 1 positions between characters where we can either: cut or: don't cut
Therefore, there can be up to: 2^(n-1) different ways to partition the string.

For example, for: abcd
there are three possible cut positions:
    a | b | c | d
      ^   ^   ^
Each position has two choices, giving: 2^3 = 8 possible partitions.
Our backtracking explores these possibilities, although non-palindromic branches are pruned.

-> Cost of palindrome checking
For every candidate substring, isPalindrome() can take: O(n) in the worst case.
So, ignoring the cost of copying curr, the backtracking exploration can be bounded roughly by: 
    O(2^n ∙ n) 
for the exploration and palindrome checking.

-> Space complexity
The recursion depth can be at most n, and `curr`/`path` can contain at most n substrings: 
O(n) auxiliary space, excluding the returned ans.
*/

// My Implementation
bool isPalindrome(string& s) {
    int l = 0, r = s.length()-1;

    while (l < r) {
        if (s[l] != s[r]) 
            return false;
        l++; r--;
    }

    return true;
}

void solve(string& s, int ind, vector<string>& curr, vector<vector<string>>& ans) {
    if (ind == s.size()) {
        ans.push_back(curr);
        return;
    }

    string str = "";
    for (int i = ind; i < s.size(); i++) {
        str += s[i];
        if (isPalindrome(str)) {
            curr.push_back(str);
            solve(s, i + 1, curr, ans);
            curr.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<string> curr;
    vector<vector<string>> ans;
    solve(s, 0, curr, ans);
    return ans;
}

// Striver's implementation
bool isPalindrome(string s, int start, int end) {
    while (start <= end) {
        if (s[start++] != s[end--])
            return false;
    }

    return true;
}

void func(int index, string s, vector<string>& path, vector<vector<string>>& res) {
    if (index == s.size()) {
        res.push_back(path);
        return;
    }

    for (int i = index; i < s.size(); i++) {
        if (isPalindrome(s, index, i)) {
            path.push_back(s.substr(index, i - index + 1));
            func(i + 1, s, path, res);
            path.pop_back();
        }
    }
}

vector<vector<string>> partitionStriver(string s) {
    vector<string> path;
    vector<vector<string>> res;
    func(0, s, path, res);
    return res;        
}

int main() {
    return 0;
}