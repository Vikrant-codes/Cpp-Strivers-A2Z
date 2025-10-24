/*
Leetcode - 387. First Unique Character in a String : Easy

Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

Examples :

Input: s = "leetcode" __ Output: 0
Explanation: The character 'l' at index 0 is the first character that does not occur at any other index.

Input: s = "loveleetcode" __ Output: 2

Input: s = "aabb" __ Output: -1

Constraints :
1 <= s.length <= 10^5
s consists of only lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Hashmap Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
💡 Intuition
We want the index of the first character that appears exactly once in the string.
So the task naturally breaks into two steps:
1. Count frequencies of all characters.
2. Find the first index where frequency = 1.

Approach :- 
Use a map to keep track of no of occurrences of each character of the string. 
After hashing the character frequencies traverse the string characters and 
return the index of the first character which has frequency of 1.

Complexity Analysis :-
Time Complexity : O(n) :- Two for loops are run n times. First to hash the frequencies then to find the unique character.
Space Complexity : O(1) :- Map used to store frequencies of each character. Characters are lowercase alphabets (a-z) so 
even in the worst case size could be at most 26.
*/
int firstUniqChar(string s) {
    unordered_map<char, int> mpp;
    for (char ch : s)
        mpp[ch]++;
    for (int i=0; i<s.size(); i++)
        if (mpp[s[i]] == 1)
            return i;
    return -1;
}

// Using Frequency Array :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🧠 Approach Types
unordered_map version: More general (works for any character set).
vector<int>(26) version: More efficient (constant-size array, faster lookups).
*/
int firstUniqChar2(string s) {
    vector<int> hash(26);
    for (char ch : s) {
        hash[ch - 'a']++;
    }
    for (int i=0; i<s.size(); i++) {
        if (hash[s[i] - 'a'] == 1)
            return i;
    }
    return -1;
}

int main() {

    return 0;
}