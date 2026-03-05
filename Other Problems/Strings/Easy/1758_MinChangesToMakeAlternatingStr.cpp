/*
Leetcode - 1758. Minimum Changes To Make Alternating Binary String : Easy

You are given a string s consisting only of the characters '0' and '1'. 
In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. 
For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Examples :-

Input: s = "0100" __ Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.

Input: s = "10" __ Output: 0
Explanation: s is already alternating.

Input: s = "1111" __ Output: 2
Explanation: You need two operations to reach "0101" or "1010".

Constraints :-
- 1 <= s.length <= 10^4
- s[i] is either '0' or '1'.
*/

#include <bits/stdc++.h>
using namespace std;

// takes a string and the expected starting bit '0' for '0101..' pattern & '1' for '1010..' pattern
int cntAlternatingOperations(string& s, char bit) {
    int cnt = 0;          // count operations required to convert the string to specified pattern
    for (char& c : s) {
        if (c != bit)    // if character is not equal to pattern bit, increment count
            cnt++;

        bit = (bit == '0') ? '1' : '0';         // invert the bit to get the next alternating bit
    }

    return cnt;
}

int minOperations(string s) {
    // the alternating binary string would be either of the form "010101..." or "101010...".
    int cnt1 = cntAlternatingOperations(s, '0');
    int cnt2 = cntAlternatingOperations(s, '1');
    
    return min(cnt1, cnt2);
}

int main() {
    return 0;
}