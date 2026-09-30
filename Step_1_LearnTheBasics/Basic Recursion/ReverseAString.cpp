/*
TUF - 294. Reverse a String I

Given an input string as an array of characters, write a function that reverses the string.

Examples :-

Input : s = ["h", "e", "l", "l", "o"]
Output : ["o", "l", "l", "e", "h"]
Explanation : The given string is s = "hello" and after reversing it becomes s = "olleh".

Input : s = ["b", "y", "e" ]
Output : ["e", "y", "b"]
Explanation : The given string is s = "bye" and after reversing it becomes s = "eyb".

Constraints :-
• 1 <= s.length <= 10^3
• s consist of only lowercase and uppercase English characters.
*/

#include <bits/stdc++.h>
using namespace std;

void reverseFun(vector<char>& s, int i, int j) {
    if (i >= j) {
        return;
    }

    swap(s[i], s[j]);
    reverseFun(s, i + 1, j - 1);
}

vector<char> reverseString(vector<char>& s){
    reverseFun(s, 0, s.size()-1);
    
    return s;
}

int main() {
    return 0;
}