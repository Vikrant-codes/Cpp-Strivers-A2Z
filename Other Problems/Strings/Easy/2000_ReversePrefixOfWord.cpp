/*
Leetcode - 2000. Reverse Prefix of Word : Easy

Given a 0-indexed string word and a character ch, 
reverse the segment of word that starts at index 0 and ends at the index of the first occurrence of ch (inclusive). 
If the character ch does not exist in word, do nothing.

For example, if word = "abcdefd" and ch = "d", then you should reverse the segment that starts at 0 and ends at 3 (inclusive). 
The resulting string will be "dcbaefd".
Return the resulting string.

Examples :-

Input: word = "abcdefd", ch = "d" __ Output: "dcbaefd"
Explanation: The first occurrence of "d" is at index 3. 
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "dcbaefd".

Input: word = "xyxzxe", ch = "z" __ Output: "zxyxxe"
Explanation: The first and only occurrence of "z" is at index 3.
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "zxyxxe".

Input: word = "abcd", ch = "z" __ Output: "abcd"
Explanation: "z" does not exist in word.
You should not do any reverse operation, the resulting string is "abcd".

Constraints :-
- 1 <= word.length <= 250
- word consists of lowercase English letters.
- ch is a lowercase English letter.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)

// helper function to reverse a portion of string word, starting from index 0 till index ind (inclusive) 
void reverse(string& word, int ind) {
    int i = 0, j = ind;
    while (i < j) {
        swap(word[i], word[j]);
        i++;
        j--;
    }
}

string reversePrefix(string word, char ch) {
    int idx = -1;           // first occurrence index
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == ch) {
            idx = i;
            break;
        }
    }
    // reverse the string portion only if character exists
    if (idx != -1)
        reverse(word, idx);
    return word;
}

int main() {
    return 0;
}