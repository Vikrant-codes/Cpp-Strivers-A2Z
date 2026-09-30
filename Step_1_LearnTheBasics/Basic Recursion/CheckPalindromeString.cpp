/*
TUF - 278. Check if String is Palindrome or Not

Given a string s, return true if the string is palindrome, otherwise false.
A string is called palindrome if it reads the same forward and backward.

Examples :-

Input : s = "hannah" __ Output : true
Explanation : The string when reversed is --> "hannah", which is same as original string , so we return true.

Input : s = "aabbaA" __ Output : false
Explanation : The string when reversed is --> "Aabbaa", which is not same as original string, So we return false.

Constraints :-
• 1 <= s.length <= 10^3
• s consist of only uppercase and lowercase English characters.
*/

#include <bits/stdc++.h>
using namespace std;

// Palindrome Check Using Recursion : Time Complexity : O(n/2) __ Space Complexity : O(n/2) -- recursive stack space

// helper method
bool fun(string s, int l, int r) {
    // Base Condition
    if (l >= r)
        return true;

    // Palindrome Check
    if (s[l] != s[r]) 
        return false;

    return fun(s, l+1, r-1);
}

// We can also implement this palindrome check helper recursive function using a single pointer variable (by passing only `l`)
bool fun(string s, int l) {
    // Base Condition
    if (l >= s.size()/2)
        return true;

    // Palindrome Check
    if (s[l] != s[s.size() - 1 - l]) 
        return false;

    return fun(s, l+1);
}

// the caller method
bool palindromeCheck(string& s){
    return fun(s, 0, s.length()-1);
    // return fun(s, 0);
}

int main() {
    return 0;
}