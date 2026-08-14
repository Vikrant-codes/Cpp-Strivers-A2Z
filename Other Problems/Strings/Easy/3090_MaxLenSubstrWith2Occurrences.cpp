/*
Leetcode - 3090. Maximum Length Substring With Two Occurrences : Easy

Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.

Examples :-

Input: s = "bcbbbcba" __ Output: 4
Explanation:
The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".

Input: s = "aaaa" __ Output: 2
Explanation:
The following substring has a length of 2 and contains at most two occurrences of each character: "aaaa".

Constraints :-
• 2 <= s.length <= 100
• s consists only of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Since the constraints are small, even the brute force solution would work for this problem

// Brute Force : Time Complexity : O(n^3) __ Space Complexity : O(n)
// Generate all substrings, and if they are valid, find their length. Keep track of the maximum length.
bool isValid(string& sub) {
    unordered_map<char, int> freq;
    for (char ch: sub) {
        freq[ch]++;
        if (freq[ch] > 2) 
            return false;
    }
    return true;
}

int maximumLengthSubstringBrute(string s) {
    int n = s.size();
    int len = 0;
    for (int i = 0; i < n; i++) {
        string sub = "";
        for (int j = i; j < n; j++) {
            sub += s[j];
            if (!isValid(sub)) break;
            len = max(len, (int) sub.size());        
        }
    }
    return len;
}

// Better Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
We don't actually build substrings and check their validity.
Instead, for each index i, we treat it as the starting index of a substring and 
try to find the longest valid substring which can be formed with this `i` as staring index.
Once the substring becomes invalid, we break out of the loop to try out the next index.
*/
int maximumLengthSubstring(string s) {
    int n = s.size();
    int len = 0;

    for (int i = 0; i < n; i++) {
        unordered_map<char, int> freq;
        for (int j = i; j < n; j++) {
            freq[s[j]]++;
            if (freq[s[j]] > 2) break;
            len = max(len, j - i + 1);
        }
    }
    return len;
}

// Optimal Approach (Using Sliding Window + Hashing) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
We maintain a valid substring window while traversing the string using two pointers.
Whenever the window is expanded by introducing a new character, the validity of the window might become false,
(this happens when the newly added character's frequency exceeds 2 in the current window).
When window becomes invalid, we shrink it down until it becomes valid again (until freq[end] becomes <= 2).
We can track the maximum window length and return it at the end.
*/
int maximumLengthSubstring(string s) {
    int n = s.size();

    int len = 0;
    int start = 0;
    unordered_map<char, int> freq;
    
    for (int end = 0; end < n; end++) {
        freq[s[end]]++;
    
        while (freq[s[end]] > 2) {
            freq[s[start]]--;
            start++;
        }
    
        len = max(len, end - start + 1);
    }

    return len;
}

int main() {
    return 0;
}