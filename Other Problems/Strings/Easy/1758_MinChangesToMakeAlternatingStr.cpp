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

// Approach 1 : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
>> Key Observation
An alternating binary string can only have two possible patterns:
• Start with '0' → "010101..."
• Start with '1' → "101010..."
There are no other valid alternating patterns.

So the idea is simple:
• Calculate how many changes are needed to convert the string into pattern 1
• Calculate how many changes are needed to convert the string into pattern 2
• Take the minimum.

>> Core Idea
Assume we want the string to follow "010101...".
We iterate through the string and keep track of the expected bit at each position.
Example => s = "0100", Expected pattern: "0101"
| Index | Actual | Expected | Change? |
| ----- | ------ | -------- | ------- |
| 0     | 0      | 0        | No      |
| 1     | 1      | 1        | No      |
| 2     | 0      | 0        | No      |
| 3     | 0      | 1        | Yes     |
Operations Required to change to expected pattern = 1

>> cntAlternatingOperations(string& s, char bit)
We use a helper function which counts how many operations are required to convert the given string into expected pattern.
The function cntAlternatingOperations(string& s, char bit) takes the string and an expected starting bit
For "0101..." pattern, the expected starting bit is '0' & for "1010..." it is '1'.
For each character in the string, we check if there is a mismatch and if yes, we increment the count of operations.
Flip the expected bit (0 ↔ 1) for the next position.
*/

// takes a string and the expected starting bit ('0' for '0101..' pattern & '1' for '1010..' pattern),
// returns the count of operations required to make the string in that particular pattern
int cntAlternatingOperations(string& s, char bit) {
    int cnt = 0;          // count operations required to convert the string to specified pattern
    for (char& c : s) {
        if (c != bit)    // if character is not equal to pattern bit, increment count
            cnt++;

        bit = (bit == '0') ? '1' : '0';         // invert the bit to get the next alternating bit
    }

    return cnt;
}

int minOperations1(string s) {
    // the alternating binary string would be either of the form "010101..." or "101010...".
    int cnt1 = cntAlternatingOperations(s, '0');        // count operations required to convert to "0101..." pattern
    int cnt2 = cntAlternatingOperations(s, '1');        // count operations required to convert to "1010..." pattern
    
    return min(cnt1, cnt2);
}

// Approach 2 : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Instead of checking both patterns separately, we can count both pattern mismatches in a single pass.

Since both patterns are complement/inverse of each other "0101..." -> "1010..."
So, if the current bit of the string matches the expected bit of one pattern, 
it must mismatch the other pattern's expected bit.

>> Key Insight
At any position i:
If the string matches one of the two patterns → it must mismatch the other pattern.
Because the other pattern is simply the inverse.

Ex -> s = "0100", Expected pattern1 = "0101", pattern2 = "1010"
| i | c | expected bit pattern-1 | mismatch cnt-1 | expected bit pattern-2 | mismatch cnt-2 |
| - | - | -------------          | -------------- | -------------          | -------------- |
| 0 | 0 | 0                      | 0              | 1                      | 1              |
| 1 | 1 | 1                      | 0              | 0                      | 2              |
| 2 | 0 | 0                      | 0              | 1                      | 3              |
| 3 | 0 | 1                      | 1              | 0                      | 3              |

for each bit, we can see that if it matches the expected bit of pattern-1, then, it mismatches the expected bit of pattern-2.

So, we use two count variables to count the mismatches according to both patterns.
We use a bit variable which stores bit according to one of the pattern.
Now, if current bit mismatches, we increment cnt1 .... else we increment cnt2 (since current bit mismatches pattern2)
Return the minimum of both count.

>> Why cnt2++ happens when c == bit
Because if a character matches "0101...", it must be wrong for "1010...".
So we don't need to explicitly track the second pattern.

Why this works ?
At each index:
    match with pattern1  ⇔ mismatch with pattern2
    mismatch with pattern1 ⇔ match with pattern2
So a single comparison gives information about both patterns.

>> One-line intuition
    Each position either agrees with "0101..." or "1010...", never both — so one comparison updates both mismatch counts.
*/
int minOperations2(string s) {
    int cnt1 = 0, cnt2 = 0;
    char bit = '0';

    for (char& c : s) {
        if (c != bit) cnt1++;
        else cnt2++;

        bit = (bit == '0') ? '1' : '0';
    } 
    
    return min(cnt1, cnt2);
}

// Approach 3 : Time Complexity : O(n) __ Space Complexity : O(1)
/*
cnt counts mismatches with the pattern "010101...".
Let the string length be n.
At every index exactly one of these is true:
- The character matches "0101..."
- The character does not match "0101..."
So: matches + mismatches = n
Since cnt stores mismatches with "0101...", the number of matches is: matches = n - cnt

Now notice something important:
If a character matches "0101...", it must mismatch "1010...", because the two patterns are exact opposites.
So, match in pattern 1 = mismatch in pattern 2
Therefore: mismatches with "1010..." = matches with "0101..."
So: cnt2 = n - cnt

>> Short intuition
Because the two alternating patterns are exact complements, every match in one pattern is a mismatch in the other, 
so: mismatch_pattern2 = n - mismatch_pattern1
*/
int minOperations(string s) {
    int cnt = 0;
    char bit = '0';

    for (char& c : s) {
        if (c != bit) cnt++;

        bit = (bit == '0') ? '1' : '0';
    }

    int cnt2 = s.size() - cnt;

    return min(cnt, cnt2);
}

int main() {
    return 0;
}