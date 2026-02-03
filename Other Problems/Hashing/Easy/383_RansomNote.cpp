/*
Leetcode - 383. Ransom Note : Easy

Given two strings ransomNote and magazine, 
return true if ransomNote can be constructed by using the letters from magazine and false otherwise.

Each letter in magazine can only be used once in ransomNote.

Examples :-
Input: ransomNote = "a", magazine = "b" __ Output: false
Input: ransomNote = "aa", magazine = "ab" __ Output: false
Input: ransomNote = "aa", magazine = "aab" __ Output: true

Constraints :-
• 1 <= ransomNote.length, magazine.length <= 10^5
• ransomNote and magazine consist of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// HashArray Approach : Time Complexity : O(m+n) where m = magazine.size(), n = ransomNote.size() __ Space Complexity : O(1)
/*
Intuition 
We need to check whether the 'ransomNote' string can be constructed from letters of 'magazine' string where each letter can 
be used only once.

Both strings consists of only lowercase English letters.

'ransomNote' can only be constructed from 'magazine' if for each letter i (from a-z) appearing 'k' no. of times in 'ransomNote'
then it must appear >= k times in 'magazine'. 
So, we need to find frequency of occurrences of letters in each string and for each letter, the frequency in magazine must be 
greater than / equal to frequency in ransomNote.

Thus, we can use 2 hashArrays of size 26 - one for ransomNote & other for magazine and
for each letter, we must check if frequency in magazine >= frequency in ransomNote. 
If for any letter this condition is false then we return false

A little improvisation of this approach would be to use a single frequency hashArray.
Initially all frequencies (of each letter a-z) are 0. We will traverse 'magazine' array and increment the frequencies.
After that, we will then traverse 'ransomNote' and decrement the frequency.
Doing this will affect the frequency in either of the 3 ways.
-> If freq in magazine > freq in ransomNote :- the final frequency will remain +ve.
-> If freq in magazine = freq in ransomNote :- the final frequency will become 0.
-> If freq in magazine < freq in ransomNote :- the final frequency will become -ve.
So after incrementing & decrementing, we traverse the hashArray and if a -ve frequency is found, we return false.
*/
bool canConstruct1(string ransomNote, string magazine) {
    int arr1[26], arr2[26];
    for (char& c : magazine) {
        arr1[c-'a']++;
    }
    for (char& c : ransomNote) {
        arr2[c-'a']++;
    }

    for (int i = 0; i < 26; i++) 
        if (arr1[i] < arr2[i])
            return false;
    return true;
}

bool canConstruct2(string ransomNote, string magazine) {
    int hashArr[26];
    for (char& c : magazine) {
        hashArr[c-'a']++;
    }
    for (char& c : ransomNote) {
        hashArr[c-'a']--;
    }

    for (int& x : hashArr) if (x < 0) return false;
    return true;
}

int main() {
    return 0;
}