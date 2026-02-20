/*
Leetcode - 1704. Determine if String Halves Are Alike : Easy

You are given a string s of even length. Split this string into two halves of equal lengths, 
and let a be the first half and b be the second half.

Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). 
Notice that s contains uppercase and lowercase letters.

Return true if a and b are alike. Otherwise, return false.

Examples :-

Input: s = "book"
Output: true
Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.

Input: s = "textbook"
Output: false
Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
Notice that the vowel o is counted twice.

Constraints :-
- 2 <= s.length <= 1000
- s.length is even.
- s consists of uppercase and lowercase letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)

bool isVowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u'); 
}

bool halvesAreAlike(string s) {
    int len = s.size();
    int half = len / 2;
    int cnt1 = 0, cnt2 = 0;

    for (int i = 0; i < half; i++) {
        if ( isVowel(s[i]) ) cnt1++;
        if ( isVowel(s[i+half]) ) cnt2++;
    }

    return cnt1 == cnt2;
}

// We can also use a single counter, increment it for vowels of half1 and decrement for half2. 
// Check if value remains zero after loop ends.
bool halvesAreAlike2(string s) {
    int len = s.size();
    int half = len / 2;
    int cnt = 0;

    for (int i = 0; i < half; i++) {
        if ( isVowel(s[i]) ) cnt++;
        if ( isVowel(s[i+half]) ) cnt--;
    }

    return cnt == 0;
}

int main() {
    return 0;
}