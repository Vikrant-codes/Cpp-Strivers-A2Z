/*
Leetcode - 1941. Check if All Characters Have Equal Number of Occurrences : Easy

Given a string s, return true if s is a good string, or false otherwise.
A string s is good if all the characters that appear in s have the same number of occurrences (i.e., the same frequency).

Examples :-

Input: s = "abacbc"
Output: true
Explanation: The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2 times in s.

Input: s = "aaabb"
Output: false
Explanation: The characters that appear in s are 'a' and 'b'.
'a' occurs 3 times while 'b' occurs 2 times, which is not the same number of times.

Constraints :-
- 1 <= s.length <= 1000
- s consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
bool areOccurrencesEqual(string s) {
    vector<int> hashArr(26);
    for (char& c : s) {
        hashArr[c - 'a']++;
    }
    int cnt = hashArr[s[0] - 'a'];

    for (int& freq : hashArr)
        if (freq != 0 && freq != cnt)
            return false;
    
    return true;
}

int main() {
    return 0;
}