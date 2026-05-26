/*
Leetcode - 3120. Count the Number of Special Characters I : Easy

You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
Return the number of special letters in word.

Examples :-

Input: word = "aaAbcBC" __ Output: 3
Explanation: The special characters in word are 'a', 'b', and 'c'.

Input: word = "abc" __ Output: 0
Explanation: No character in word appears in uppercase.

Input: word = "abBCab" __ Output: 1
Explanation: The only special character in word is 'b'.

Constraints :-
- 1 <= word.length <= 50
- word consists of only lowercase and uppercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(26 * n) __ Space Complexity : O(1)
/*
For all alphabets (A to Z), check whether both uppercase & lowercase of the alphabet exist in the string.
Count such alphabets.
Return count
*/
bool isPresent(string word, char x) {
    for (char ch : word) 
        if (ch == x)
            return true;

    return false;
}

int numberOfSpecialCharsNaive(string word) {
    int cnt = 0;

    for (int i = 0; i < 26; i++)
        if (isPresent(word, 'a' + i) && isPresent(word, 'A' + i))
            cnt++;

    return cnt;
}

// Optimal Approach :- Time Commplexity : O(n + 26) __ Space Complexity : O(26 + 26) = O(52) ~ O(1)
/*
Use two hash arrays to store the frequency (or existence) of the characters present in the array.
One hash array for lowercase chars, another one for uppercase chars.
For chars A to Z (26 alphabets), check if both lowercase & uppercase of that alphabets exists in the string using hashArray.
Count such chars
Return count
*/
int numberOfSpecialChars1(string word) {
    vector<int> lowerChars(26);
    vector<int> upperChars(26);

    for (char& ch : word) {
        if (ch >= 'a' && ch <= 'z') 
            lowerChars[ch-'a']++;
        else
            upperChars[ch-'A']++;
    }

    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (lowerChars[i] && upperChars[i])
            cnt++;
    
    return cnt;
}

// we can also use two boolean vector to check existence of the lowercase & uppercase chars, no need to store frequencies
int numberOfSpecialChars2(string word) {
    vector<bool> lowerCase(26);
    vector<bool> upperCase(26);

    for (char& ch : word) {
        if (ch >= 'a' && ch <= 'z')
            lowerCase[ch - 'a'] = true;
        else
            upperCase[ch - 'A'] = true;
    }
    
    int cnt = 0;
    for (int i = 0; i < 26; i++) 
        if (lowerCase[i] && upperCase[i])
            cnt++;
    
    return cnt;
}

int main() {
    return 0;
}