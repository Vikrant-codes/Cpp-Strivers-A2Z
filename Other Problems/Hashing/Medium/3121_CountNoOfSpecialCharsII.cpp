/*
Leetcode - 3121. Count the Number of Special Characters II : Medium

You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, 
and every lowercase occurrence of c appears before the first uppercase occurrence of c.
Return the number of special letters in word.

Examples :-

Input: word = "aaAbcBC" __ Output: 3
Explanation: The special characters are 'a', 'b', and 'c'.

Input: word = "abc" __ Output: 0
Explanation: There are no special characters in word.

Input: word = "AbBCab" __ Output: 0
Explanation: There are no special characters in word.

Constraints :-
- 1 <= word.length <= 2 * 10^5
- word consists of only lowercase and uppercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (HashArray) :- Time Complexity : O(n) __ Space Complexity : O(1)
int numberOfSpecialChars(string word) {
    vector<int> lastLowerOcc(26, -1);       // store last occurrence index of lowercase characters
    vector<int> firstUpperOcc(26, -1);      // store first occurrence index of uppercase characters

    for (int i = 0; i < word.length(); i++) {
        char ch = word[i];
        // if char is lowercase, update the last occurrence index for current char
        if (ch >= 'a' && ch <= 'z') {
            lastLowerOcc[ch - 'a'] = i;
        }
        // if char is uppercase
        else {
            // if the char has not been previously seen, update its first occurrence index
            if (firstUpperOcc[ch - 'A'] == -1)
                firstUpperOcc[ch - 'A'] = i;
        }
    }

    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        // if current alphabet appears in both lowercase and uppercase
        if (lastLowerOcc[i] != -1 && firstUpperOcc[i] != -1) 
            // increment count only if last occurrence index of lowercase < first occurrence index of uppercase
            if (lastLowerOcc[i] < firstUpperOcc[i])
                cnt++;
    }

    return cnt;
}

int main() {
    return 0;
}