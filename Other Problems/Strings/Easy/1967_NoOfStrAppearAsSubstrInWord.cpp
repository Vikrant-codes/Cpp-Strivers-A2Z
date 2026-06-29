/*
Leetcode - 1967. Number of Strings That Appear as Substrings in Word : Easy

Given an array of strings patterns and a string word, 
return the number of strings in patterns that exist as a substring in word.
A substring is a contiguous sequence of characters within a string.

Examples :-

Input: patterns = ["a","abc","bc","d"], word = "abc" __ Output: 3
Explanation:
- "a" appears as a substring in "abc".
- "abc" appears as a substring in "abc".
- "bc" appears as a substring in "abc".
- "d" does not appear as a substring in "abc".
3 of the strings in patterns appear as a substring in word.

Input: patterns = ["a","b","c"], word = "aaaaabbbbb" __ Output: 2
Explanation:
- "a" appears as a substring in "aaaaabbbbb".
- "b" appears as a substring in "aaaaabbbbb".
- "c" does not appear as a substring in "aaaaabbbbb".
2 of the strings in patterns appear as a substring in word.

Input: patterns = ["a","a","a"], word = "ab" __ Output: 3
Explanation: Each of the patterns appears as a substring in word "ab".

Constraints :-
- 1 <= patterns.length <= 100
- 1 <= patterns[i].length <= 100
- 1 <= word.length <= 100
- patterns[i] and word consist of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(k m n) __ Space Complexity : O(1)

// using the built-in function to check for existence of substring 
/*
'word.contains(sub)'
contains() is essentially implemented as 'word.find(sub) != string::npos'
The complexity of find() is implementation-dependent.
If m = word.length(), n = sub.length()
The C++ Standard : The standard only guarantees at most O(mn) comparisons in the worst case.

So, if patterns array has 'k' patterns (i.e. patterns.size() = k), and averge length of string in pattern is 'n',
then, total time complexity : O(k m n).
*/
int numOfStrings2(vector<string>& patterns, string word) {
    int ans = 0;

    for (string sub : patterns) 
        if (word.contains(sub))
            ans++;

    return ans;
}

/*
>> Complexity Analysis :-

-> substrExists(word, s)
Let: m = word.length(), n = s.length()
The outer loop runs:
    for (int i = 0; i <= m - n; i++)
which is approximately (m − n + 1) times.
For each starting position, the inner while loop may compare up to n characters.

:Worst case

Example:

word = "aaaaaaaaaa"
s    = "aaaaab"

At every position, almost all characters match before failing.

So,

Outer loop → O(m - n + 1)
Inner loop → O(n)

Total:

O((m−n+1)×n)

which is commonly written as

O(mn)
	​


*/

// helper method -> returns true if the string 'word' contains string 's' as substring
bool substrExists(string word, string s) {
    int m = word.length();
    int n = s.length();

    if (m < n) return false;
    
    for (int i = 0; i <= m - n; i++) {
        int j = 0;
    
        while (j < n && word[i+j] == s[j]) 
            j++;
        
        if (j == n) 
            return true;
    }
    return false;
}

int numOfStrings1(vector<string>& patterns, string word) {
    int ans = 0;

    for (string sub : patterns) 
        if (substrExists(word, sub))
            ans++;
    
    return ans;
}



int main() {
    return 0;
}