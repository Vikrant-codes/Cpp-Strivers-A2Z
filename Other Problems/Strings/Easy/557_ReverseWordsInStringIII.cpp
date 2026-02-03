/*
Leetcode - 557. Reverse Words in a String III

Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace 
and initial word order.

Examples :-
Input: s = "Let's take LeetCode contest" __ Output: "s'teL ekat edoCteeL tsetnoc"
Input: s = "Mr Ding" __ Output: "rM gniD"

Constraints :-
- 1 <= s.length <= 5 * 10^4
- s contains printable ASCII characters.
- s does not contain any leading or trailing spaces.
- There is at least one word in s.
- All the words in s are separated by a single space.
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointer Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/* 
🧠 Intuition
The problem asks you to reverse each word individually while keeping their order in the sentence unchanged.
If you look at the string, every word is bounded by spaces — so:
When you hit a space, it means the end of a word.
You can reverse that word in place between its starting and ending indices.

⚙️ Algorithm (Step-by-step reasoning)
1. Initialize a pointer i = 0, marking the start of the current word.
2. Traverse the string using another pointer j:
-- When s[j] == ' ', it means the current word ends at j-1.
-- Reverse the word in-place using the helper function reverse(s, i, j-1).
-- Then set i = j + 1 to mark the start of the next word.
3. After the loop, reverse the last word separately (because it won’t end with a space).
4. Return the modified string.

⏱ Time Complexity : O(n) — Each character is visited and swapped at most once.
💾 Space Complexity : O(1) — In-place reversal; no extra memory used apart from a few variables.
*/
void reverse(string &s, int l, int r) {
    while (l < r) {
        swap(s[l], s[r]);
        l++; r--;
    }
}

string reverseWords(string s) {
    int n = s.size();
    int i = 0;

    for (int j=0; j<n; j++) {
        if (s[j] == ' ') {
            reverse(s, i, j-1);
            i = j + 1;
        }
    }
    reverse(s, i, n-1);

    return s;
}

int main() {
    string s = "Hello World xyz";
    string rv = reverseWords(s);
    cout << rv;
    
    return 0;
}