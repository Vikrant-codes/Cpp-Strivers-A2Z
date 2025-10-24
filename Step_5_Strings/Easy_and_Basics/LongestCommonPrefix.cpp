/*
Leetcode - 14. Longest Common Prefix : Easy

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Examples :-

Input: strs = ["flower","flow","flight"] __ Output: "fl"

Input: strs = ["dog","racecar","car"] __ Output: ""
Explanation: There is no common prefix among the input strings.

Constraints :- 
1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters if it is non-empty.
*/

#include <bits/stdc++.h>
using namespace std;

// Helper Function :- This function helps to find the longest common prefix of two strings s1 & s2
// Time Complexity : O(n) where n = min(s1.size, s2.size) __ Space Complexity : O(1)
string findLCP(string s1, string s2) {
    int n = s1.size(); 
    int m = s2.size();
    int size = min(n, m);

    string lcp = "";

    for (int i=0; i<size; i++) {
        if (s1[i] == s2[i]) lcp += s1[i];
        else break;
    }

    return lcp;
}

/*
🧩 Approach 1 — Pairwise LCP Reduction

💡 Intuition
The idea is to gradually reduce the common prefix as you compare each new word.
If the common prefix between the first few words is "fl", and the next word doesn’t share "fl", the prefix shrinks accordingly.
By the end, you’re left with the prefix that all words share.

⚙️ Algorithm
1. Start with lcp = strs[0].
2. For each string strs[i] (from index 1 to end):
-- Find the common prefix between lcp and strs[i] using the helper function findLCP().
-- Update lcp with this new prefix.
-- If lcp becomes empty, stop early — no common prefix exists.
3. Return the final lcp.

🧠 Complexity Analysis
-> Time :
Each findLCP takes O(min(len(lcp), len(strs[i]))). In the worst case (all strings identical of length m), so O(m)
Thus,  O(n × m), where n = number of strings, m = average string length.
-> Space: O(1) — only a few auxiliary variables.

✅ Remarks
-- Simple and intuitive.
-- Easy to implement and debug.
-- Works well when the number of strings is small or average prefix is short.

🧩 Approach 2 — Sorting Trick (First–Last Comparison)

💡 Intuition
If you sort the strings lexicographically, the strings that differ the most will be placed at the extremes 
(first and last in sorted order).
👉 Therefore, the LCP of the entire list is the same as the LCP of the first and last strings.
Because sorting aligns similar prefixes together.

⚙️ Algorithm
1. Sort the array of strings.
2. Compare only the first and last strings character by character to find their common prefix.
3. Return that prefix.

🧠 Complexity Analysis
-> Time:
Sorting: O(n × m × log n) (since string comparisons take up to O(m) each).
Comparing first & last: O(m).
Total: O(n × m × log n).
-> Space: O(1) (ignoring sort’s internal memory).

✅ Remarks
-- Conceptually elegant and short.
-- Performs well when n is small or when sorting overhead isn’t significant.
-- Slightly slower asymptotically than the first approach, but often faster in practice for small inputs.

✅ Verdict:
Your first solution is the more optimal in terms of time complexity,
while your second solution is more elegant and compact — both are perfectly acceptable depending on the situation.
*/

// Approach 1 (Pairwise Reduction of LCP) :- Time Complexity : O(n × m) __ Space Complexity : O(1)
string longestCommonPrefix1(vector<string>& strs) {
    int n = strs.size();
    if (n == 1) return strs[0];

    string lcp = strs[0]; 

    for (int i=1; i<n; i++) {
        lcp = findLCP(lcp, strs[i]);
    } 
    return lcp;
}
// Approach 2 (Sorting Trick) :- Time Complexity : O(n × m × log n) __ Space Complexity : O(1)
string longestCommonPrefix2(vector<string>& strs) {
    sort(strs.begin(), strs.end());
    int n = strs.size();
    
    return findLCP(strs[0], strs[n-1]);
}

int main() {

    return 0;
}