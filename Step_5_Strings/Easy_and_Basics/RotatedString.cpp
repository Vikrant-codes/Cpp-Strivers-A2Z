/*
Leetcode - 796. Rotate String : Easy

Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.
For example, if s = "abcde", then it will be "bcdea" after one shift.

Examples :-

Input: s = "abcde", goal = "cdeab"
Output: true

Input: s = "abcde", goal = "abced"
Output: false

Constraints :-
1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Brute Force / Naive Approach :- Time Complexity: O(n^2) __ Space Complexity: O(n)
/*
Intuition :-
We need to check whether goal is a rotated/left-shifted version of string s or not. 
String goal is a rotation of s if there exists some index i such that shifting the first i chars of s to the end gives goal.
For string s of size n the rotation index i can be between [0,n) so we run a loop from 0 to n 
and considering i as the rotation point, we check if the rotated string at index i equals goal or not.
Rotated string at index i can be found using s.substr(i) + s.substr(0, i) 
since s.substr(i) gives substring from ith index to index and s.substr(0, i) gives substring from 0th index to i-1th index

Algorithm :-
- Start by generating all possible left rotations of the original string using substring slicing and concatenation.
- For each rotated version of the string, compare it with the target (goal) string.
- If a match is found at any point, return true immediately as the goal can be achieved.
- If none of the rotations match the goal string after checking all possibilities, return false.

Complexity Analysis :-
- Time Complexity: O(n^2)
  Each substr call is O(n), and we do it twice for each of the n rotations → O(n²).
  Comparing two strings of length n → O(n), which is already included in the rotation creation step.
  Overall: O(n^2)
- Space Complexity: O(n) for the temporary rotated string.
*/
bool rotateStringNaive(string s, string goal) {
    if (s.size() != goal.size()) return false;
    int n = s.size();
    for (int i=0; i<n; i++) {
        string rotated = s.substr(i) + s.substr(0, i);
        if (rotated == goal) return true;
    }
    return false;
}

// Optimal Approach :- Time Complexity : O(n) / O(n^2) (worst-case) __ Space Complexity : O(2n)
/*
Intuition & Algorithm:
1. Any rotation of s will appear as a substring of s + s.
Example: s = "abc", then s+s = "abcabc" contains all rotations: "abc", "bca", "cab".
2. Check if goal is a substring of s + s.
3. If yes, return true; otherwise, return false.

Complexity Analysis :- 
- Time Complexity : O(n) (average case) / O(n^2) worst-case (due to internal implementation working of find function)
  Constructing s + s → O(n).
  find() → worst-case O(n²) using naive substring search, but in practice often optimized (like KMP internally) → O(n).
  Overall: O(n) if find uses efficient substring search.
- Space Complexity: O(2n) for the concatenated string s + s.
*/
bool rotateString(string s, string goal) {
    if (s.size() != goal.size()) return false;
    string s2 = s + s;
    return s2.find(goal) != string::npos;
}

int main() {

    return 0;
}