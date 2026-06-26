/*
Leetcode - 2185. Counting Words With a Given Prefix : Easy

You are given an array of strings words and a string pref.
Return the number of strings in words that contain pref as a prefix.
A prefix of a string s is any leading contiguous substring of s.

Examples :-

Input: words = ["pay","attention","practice","attend"], pref = "at" __ Output: 2
Explanation: The 2 strings that contain "at" as a prefix are: "attention" and "attend".

Input: words = ["leetcode","win","loops","success"], pref = "code" __ Output: 0
Explanation: There are no strings that contain "code" as a prefix.
 
Constraints :-
- 1 <= words.length <= 100
- 1 <= words[i].length, pref.length <= 100
- words[i] and pref consist of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

bool hasPrefix(string& s, string& p) {
    if (s.length() < p.length())
        return false;
    
    for (int i = 0; i < p.length(); i++) 
        if (s[i] != p[i])
            return false;
    
    return true;
}

int prefixCount(vector<string>& words, string pref) {
    int ans = 0;

    for (string& s : words)
        if (hasPrefix(s, pref)) 
            ans++;
    
    return ans;
}

int main() {
    return 0;
}