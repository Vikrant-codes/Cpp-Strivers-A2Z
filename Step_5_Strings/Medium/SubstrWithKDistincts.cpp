/*
GFG - Substrings with K Distinct : Medium

You are given a string s consisting of lowercase characters and an integer k, 
You have to count all possible substrings that have exactly k distinct characters.

Examples :-

Input: s = "abc", k = 2 __ Output: 2
Explanation: Possible substrings are ["ab", "bc"]

Input: s = "aba", k = 2 __ Output: 3
Explanation: Possible substrings are ["ab", "ba", "aba"]

Input: s = "aa", k = 1 __ Output: 3
Explanation: Possible substrings are ["a", "a", "aa"]

Constraints :-
1 ≤ s.size() ≤ 10^6
1 ≤ k ≤ 26
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^3) __ Space Complexity : O(1) 
/*
Naive Approach :- 
Check for each substring, the no of distinct characters it have. If that count is equal to k, then consider that substring.
*/

// distinctChars function return the count of distinct chars in the substring
int distinctChars(string s) {
    unordered_set<char> st;
    for (char c : s) st.insert(c);
    return st.size();
}
int countSubstrNaive(string& s, int k) {
    if (k > s.size()) return 0;             // if no of distinct chars is greater than string size return 0
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        string substr = "";
        for (int j=i; j<n; j++) {
            substr += s[j];
            int distinct = distinctChars(substr);       // no. of distinct chars in the current substring 
            if (distinct == k) cnt++;
        }
    }
    return cnt;
}

int main() {
    string s = "abcbacdeffgabcd";
    cout << "All Substrings of s are :- " << endl;
    int cnt = countSubstrNaive(s, 3);
    cout << "Count : " << cnt;

    return 0;
}