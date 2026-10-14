/*
GFG - Roll Characters of String : Medium

Given a string s consisting of lowercase English letters and an integer array roll[], 
perform a sequence of roll operations on the string.

For each value roll[i], increment each of the first roll[i] characters of the string by 1 in the English alphabet. 
After 'z', the character wraps around to 'a'.

Return the final string after applying all roll operations.

Note: A roll operation affects the current state of the string, including all previous modifications.

Examples :-

Input: s = "bca", roll[] = [1, 2, 3]
Output: eeb
Explanation: Initially, s = "bca" 
roll[0] = 1: Roll the first 1 character. "bca" -> "cca" 
roll[1] = 2: Roll the first 2 characters. "cca"-> "dda" 
roll[2] = 3: Roll the first 3 characters. "dda" -> "eeb" 
After applying all the roll operations, the final string is "eeb".

Input: s = "zcza", roll[] = [1, 1, 3, 4]
Output: debb
Explanation: Initially, s = "zcza". 
Roll first 1 character: "zcza" -> "acza" 
Roll first 1 character again: "acza" -> "bcza" 
Roll first 3 characters: "bcza" -> "cdaa" 
Roll first 4 characters: "cdaa" -> "debb" 
Therefore, the final string is "debb".

Constraints :-
• 1 ≤ s.size(), roll.size() ≤ 10^5
• 1 ≤ roll[i] ≤ s.size()
• s consists only of lowercase English alphabets
*/

#include <bits/stdc++.h>
using namespace std;

char getNextChar(char ch, int steps) {
    steps = steps % 26;
    
    int nextChar = ch + steps;
    
    if (nextChar > 'z') {
        nextChar = 'a' + nextChar - 'z' - 1;
    }
    
    return (char) nextChar;
}

// this below logic is not working for cases like ch = 'v' and steps = 10, (due to signed char in C++)
/*
char getNextChar(char ch, int steps) {
    steps = steps % 26;
    
    char nextChar = (char) (ch + steps);
    
    if (nextChar > 'z') {
        nextChar = (char) ('a' + nextChar - 'z' - 1);
    }
    
    return nextChar;
}
*/

char getNextChar2(char ch, int steps) {
    steps = steps % 26;
    
    return (char) ('a' + (ch - 'a' + steps) % 26);
}

string findRollOut(string& s, vector<int>& roll) {
    int n = s.length();
    
    vector<int> updates(n, 0);
    
    for (int x: roll) updates[x-1]++;
    
    int sum = 0;
    string ans(n, ' ');
    
    for (int i = n - 1; i >= 0; i--) {
        sum += updates[i];
        
        ans[i] = getNextChar(s[i], sum);
    }
    
    return ans;
}

int main() {
    return 0;
}