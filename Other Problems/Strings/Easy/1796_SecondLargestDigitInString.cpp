/*
Leetcode - 1796. Second Largest Digit in a String

Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
An alphanumeric string is a string consisting of lowercase English letters and digits.

Examples :-

Input: s = "dfa12321afd" __ Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.

Input: s = "abc1111" __ Output: -1
Explanation: The digits that appear in s are [1]. There is no second largest digit. 
 
Constraints :-
1 <= s.length <= 500
s consists of only lowercase English letters and digits.
*/

#include<bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
int secondHighest(string s) {
    int fr = -1, sc = -1;     // fr : first maximum, sc : second maximum
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            int dig = c - '0';
            if (dig > fr) {
                sc = fr;
                fr = dig;
            }
            else if (dig != fr && dig > sc)
                sc = dig;
        }
    }
    return sc;
}

int main() {
    return 0;
}