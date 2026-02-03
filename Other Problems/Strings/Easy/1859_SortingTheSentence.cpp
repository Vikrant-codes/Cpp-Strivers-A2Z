/*
Leetcode - 1859. Sorting the Sentence : Easy

A sentence is a list of words that are separated by a single space with no leading or trailing spaces. 
Each word consists of lowercase and uppercase English letters.

A sentence can be shuffled by appending the 1-indexed word position to each word then rearranging the words in the sentence.

For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
Given a shuffled sentence s containing no more than 9 words, reconstruct and return the original sentence.

Examples :-

Input: s = "is2 sentence4 This1 a3"
Output: "This is a sentence"
Explanation: Sort the words in s to their original positions "This1 is2 a3 sentence4", then remove the numbers.

Input: s = "Myself2 Me1 I4 and3"
Output: "Me Myself and I"
Explanation: Sort the words in s to their original positions "Me1 Myself2 and3 I4", then remove the numbers.

Constraints :-
- 2 <= s.length <= 200
- s consists of lowercase and uppercase English letters, spaces, and digits from 1 to 9.
- The number of words in s is between 1 and 9.
- The words in s are separated by a single space.
- s contains no leading or trailing spaces.
*/

#include<bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
string sortSentence1(string s) {
    string words[9];
    
    string word = "";
    for (char& ch : s) {
        if (ch == ' ') word = "";
        else if (ch > '0' && ch <= '9') {
            words[ch - '1'] = word;
        }
        else word += ch;
    }
    
    s = words[0];
    for (int i = 1; i < 9; i++) {
        if (words[i] == "") break;
        s = s + " " + words[i];
    }
    return s;
}

// Using istringstream
string sortSentence2(string s) {
    string words[9];
    istringstream iss(s);
    string word;
    
    while (iss >> word) {
        int pos = word.back()-'1';      
        // word contains 1-indexed position, so it will convert to -'1' for 0 based indexing for array
        word.pop_back();        // Remove the position digit from the word
        words[pos] = word;
    }

    string ans = "";
    for (string& word : words) {
        if (word.empty()) break;
        if (! ans.empty()) ans += " ";
        ans += word;
    }
    return ans;
}

int main() {
    return 0;
}