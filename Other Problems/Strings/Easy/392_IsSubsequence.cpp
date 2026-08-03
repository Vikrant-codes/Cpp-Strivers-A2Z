/*
Leetcode - 392. Is Subsequence : Easy

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string 
by deleting some (can be none) of the characters 
without disturbing the relative positions of the remaining characters. 
(i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Examples :-

Input: s = "abc", t = "ahbgdc"
Output: true

Input: s = "axc", t = "ahbgdc"
Output: false

Constraints :-
• 0 <= s.length <= 100
• 0 <= t.length <= 10^4
• s and t consist only of lowercase English letters.

Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109, 
and you want to check one by one to see if t has its subsequence. 
In this scenario, how would you change your code?
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointers Approach : Time Complexity : O(t.size()) = O(n) __ Space Complexity : O(1)
/*
• Initialize two pointers: i for string s and j for string t, both starting at index 0.
• Traverse both strings while neither pointer has reached the end of its respective string.
• If s[i] == t[j], the current character of s has been found in t. Increment both i and j to match the next character.
• Otherwise, increment only j to continue searching for s[i] in the remaining part of t.
• Continue this process until either all characters of s have been matched or t has been completely traversed.
• After the loop, if i == s.size(), every character of s has been matched in order, so s is a subsequence of t. Return true.
• Otherwise, t has been exhausted before all characters of s could be matched, so return false.

>> Time Complexity : 
The two pointers i & j traverse the two strings s & t. In worst cases, t is fully traversed, 
so total time: O(t.size()) = O(n)
*/
bool isSubsequence(string s, string t) {
    // empty substring is always a sub-sequence
    if (s.empty()) return true;
    // not needed to explicitly handle this empty string s case, it will be handled by logic itself

    int m = s.size();
    int n = t.size();
    int i = 0, j = 0;
    
    while (i < m && j < n) {
        if (s[i] == t[j]) {
            i++;
            j++;
        }
        else j++;
    }

    return i == m;
}

// Follow up -> Solution (Pre-processing + binary search)

int main() {
    return 0;
}