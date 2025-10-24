/*
Leetcode - 500. Keyboard Row : Easy

Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of 
American keyboard like the image below.
Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are 
at the same row.

In the American keyboard:
- the first row consists of the characters "qwertyuiop",
- the second row consists of the characters "asdfghjkl", and
- the third row consists of the characters "zxcvbnm".

Examples :-

Input: words = ["Hello","Alaska","Dad","Peace"] __ Output: ["Alaska","Dad"]

Input: words = ["omk"] __ Output: []

Input: words = ["adsdf","sfd"] __ Output: ["adsdf","sfd"]

Constraints :-
1 <= words.length <= 20
1 <= words[i].length <= 100
words[i] consists of English letters (both lowercase and uppercase). 
*/

#include<bits/stdc++.h>
using namespace std;

// Hashing Approach : Time Complexity : O(N) where N is the total character length of the whole string vector __ Space : O(1)
/*
🧠 Intuition
Each letter on a keyboard belongs to one of three rows.
A word can be typed using letters from a single row if all its characters belong to that same row.
So, the idea is simple:
- Define which letters belong to each row.
- For every word, count how many of its letters belong to row 1, row 2, and row 3.
- If all letters fall into the same row (i.e., the count of one row equals the word length), that word qualifies.

⏱ Complexity

Time: O(N × L)
where N = number of words, L = average word length.
Each character is checked in constant time (O(1) lookup in unordered_set).

Space: O(1) — the sets have fixed size (26 total letters), independent of input.
*/
vector<string> findWords(vector<string>& words) {
    vector<string> ans;

    unordered_set<char> r1 = {'q','w','e','r','t','y','u','i','o','p'};
    unordered_set<char> r2 = {'a','s','d','f','g','h','j','k','l'};
    unordered_set<char> r3 = {'z','x','c','v','b','n','m'};

    for (string word : words) {
        int n = word.length();     // no of characters in the current word
        // counters to keep count of how many characters of current word appear in each row
        int cntR1 = 0, cntR2 = 0, cntR3 = 0;

        for (char ch : word) {
            ch = tolower(ch);       // to convert uppercase to lowercase
            // check the character character belongs to which row. Increment that corresponding row counter
            if (r1.count(ch)) cntR1++;
            else if (r2.count(ch)) cntR2++;
            else cntR3++;
        }
        // if all the characters of current word belong to a particular row, add that word to ans vector
        if (cntR1 == n || cntR2 == n || cntR3 == n) ans.push_back(word);
    }

    return ans;
}

int main() {
    return 0;
}