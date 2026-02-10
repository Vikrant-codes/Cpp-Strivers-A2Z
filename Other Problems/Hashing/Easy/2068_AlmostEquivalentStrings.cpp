/*
Leetcode - 2068. Check Whether Two Strings are Almost Equivalent : Easy

Two strings word1 and word2 are considered almost equivalent if the differences between the frequencies of each letter 
from 'a' to 'z' between word1 and word2 is at most 3.
Given two strings word1 and word2, each of length n, return true if word1 and word2 are almost equivalent, or false otherwise.
The frequency of a letter x is the number of times it occurs in the string.

Examples :-

Input: word1 = "aaaa", word2 = "bccb"
Output: false
Explanation: There are 4 'a's in "aaaa" but 0 'a's in "bccb".
The difference is 4, which is more than the allowed 3.

Input: word1 = "abcdeef", word2 = "abaaacc"
Output: true
Explanation: The differences between the frequencies of each letter in word1 and word2 are at most 3:
- 'a' appears 1 time in word1 and 4 times in word2. The difference is 3.
- 'b' appears 1 time in word1 and 1 time in word2. The difference is 0.
- 'c' appears 1 time in word1 and 2 times in word2. The difference is 1.
- 'd' appears 1 time in word1 and 0 times in word2. The difference is 1.
- 'e' appears 2 times in word1 and 0 times in word2. The difference is 2.
- 'f' appears 1 time in word1 and 0 times in word2. The difference is 1.

Input: word1 = "cccddabba", word2 = "babababab"
Output: true
Explanation: The differences between the frequencies of each letter in word1 and word2 are at most 3:
- 'a' appears 2 times in word1 and 4 times in word2. The difference is 2.
- 'b' appears 2 times in word1 and 5 times in word2. The difference is 3.
- 'c' appears 3 times in word1 and 0 times in word2. The difference is 3.
- 'd' appears 2 times in word1 and 0 times in word2. The difference is 2.

Constraints :-
- n == word1.length == word2.length
- 1 <= n <= 100
- word1 and word2 consist only of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n + 26) __ Space Complexity : O(26) ~ O(1)
/*
Use 2 frequency arrays to count how many times each letter appears in word1 & word2. 
For every letter from 'a' to 'z', check how different the counts are.
If the difference of number of occurrences for any letter is more than 3 → not almost equivalent.
*/
bool checkAlmostEquivalent1(string word1, string word2) {
    vector<int> freq1(26, 0), freq2(26, 0);
        
    for (char& c : word1) freq1[c - 'a']++;
    for (char& c : word2) freq2[c - 'a']++;

    for (int i = 0; i < 26; i++) {
        if (abs(freq1[i] - freq2[i]) > 3)
            return false;
    }
    return true;
}

/*
Instead of using two different frequency arrays, 
we can use a single array to store the difference of no. of occurrences of a letter (a to z) in both strings.
For characters in word1, we increase the frequency and for word2 we decrease it.
At the end, the array already stores the difference between frequencies.
The two strings will be almost equivalent 
if this difference between the letter counts is in range [-3, 3] (or, absolute value less than 3).
*/
bool checkAlmostEquivalent2(string word1, string word2) {
    vector<int> freq(26, 0);
    for (int i = 0; i < word1.size(); i++) {
        freq[word1[i] - 'a']++;
        freq[word2[i] - 'a']--;
    }

    for (int& x : freq) {
        if (x < -3 || x > 3)        // same as abs(x) > 3
            return false;
    }
    return true;
}

int main() {
    return 0;
}