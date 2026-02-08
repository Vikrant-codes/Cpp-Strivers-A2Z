/*
Leetcode - 1576. Replace All ?'s to Avoid Consecutive Repeating Characters : Easy

Given a string s containing only lowercase English letters and the '?' character, convert all the '?' characters 
into lowercase letters such that the final string does not contain any consecutive repeating characters. 
You cannot modify the non '?' characters.
It is guaranteed that there are no consecutive repeating characters in the given string except for '?'.
Return the final string after all the conversions (possibly zero) have been made. 
If there is more than one solution, return any of them. 
It can be shown that an answer is always possible with the given constraints. 

Examples :-

Input: s = "?zs"
Output: "azs"
Explanation: There are 25 solutions for this problem. From "azs" to "yzs", all are valid. 
Only "z" is an invalid modification as the string will consist of consecutive repeating characters in "zzs".

Input: s = "ubv?w"
Output: "ubvaw"
Explanation: There are 24 solutions for this problem. Only "v" and "w" are invalid modifications 
as the strings will consist of consecutive repeating characters in "ubvvw" and "ubvww".

Constraints :-
- 1 <= s.length <= 100
- s consist of lowercase English letters and '?'.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
We need to replace '?' chars with lowercase english alphabets such that 
the final string won't have any consecutive repeating characters.
For any '?' there are only two consecutive characters and we must assign an alphabet to this '?' such that 
the assigned value is not equal to left or right character to the current character.
Thus, we can always choose the replaced value from a fixed set of 3 consecutive alphabets like {a, b, c} or {p, q, r} etc.
Because for any set of 3 consecutive alphabets, the '?' should be able to be replaced by at-least one of the value. 
*/
string modifyString(string s) {
    int n = s.size();
    for(int i = 0; i < n; i++) {
        if (s[i] == '?') {
            char left = (i-1 >= 0) ? s[i-1] : ' ';
            char right = (i+1 < n) ? s[i+1] : ' ';
            char x = 'a';
            while (left == x || right == x)
                x++;
            s[i] = x;
        }
    }
    return s;
}

string modifyString2(string s) {
    int n = s.size();
    for(int i = 0; i < n; i++) {
        if (s[i] == '?') {
            char left = (i-1 >= 0) ? s[i-1] : ' ';
            char right = (i+1 < n) ? s[i+1] : ' ';
            for (char c = 'a'; c <= 'c'; c++) {
                if (c != left && c != right) {
                    s[i] = c;
                    break;
                }
            }
        }
    }
    return s;
}

int main() {
    return 0;
}