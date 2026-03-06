/*
Leetcode - 1784. Check if Binary String Has at Most One Segment of Ones : Easy

Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. 
Otherwise, return false.

Examples :-

Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.

Input: s = "110"
Output: true

Constraints :-
- 1 <= s.length <= 100
- s[i]​​​​ is either '0' or '1'.
- s[0] is '1'.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:-
The problem want to check if the given string has at most one contiguous segment of 1s.
That is, if a segment of 1s is present in the string at some index range, no other segment of 1s must exist anywhere else.
Ex- valid cases : "111000", "100", "00"
invalid cases : "110111", "10101", "10001"

In valid cases, we can only have at most 1 segment of 1s (or no segment at all), i.e. 
all the 1s of the string must appear together.
*/

bool checkOnesSegment(string s) {
    // all the 1s of the string must form a continuous segment
    // so the string must have only 1 continuous segment of 1s
    int n = s.size();

    int i = 0;              // traversal pointer 
    
    // find the first occurrence index of '1'
    while (i < n && s[i] != '1') i++;
    // now 1 is at the first '1' character
    
    // move ahead this continuous segment of 1s and check if any other segment of 1 is present apart from this segment
    while (i < n && s[i] == '1') i++;           // skip this segment of 1s

    // now check for remaining string portion and it shouldn't have any segment of 1s for true condition
    while (i < n) {
        if (s[i] == '1')            // a new segment of 1s found
            return false;
        i++;
    }
    
    return true;
}

int main() {
    return 0;
}