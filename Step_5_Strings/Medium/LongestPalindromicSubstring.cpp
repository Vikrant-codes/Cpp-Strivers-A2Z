/*
Leetcode - 5. Longest Palindromic Substring : Medium

Given a string s, return the longest palindromic substring in s.

Examples :-

Input: s = "babad" __ Output: "bab"
Explanation: "aba" is also a valid answer.

Input: s = "cbbd" __ Output: "bb"

Constraints :-
- 1 <= s.length <= 1000
- s consist of only digits and English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^3) __ Space Complexity : O(n)
// for each substring check whether it's palindrome, if it is then check whether it's the longest one.
bool isPalindrome(string& s) {
    int i=0, j=s.size()-1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}
string longestPalindrome(string s) {
    string ans = "";
    for (int i=0; i<s.size(); i++) {
        string subs = "";
        for (int j=i; j<s.size(); j++) {
            subs += s[j];
            // if current substring is Palindrome and is longer than the ans substring, then ans = current substring
            if (isPalindrome(subs) && subs.size() > ans.size()) ans = subs;
        }
    }
    return ans;
}

// Optimal Approach (Expand Around Center) :- Time Complexity : O(n^2) __ Space Complexity : O(1)
// " This approach is not the most optimal one. "
/*
🔹 Intuition (Expand Around Center)
| A palindrome is symmetric around its center.

We consider how to check for a palindormic string 
There are 2 ways, first one is to start from the end points and come inwards while checking the left & right pointer chars.
The other way is to start from the center and then expand about the center checking the left & right chars.
Like for palindrome "cbabc",
we can either place l & r at end-points 'c' and come towards 'a' (l++, r--) while checking for palindrome 
or, we can also place l & r at center 'a' and then expand around center (l--, r++) while checking for palindrome. 
Also, if the palindrome is of even length, then it will have two centers ex- "baab" has two centers 'a'

Every palindrome has:
• One center → odd length (aba)
• Two centers → even length (abba)

So instead of checking all substrings, we:
1. Treat every index as a possible center (odd)
2. Treat every gap between indices as a center (even)
3. Expand outward from the center as long as characters match
4. Keep track of the longest valid expansion and the start point of that expansion.

This avoids unnecessary checks and focuses only on valid palindromes.

🔹 Algorithm (Steps)
1. Initialize start = 0, maxLen = 1
2. For each index i in the string:
    • Expand around (i, i) → odd-length palindrome
    • Expand around (i, i+1) → even-length palindrome
3. During expansion:
    • While characters match and bounds are valid
    • Update start and maxLen if a longer palindrome is found
4. Return substring using start and maxLen

🔹 Complexity Analysis
⏱ Time Complexity: O(n²)
• There are n centers
• Each expansion can take up to O(n) in the worst case
• Example worst case: "aaaaaa"

💾 Space Complexity: O(1)
• Only index variables used
• No extra arrays or DP tables

🔹 Why this is optimal (practically)
| Approach             | Time      | Space    |
| -------------------- | --------- | -------- |
| Brute Force          | O(n³)     | O(1)     |
| Expand Around Center | **O(n²)** | **O(1)** |
| Manacher’s           | O(n)      | O(n)     |

👉 Expand Around Center is:
• Easy to implement
• Efficient enough for interviews
• Cleaner than DP
• Preferred over Manacher unless required

🔹 One-line takeaway
| A palindrome grows symmetrically, so we expand from every possible center and keep the longest one.
*/

void expand(string& s, int l, int r, int& start, int& maxLen) {
    int n = s.size();
    while (l >= 0 && r < n && s[l] == s[r]) {
        // length of current palindromic substring with l & r as it's end-points = r - l + 1
        if (r - l + 1 > maxLen) {
            start = l;
            maxLen = r - l + 1;
        }
        l--; r++;
    }
}

string longestPalindrome(string s) {
    int n = s.size();
    int start = 0, maxLen = 1;

    for (int i = 0; i < n; i++) {
        expand(s, i, i, start, maxLen);       // odd length
        expand(s, i, i + 1, start, maxLen);   // even length
    }

    return s.substr(start, maxLen);
}

int main() {
    return 0;
}