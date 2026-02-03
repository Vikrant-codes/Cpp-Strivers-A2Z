/*
Leetcode - 541. Reverse String II : Easy

Given a string s & an integer k, reverse the first k characters for every 2k characters counting from the start of the string.
If there are fewer than k characters left, reverse all of them. 
If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and leave the other as original.

Examples :-

Input: s = "abcdefg", k = 2 __ Output: "bacdfeg"
Input: s = "abcd", k = 2 __ Output: "bacd"

Constraints :-
1 <= s.length, k <= 10^4
s consists of only lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Two Pointer Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition

Process the string in chunks of size 2k.
For every chunk you only need to reverse the first k characters and leave the next k alone.
So jump by 2k each time and reverse the substring from i to min(i+k-1, n-1).
The min handles the last partial chunk:
- if fewer than k remain → reverse them all;
- if between k and 2k remain → reverse the first k only.
*/
void reverse(string &s, int l, int r) {
    while (l < r) {
        swap(s[l], s[r]);
        l++; r--;
    }
}
/*
// The code I first wrote
string reverseStr(string s, int k) {
    int n = s.size();
    int start = 0, end = 2*k -1;
    while (end < n) {
        reverse(s, start, start+k-1);
        start = end+1;
        end += 2*k; 
    }
    if (start < n) {
        if (start+k-1 < n) reverse(s, start, start+k-1);
        else reverse(s, start, n-1);
    }
    return s;
}
*/
string reverseStr(string s, int k) {
    int n = s.size();
    for (int i=0; i < n; i += 2*k) {
        int end = min(i+k-1, n-1);
        reverse(s, i, end);
    }
    return s;
}

int main() {
    return 0;
}