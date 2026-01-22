/*
Leetcode - 1624. Largest Substring Between Two Equal Characters : Easy

Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. 
If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

Examples :-

Input: s = "aa" __ Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.

Input: s = "abca" __ Output: 2
Explanation: The optimal substring here is "bc".

Input: s = "cbzxy" __ Output: -1
Explanation: There are no characters that appear twice in s.

Constraints :-
- 1 <= s.length <= 300
- s contains only lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Hashing Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :-
We want to find the length of the largest substring which exists between two equal characters (excluding the two characters).
To get the largest substring we need to check only the first and last occurring indices of repeating charaters.
Ex- assume string is : "xabcxdexf", 
here 'x' repeats three times at indices 0, 4 and 7. 
the substrings b/w equal characters are "abc" (b/w 0 & 4th x), "de" (b/w 4th & 7th x) and "abcxde" (b/w 0th & 7th x).
For the same character 'x' appearing multiple times, the longest substring is b/w its first & last occurrence.
So, we need to store the first occuring indices of characters and also need the last occurring indices to get the answer.

The characters are lowercase only (26 in size), so we use a 26-sized array to store the first occurring indices of each chars.
Initially, it consists of only -1 (-1 shows that a particular characters is not seen in the string till now)
So, we traverse the array and if a characters appears for the first time (i.e. if it's corresponding value is -1), 
we store the current occurrence index as this is the index of first occurrence of the character.
Else if, a character has been seen already before (means this character is repeating), there must exist a substring b/w its 
first occurrence index and current index. We can find the length of this substring easily.
Assume, the current index is 'i' and first occurrence index of char x is hashArr[x],
then length of substring between the two occurrences (excluding the two characters) = i - hashArr[x] - 1.
We can find the length of all such substring in this way and store the maximum length.
*/
int maxLengthBetweenEqualCharacters(string s) {
    int ans = -1;
    vector<int> ind(26, -1);            // array containing first occurrence indices of chars
    for (int i = 0; i < s.size(); i++) {
        int c_ind = s[i] - 'a';         // corresponding character index in array
        // if char has not appeared before, then update its first occurrence index in the hash array
        if (ind[c_ind] == -1) 
            ind[c_ind] = i;
        // else, if char has appeared before, find the length of substring existing b/w the characters and update ans (if needed)
        else 
            ans = max(ans, i - ind[c_ind] - 1);
    }
    return ans;
}

int main() {
    return 0;
}