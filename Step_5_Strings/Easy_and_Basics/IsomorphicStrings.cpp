/*
Leetcode - 205. Isomorphic Strings

Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. 
No two characters may map to the same character, but a character may map to itself.

Examples :-

Input: s = "egg", t = "add" __ Output: true
Explanation:
The strings s and t can be made identical by:
Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

Input: s = "foo", t = "bar" __ Output: false
Explanation:
The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Input: s = "paper", t = "title" __ Output: true

Constraints :-
1 <= s.length <= 5 * 10^4
t.length == s.length
s and t consist of any valid ascii character.
*/

#include <bits/stdc++.h>
using namespace std;

// Bidirectional Mapping Check :- Time Complexity : O(n) __ Space Complexity : O(1) 
/*
🧠 Intuition
Two strings s and t are isomorphic if each character in s can be replaced to get t, with a one-to-one mapping.
- That means no two characters in s map to the same character in t, and vice versa.
- So we need bidirectional mapping between s and t.

⚙️ Algorithm
1. Use two hash maps:
    - mp1 for s[i] → t[i]
    - mp2 for t[i] → s[i]
2. Iterate through each character pair (s[i], t[i]):
    - If s[i] already maps to a different t[i], return false.
    - If t[i] already maps to a different s[i], return false.
    - Otherwise, record the mapping in both maps.
3. If we finish the loop without conflicts, the strings are isomorphic → return true

⏱️ Complexity Analysis
Time Complexity: O(n) — single pass through the strings.
Space Complexity: O(1) — maps store at most 256 ASCII characters (or 128 for standard ASCII).
*/
bool isIsomorphic(string s, string t) {
    unordered_map<char, char> mp1, mp2;
    int n = s.size();

    for (int i=0; i<n; i++) {
        char ch1 = s[i];
        char ch2 = t[i];
        // if ch1 already exists in map 1
        if (mp1.count(ch1) && (mp1[ch1] != ch2) ) return false;
        // if ch2 already exists in map 2
        if (mp2.count(ch2) && (mp2[ch2] != ch1) ) return false;
        
        mp1[ch1] = ch2;
        mp2[ch2] = ch1;
    }

    return true;
}

// Last Seen Position / pattern encoding via index mapping :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
➡️ Logical Reasoning Behind Last Seen Positions
1. What we care about:
For every character pair (s[i], t[i]) at index i, we want to ensure the mapping is consistent with previous occurrences.

2. Observation:
Suppose s[i] appeared before at index p. Its corresponding character in t must have appeared at the same index pattern in t.
Example: s = "paper", t = "title"
At i=0: p→t → first occurrence, fine.
At i=2: p appeared before at i=0. Its mapping must be t[2] = t[0] (consistent).
If t[2] != t[0], the mapping is inconsistent → not isomorphic.

3. Encoding pattern with indices:
Instead of explicitly storing p→t mappings, we can store the last seen index for every character in s and t.
Let arr1[c] = last index c appeared in s
Let arr2[c] = last index c appeared in t
At any index i: if (arr1[s[i]] != arr2[t[i]]) return false;
-- If last-seen positions match, the “pattern” is consistent.
-- If they differ, it means this character in s is mapped inconsistently to t → not isomorphic.

4. Why i+1 instead of i:
Arrays are initialized with 0.
i+1 ensures first occurrence is treated as 0 (not seen yet) → avoids false mismatch.


🧠 Intuition
- Two strings are isomorphic if the pattern of character occurrences is the same.
- Track the last position each character appeared in both strings.
- If the last seen positions mismatch for corresponding characters at any index, the mapping is inconsistent → not isomorphic.
- Using i + 1 instead of i allows 0 to indicate “not seen yet,” so the first occurrence is correctly handled.
Think of it as checking if the “shape” of the two strings’ character patterns is identical.

⚙️ Algorithm
1. Initialize two arrays arr1 and arr2 of size 256 (to cover all ASCII characters) with 0s.
    arr1[c] = last index where character c appeared in s.
    arr2[c] = last index where character c appeared in t.
2. Iterate through both strings simultaneously:
    For each pair (s[i], t[i]):
        If arr1[s[i]] != arr2[t[i]] → return false (inconsistent mapping).
        Else, set arr1[s[i]] = i + 1 and arr2[t[i]] = i + 1.
3. If no mismatch is found after iterating, return true.

⏱️ Complexity Analysis
Time Complexity: O(n) — one pass through the strings.
Space Complexity: O(1) — two arrays of fixed size 256, independent of string length.

Summary Intuition :
    - Use the last seen positions of characters to encode the “pattern” of each string.
    - If patterns match at every index, the strings are isomorphic.
    - Elegant and efficient, avoids hash maps, and uses constant space.
*/
bool isIsomorphic(string s, string t) {
    int arr1[256] = {0}, arr2[256] = {0};
    int n = s.size();

    for (int i=0; i<n; i++) {
        char c1 = s[i], c2 = t[i];
        if (arr1[c1] != arr2[c2]) return false;
        arr1[c1] = i+1;
        arr2[c2] = i+1;
    }

    return true;
}

int main() {

    return 0;
}