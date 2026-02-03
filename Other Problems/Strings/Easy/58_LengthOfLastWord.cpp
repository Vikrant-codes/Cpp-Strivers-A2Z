/*
Leetcode - 58. Length of Last Word : Easy

Given a string s consisting of words and spaces, return the length of the last word in the string.
A word is a maximal substring consisting of non-space characters only.

Examples :-

Input: s = "Hello World" __ Output: 5
Explanation: The last word is "World" with length 5.

Input: s = "   fly me   to   the moon  " __ Output: 4
Explanation: The last word is "moon" with length 4.

Input: s = "luffy is still joyboy" __ Output: 6
 
Constraints :-
1 <= s.length <= 10^4
s consists of only English letters and spaces ' '.
There will be at least one word in s.
*/

#include <bits/stdc++.h>
using namespace std;

// Reverse Traversal :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
💡 Intuition
We only care about the last word’s length, so instead of splitting the entire string, we:
1. Start from the end of the string. (pointer j = string.size - 1)
2. Skip trailing spaces (since the input might have traling spaces). To do so we decrement j until a non-space character is found
do while (s[j] == ' ') j--;  After this loop j will now point to the first non-space character.
3. Count characters of the last word until you hit another space (or start of string). 
Since j now points to the end of last word we can easily count length of last word by moving j. 
When j hits another space return length or
in case string only has one word, then return length after exiting the loop.

⚙️ Algorithm
1. Initialize pointer j = s.size() - 1.
2. While s[j] == ' ', decrement j to remove trailing spaces.
3. Initialize len = 0.
4. While j >= 0 and s[j] != ' ', increment len and decrement j.
5. Return len.

⏱️ Complexity Analysis
Time Complexity: O(n) (single backward pass through the string).
Space Complexity: O(1) (only a few variables used).
*/
int lengthOfLastWord(string s) {
    int j = s.size()-1;
    // Remove trailing spaces 
    while (s[j] == ' ') j--;
    
    int len = 0;
    while (j >= 0 && s[j] != ' ') {
        len++;
        j--;
    }
    return len;
}

int main() {

    return 0;
}