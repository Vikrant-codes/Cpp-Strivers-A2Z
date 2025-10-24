/*
Leetcode - 242. Valid Anagram : Easy

Given two strings s and t, return true if t is an anagram of s, and false otherwise.
Anagram : An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
using all the original letters exactly once. Ex- 'throw' & 'worth', 'race' & 'care', 'thing', 'night'.

Examples :-

Input: s = "anagram", t = "nagaram" __ Output: true
Input: s = "rat", t = "car" __ Output: false

Constraints :-
1 <= s.length, t.length <= 5 * 10^4
s and t consist of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Sorting Approach :- Time Complexity : O(nlogn) __ Space Complexity : O(1)
/*
Approach :- 
Two strings are anagrams of each other if they are made of same characters just shuffled. So if we sort both the strings 
then the strings would be anagrams of each other iff the sorted strings are equal.  
So, to check for anagrams we sort both the strings and check whether the sorted strings are equal or not.

Complexity Analysis :-
Time Complexity :- O(n log n) to sort both the strings
*/
bool isAnagramSort(string s, string t) {
    if (s.size() != t.size()) return false;
    sort(s.begin(), s.end());       // sort string s
    sort(t.begin(), t.end());       // sort string t
    return s == t;
}

// Optimal Approach (Hashing) :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition :
Two strings are said to be anagram of each other if they have the same characters appearing same no of times. 
Or if one can be formed by rearranging the letters of the other. 
So we can use hashing to keep count of the frequencies of lowercase characters in the string. 

There can be two approaches to this :- 
1. We take two freq arrays - one for string s, and second for string t. We can update the corresponding frequency arrays of 
both strings and then check whether the two frequency arrays are same or not. 
It's like counting frequency of occuring characters in each string and then check whether the frequencies are same or not.

2. Instead of using two different arrays of character hashing we can use a single array and we will update frequency as follows:
- for characters of string s, we will increment the frequency count
- for characters of string t, we will increment the frequency count
At the end we check if all the frequencies are 0 or not since if both strings are anagrams they must contain same frequencies of 
characters and thus incrementing & decrementing frequencies of corresponding chars should keep the net vector as zero.

Complexity Analaysis :-
> Time Complexity : O(n) 
- O(n) to traverse the characters of each string once to update the frequency array.
- O(26) to traverse the freq array to check for non-zero freq in case of non-anagrams. 
- So, total complexity is O(n + 26) ~ O(n).
> Space Complexity : O(1) since the hasing vector used is of fixed size 26.
*/
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;

    vector<int> freq(26);

    for (int i=0; i<s.size(); i++) {
        int x = s[i] - 'a';         // corresponding string s character index
        int y = t[i] - 'a';         // corresponding string t character index
        freq[x]++; freq[y]--;
    }

    for (int x : freq) 
        if (x != 0) 
            return false;
    return true;
}

int main() {

    return 0;
}