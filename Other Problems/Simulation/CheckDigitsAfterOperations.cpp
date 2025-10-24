/*
Leetcode - 3461. Check If Digits Are Equal in String After Operations I : Easy

You are given a string s consisting of digits. 
Perform the following operation repeatedly until the string has exactly two digits:
- For each pair of consecutive digits in s, starting from the first digit, 
  calculate a new digit as the sum of the two digits modulo 10.
- Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.

Return true if the final two digits in s are the same; otherwise, return false.

Examples :-

Input: s = "3902" __ Output: true
Explanation:
Initially, s = "3902"
First operation:
(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
s becomes "292"
Second operation:
(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
s becomes "11"
Since the digits in "11" are the same, the output is true.


Input: s = "34789" __ Output: false
Explanation:
Initially, s = "34789".
After the first operation, s = "7157".
After the second operation, s = "862".
After the third operation, s = "48".
Since '4' != '8', the output is false.
 

Constraints :-
3 <= s.length <= 100
s consists of only digits.
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation Approach :- Time Complexity : O(n^2) -- Space Complexity : O(n)
/*
🧠 Intuition
- Take the given string of digits.
- Repeatedly replace it with a new string formed by taking (sum of every two adjacent digits) % 10.
- Continue until the string becomes of size 2.
- Finally, check if both digits are equal.

It’s a direct and intuitive way to “mimic” the operations as the problem states — 
without trying to find any mathematical shortcut.

⚙️ Algorithm
1. Initialize a temporary string temp = "".
2. While the string s has more than 2 digits:
  - For each adjacent pair (s[i], s[i+1]):
    -> Convert both characters to integers.
    -> Compute (n1 + n2) % 10 and convert it back to a character.
    -> Append it to temp.
 - Replace s with temp and reset temp to "".
3. When s.size() == 2, return whether s[0] == s[1].

⏱️ Time Complexity
In the 1st pass: You perform (n − 1) operations.
In the 2nd pass: (n − 2) operations.
… and so on, until 2 digits remain.
Total operations = (n − 1) + (n − 2) + … + 1 ≈ O(n²)

💾 Space Complexity
You create a temporary string each time proportional to the current length of s,
but you reuse the same variable — so O(n) auxiliary space (for storing temp).
*/
bool hasSameDigits(string s) {
    string temp = "";

    while (s.size() != 2) {
        for (int i=0; i<s.size()-1; i++) {
            int n1 = s[i] - '0';
            int n2 = s[i+1] - '0';
            int num = (n1 + n2) % 10;
            char ch = num + '0';
            temp += ch;
        }
        s = temp;
        temp = "";
    }

    return s[0] == s[1];
}

int main() {

    return 0;
}