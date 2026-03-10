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
Ex- valid cases : "111000", "100"
invalid cases : "110111", "10101", "10001"

In valid cases, we can only have at most 1 segment of 1s, i.e. all the 1s of the string must appear together.
*/

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition :-
- The string must contain at most 1 segment of 1s.
- So, we traverse the string and skip the first segment of 1s.
- Now, after that we traverse the remaining portion of the string and no '1' should appear in this remaining part for 
  the condition "at most one contiguous segment of ones" to be true.
- If '1' appears in this remaining part, it means there is more than one segment of ones. So, return false
- If loop ends normally, return true.

Code Intuition:-
- Because the string doesn't have leading zeros, if a segment of 1s exists it must start at index 0.
- Skip the first contiguous segment of 1s. Make the pointer point to the position after the end of the first segment of 1s.
- Now, from this position, again traverse the string and if any '1' is found, return false.
*/
bool checkOnesSegment(string s) {
    int n = s.size();

    int i = 0;
    // the problem states that s doesn't have leading zeros
    // so the first segment of 1s (if exist) must start from index 0 
    // traverse the first segment of 1s and skip this, place the pointer after the end of 1st segment of 1s
    while (i < n && s[i] == '1') i++;

    // now traverse till string end & no other 1 must apper for the "at most 1 segment of 1s" condition
    for (i; i < n; i++) 
        if (s[i] == '1')
            return false;

    return true;
}

int main() {
    return 0;
}