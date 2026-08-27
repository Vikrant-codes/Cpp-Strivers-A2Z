/*
Leetcode - 2904. Shortest and Lexicographically Smallest Beautiful String : Medium

You are given a binary string s and a positive integer k.
A substring of s is beautiful if the number of 1's in it is exactly k.
Let len be the length of the shortest beautiful substring.
Return the lexicographically smallest beautiful substring of string s with length equal to len. 
If s doesn't contain a beautiful substring, return an empty string.

A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, 
a has a character strictly larger than the corresponding character in b.

For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, 
and d is greater than c.

Examples :-

Input: s = "100011001", k = 3
Output: "11001"
Explanation: There are 7 beautiful substrings in this example:
1. The substring "100011001".
2. The substring "100011001".
3. The substring "100011001".
4. The substring "100011001".
5. The substring "100011001".
6. The substring "100011001".
7. The substring "100011001".
The length of the shortest beautiful substring is 5.
The lexicographically smallest beautiful substring with length 5 is the substring "11001".

Input: s = "1011", k = 2
Output: "11"
Explanation: There are 3 beautiful substrings in this example:
1. The substring "1011".
2. The substring "1011".
3. The substring "1011".
The length of the shortest beautiful substring is 2.
The lexicographically smallest beautiful substring with length 2 is the substring "11".

Input: s = "000", k = 1
Output: ""
Explanation: There are no beautiful substrings in this example.

Constraints :-
• 1 <= s.length <= 100
• 1 <= k <= s.length
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(n^3) __ Space Complexity : O(n)

// checks two equal length strings s1 & s2, returns true if s1 is lexicographically smaller than s2
bool isSmaller(string& s1, string& s2) {
    int len = s1.size();

    int i = 0;
    while (i < len && s1[i] == s2[i]) 
        i++;
    
    if (i == len) 
        return false;     // both strings are equal
    
    return s1[i] < s2[i];
}

string shortestBeautifulSubstringNaive(string s, int k) {
    int n = s.length();

    string ans = "";

    // consider each index as the starting index of substrings, create substrings
    for (int i = 0; i <= n - k; i++) {

        if (s[i] == '0') continue;

        string substr = "";     // substring for current start_index `i`, initially empty
        int cnt1 = 0;           // count of 1s in current substring

        for (int j = i; j < n; j++) {
            substr += s[j];

            if (s[j] == '1') cnt1++;

            if (cnt1 == k) {
                if ( ans == "" || ans.length() > substr.length() || 
                     ( ans.length() == substr.length() && isSmaller(substr, ans) ) )
                    {
                        ans = substr;
                    }
                break;  // extending the current substring any further is no good
                // it would either make it ugly, or, just increase its length,
                // so `break` to consider the next 'start_index' 
            }
        }
    }

    return ans;
}

string shortestBeautifulSubstring(string s, int k) {
    int n = s.length();

    int start = 0;
    // place start at the index where first '1' is present
    while (start < n && s[start] == '0') start++;
    
    if (start == n) return "";      // string contains all 0s only
    if (k == 1) return "1";         // if k = 1, then "1" is the shortest & smallest beautiful string
    
    string ans = "";
    int cnt1 = 0;
    
    for (int end = start; end < n; end++) {
        if (s[end] == '1') cnt1++;
    
        // when cnt1 becomes `k`, that means current window substring is beautiful
        // update ans if needed and shrink the window until start points at the next `1`
        if (cnt1 == k) {

            string substr = s.substr(start, end - start + 1);

            // update ans to make sure ans remains the shortest and lexicographically smallest
            if ( ans == "" || ans.length() > substr.length() || 
            (ans.length() == substr.length() && isSmaller(substr, ans)) ) 
            {
                ans = substr;
            }

            // shrink the window to move start at the next 1
            start++;
            while (s[start] != '1') start++;

            cnt1--;     // since one '1' has been removed from the current window
        }
    }
    
    return ans;
}

// consider two substrings of s[ansStart .... ansStart + len-1], s[substrStart ... substrStart + len-1]
// returns true if the `substrStart` substring is lexicographically smaller than `ansStart` one
bool isSubstrSmaller(string& s, int ansStart, int substrStart, int len) {
    int i = ansStart, j = substrStart;
    while (i < ansStart + len && s[i] == s[j]) {
        i++; j++;
    }
    if (i == len) return false;     // both strings are equal

    return s[i] > s[j];
}

string shortestBeautifulSubstring2(string s, int k) {
    int n = s.length();
    int start = 0;
    // place start at the index where first '1' is present
    while (start < n && s[start] == '0') start++;
    if (start == n) return "";      // string contains all 0s only
    if (k == 1) return "1";         // if k = 1, then "1" is the shortest & smallest beautiful string
    int ansLen = 0;
    int ansStart = start;
    int cnt1 = 0;
    for (int end = start; end < n; end++) {
        if (s[end] == '1') cnt1++;
        // when cnt1 becomes `k`, that means current window substring is beautiful
        // update ans if needed and shrink the window until start points at the next `1`
        if (cnt1 == k) {
            int substrLen = end - start + 1;
            // update ans to make sure ans remains the shortest and lexicographically smallest
            if ( ansLen == 0 || ansLen > substrLen || 
            (ansLen == substrLen && isSubstrSmaller(s, ansStart, start, ansLen)) ) 
            {
                ansLen = substrLen;
                ansStart = start;
            }
            // shirnk the window to move start at the next 1
            start++;
            while (s[start] != '1') start++;
            cnt1--;     // since one '1' has been removed from the current window
        }
    }
    return s.substr(ansStart, ansLen);
}



int main() {

    return 0;
}