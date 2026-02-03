/*
Leetcode - 345. Reverse Vowels of a String : Easy

Given a string s, reverse only all the vowels in the string and return it.
The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Examples :-

Input: s = "IceCreAm" __ Output: "AceCreIm"
Explanation:
The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Input: s = "leetcode" __ Output: "leotcede"

Constraints :-
1 <= s.length <= 3 * 10^5
s consist of printable ASCII characters.
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointer Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :-
1. Initialize two pointers i & j : i  = 0, j = s.length()-1.
2. While i < j (i.e. the pointers don't cross each other) 
-- If both pointers point to vowel then swap the vowels. Increment i & decrement j (do i++; j--;)
-- Else if s[i] is not a vowel then inrement i to find a vowel
-- Else (s[j] is not a vowel) decrement j to find the vowel
*/

bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

string reverseVowels(string s) {
    int i = 0, j = s.length()-1;
    while (i < j) {
        if (isVowel(s[i]) && isVowel(s[j]) ) {
            swap(s[i], s[j]);
            i++; j--;
        }
        else if (!isVowel(s[i])) i++;
        else j--;
    }
    return s;
}

int main() {

    return 0;
}