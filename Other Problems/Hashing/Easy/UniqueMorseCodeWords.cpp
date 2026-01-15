/*
Leetcode - 804. Unique Morse Code Words : Easy

International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:
'a' maps to ".-",
'b' maps to "-...",
'c' maps to "-.-.", and so on.
For convenience, the full table for the 26 letters of the English alphabet is given below:
[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",
".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]

Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.

For example, "cab" can be written as "-.-..--...", which is the concatenation of "-.-.", ".-", and "-...". 
We will call such a concatenation the transformation of a word.

Return the number of different transformations among all words we have. 

Examples :-

Input: words = ["gin","zen","gig","msg"] __ Output: 2
Explanation: The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."
There are 2 different transformations: "--...-." and "--...--.".

Input: words = ["a"] __ Output: 1

Constraints :-
- 1 <= words.length <= 100
- 1 <= words[i].length <= 12
- words[i] consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// HashSet Approach : Time Complexity : O(n) __ Space Complexity : O(n)
int uniqueMorseRepresentations(vector<string>& words) {
    string morse[26] = {
        ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--",
        "-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
    };
    
    unordered_set<string> unique_codes;
    
    for (string& s : words) {
        string code = "";
        for (char& c : s)
            code += morse[c - 'a'];
        unique_codes.insert(code);
    }

    return unique_codes.size();
}

int main() {
    return 0;
}