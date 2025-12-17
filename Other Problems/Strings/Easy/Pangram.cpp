/*
Leetcode - 1832. Check if the Sentence Is Pangram : Easy

A pangram is a sentence where every letter of the English alphabet appears at least once.
Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.

Examples :-

Input: sentence = "thequickbrownfoxjumpsoverthelazydog" __ Output: true
Explanation: sentence contains at least one of every letter of the English alphabet.

Input: sentence = "leetcode" __ Output: false

Constraints :-
- 1 <= sentence.length <= 1000
- sentence consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

bool checkIfPangram(string sentence) {
    vector<int> alphabets(26);
    for (char c : sentence) {
        int x = c - 'a';
        alphabets[x]++;
    }
    for (int x : alphabets) 
        if (x == 0) 
            return false;
    return true;
}

int main() {
    return 0;
}