/*
Leetcode - 1221. Split a String in Balanced Strings : Easy

Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
Given a balanced string s, split it into some number of substrings such that:
- Each substring is balanced.
Return the maximum number of balanced strings you can obtain.

Examples :-

Input: s = "RLRRLLRLRL" __ Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.

Input: s = "RLRRRLLRLL" __ Output: 2
Explanation: s can be split into "RL", "RRRLLRLL", each substring contains same number of 'L' and 'R'.
Note that s cannot be split into "RL", "RR", "RL", "LR", "LL", because the 2nd and 5th substrings are not balanced.

Input: s = "LLLLRRRR" __ Output: 1
Explanation: s can be split into "LLLLRRRR".

Constraints :-
- 2 <= s.length <= 1000
- s[i] is either 'L' or 'R'.
- s is a balanced string.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space : O(1)
/*
🧠 Problem Intuition
You are given a string consisting only of 'L' and 'R'. 
A balanced string is defined as a substring that contains equal numbers of 'L' and 'R'.
Goal: Count how many balanced substrings you can split the string into.
Key Idea: Whenever the number of 'L' equals the number of 'R' in a substring, that substring is balanced.

⚙️ Algorithm / Logic

1. Use a counter to track the balance:
- Increment cnt for 'L'
- Decrement cnt for 'R'
(or vice versa — it doesn’t matter, as long as you’re consistent)

2. Iterate through the string character by character:
- if character == 'L' : increment cnt
- else (character == 'R') : decrement cnt
- if cnt == 0 → balanced substring found :- if (cnt == 0) ans++;

3. Explanation of why this works:
- Every 'L' increases the balance, every 'R' decreases it.
- When cnt reaches 0, the number of 'L' and 'R' seen so far is equal.
- That’s exactly a balanced substring, so increment your answer.

4. Return the count of balanced substrings.
*/
int balancedStringSplit(string s) {
    short ans = 0;
    short cnt = 0;            // count of L to check for balanced substring part
    for (char c : s) {
        if (c == 'L') cnt++;
        else cnt--;
        // if cnt == 0 → balanced substring found
        if (cnt == 0) ans++;
    }
    return ans;
}

int main() {
    return 0;
}