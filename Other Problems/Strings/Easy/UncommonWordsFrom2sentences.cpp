/*
Leetcode - 884. Uncommon Words from Two Sentences : Easy

A sentence is a string of single-space separated words where each word consists only of lowercase letters.
A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.

Examples :-

Input: s1 = "this apple is sweet", s2 = "this apple is sour" __ Output: ["sweet","sour"]
Input: s1 = "apple apple", s2 = "banana" __ Output: ["banana"]

Constraints :- 
- 1 <= s1.length, s2.length <= 200
- s1 and s2 consist of lowercase English letters and spaces.
- s1 and s2 do not have leading or trailing spaces.
- All the words in s1 and s2 are separated by a single space.
*/

#include <bits/stdc++.h>
using namespace std;

// HashMap Approach :- Time Complexity : O(N + U) ≈ O(N) __ Space Complexity : O(U), where U = no. of uncommon words
/*
🧠 Intuition
The problem asks for words that appear exactly once across both sentences combined.
To solve this, the key idea is to:
- Count how many times each word appears in total (in both sentences).
- Then collect the ones that appear exactly once.
You don’t need to separate the sentences or track where the words came from — just aggregate their frequencies.

⚙️ Algorithm
1. Initialize an unordered map mpp to store each word and its frequency.
2. Define a helper function wordCount(mpp, s) that:
-- Iterates through string s.
-- Extracts each word (splitting on spaces).
-- Increments its count in mpp.
3. Call wordCount on both s1 and s2 — this combines word counts for both sentences.
4. Iterate through the map:
-- If a word’s count is exactly 1, add it to the answer vector.
5. Return the answer vector.

⏱ Complexity Analysis

Time Complexity: O(N + U) ≈ O(N)
- O(N) — where N is the total length of both sentences combined.
--> Each character is processed once while splitting words.
--> Map insertion and lookup take O(1) on average (unordered_map).
- Iterating over the map adds O(U), where U is the number of unique words.
- ✅ Overall: O(N + U) ≈ O(N)

Space Complexity: O(U) — to store word counts in the map and the result vector.
*/
void wordCount(unordered_map<string, int> &mpp, string s) {
    string word = "";
    for (int i=0; i<s.size(); i++) {
        if (s[i] == ' ') {
            mpp[word]++;
            word = "";
        }
        else word += s[i];
    }
    mpp[word]++;
}

vector<string> uncommonFromSentences(string s1, string s2) {
    // keeps count of occurence of each word
    unordered_map<string, int> mpp;

    vector<string> ans;

    wordCount(mpp, s1); // update word count of sentence 1
    wordCount(mpp, s2); // update word count of sentence 2
    // for each word, frequency pair in map, check for the words with frequency 1. If found, add that word to ans vector
    for (auto x: mpp) {
        if (x.second == 1) {
            ans.push_back(x.first);
        } 
    }

    return ans;
}

int main() {

    return 0;
}