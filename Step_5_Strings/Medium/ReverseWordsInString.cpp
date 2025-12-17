/*
Leetcode - 151. Reverse Words in a String : Medium

Given an input string s, reverse the order of the words.
A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words.
The returned string should only have a single space separating the words. Do not include any extra spaces.

Examples :-

Input: s = "the sky is blue" __ Output: "blue is sky the"

Input: s = "  hello world  " __ Output: "world hello"

Input: s = "a good   example" __ Output: "example good a"

Constraints :- 
- 1 <= s.length <= 10^4
- s contains English letters (upper-case and lower-case), digits, and spaces ' '.
- There is at least one word in s.

Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(n)
/*
Intuition: We just need to print the words in reverse order. Can we somehow store them in reverse order of the occurrence and
then simply add it to our answer?

Approach -
-- Use a stack to push all the words in a stack
-- Now, all the words of the string are present in the stack, but in reverse order
-- Pop elements of the stack one by one and add them to our answer variable. Remember to add a space between the words as well.
*/
string reverseWordsNaive(string s) {
    stack<string> words;
    string word;
    // push each word to the 'words' stack
    for (int i = 0; i < s.length(); i++)
    {
        // if current char != ' ' means the char is part of word so add it to the current word
        if (s[i] != ' ')
            word += s[i];
        // else, when space is encountered, push the word to the stack and empty the word string to gather new words
        else if (word.length() > 0) {
            words.push(word);
            word = "";
        }
    }
    if (word.length() > 0) words.push(word);            // add the last word to the stack

    string ans = "";
    while (words.size() != 1)
    {
        ans += words.top();
        words.pop();
        ans += " ";
    }
    ans += words.top();

    return ans;
}

// Same Logic as above but using Vector instead of stack
string reverseWordsNaiveVector(string s) {
    vector<string> words;
    string word;
    for (int i=0; i<s.length(); i++) {
        if (s[i] != ' ') 
            word += s[i];
        else if (word.length() > 0) {
            words.push_back(word);
            word = "";
        }
    }
    if (word.length() > 0) words.push_back(word);

    string ans = "";
    for (int i = words.size()-1; i > 0; i--) {
        ans += words[i] + " ";
    }
    ans += words[0];

    return ans;
}

// Reversal Approach :- Time Complexity : O(n) __ Space Complexity : O(n)
/*
Key idea
1. Reverse the entire string
• This puts the words in reverse order
• But each word itself becomes reversed
2. Traverse the reversed string word by word
• Extract each word
• Reverse that word again to fix its character order
• Add it to the answer
3. Skip extra spaces
• Only add valid words to the result
*/
void reverseX(string& s) {
    int i = 0, j = s.length() - 1;
    while (i < j)
        swap(s[i++], s[j--]);
}
string reverseWordsX(string s) {
    int n = s.length();
    string ans = "";
    reverseX(s);
    int i=0;
    while (i < n) {
        string word = "";
        while (i < n && s[i] != ' ') {
            word += s[i];
            i++;
        }
        if (word.length() > 0) {
            reverseX(word);
            ans += word + " ";
        } 
        i++;
    }
    ans.pop_back();
    return ans;
}

// Optimal Approach (Read-Write Pointer In-Place Technique) :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
✅ Intuition
| The goal is to reverse the order of words, not characters, while also removing extra spaces — and do it in-place.

Core idea
1. Reverse the entire string
    • This puts the words in the correct reversed order
    • But each word’s characters become reversed
2. Scan once using two pointers
    • j reads characters from the reversed string
    • i writes the cleaned result forward in the same string
3. For each word
    • Skip extra spaces
    • Copy the word forward
    • Reverse that word to fix its character order
    • Add exactly one space after it (if needed)
4. Trim the final length
    • Return only the valid part of the string

⚛️ Code Working & Explanation ⚛️
High-level idea
| Reverse the whole string → then rebuild it in-place word by word, fixing each word’s order and removing extra spaces.

Step 1: Reverse the entire string
    reverseString(s, 0, n - 1);
Example :- Input :  "  the   sky is  blue " __ After reverse : " eulb  si yks   eht  "
✔ Word order is now correct
❌ Letters inside words are reversed
❌ Extra spaces still exist

| Variable | Meaning                                      |
| -------- | -------------------------------------------- |
| `j`      | Reads characters from the reversed string    |
| `i`      | Writes the cleaned result in the same string |
| `start`  | Start index of current word (for reversing)  |
| `end`    | End index of current word                    |
👉 This is a read pointer (j) + write pointer (i) technique.

Step 2: Process the string word by word 
    while (j < n) {

>> 2.1 Skip extra spaces
    while (j < n && s[j] == ' ') j++;
    if (j == n) break;
Skips :
• Leading spaces
• Multiple spaces between words

>> 2.2 Mark where the word will start : start = i;
We remember this because we’ll reverse this word later.

>> 2.3 Copy the word forward
    while (j < n && s[j] != ' ') {
        s[i++] = s[j++];
    }
Example :- Reading: "eulb" __ Writing: "eulb"
✔ Word copied
❌ Still reversed → will fix next

>> 2.4 Reverse the current word
    end = i - 1;
    reverseString(s, start, end);
"eulb" → "blue" : Now the word is correct.

>> 2.5 Add single space (if needed)
    if (j < n) {
        s[i++] = ' ';
    }
✔ Ensures only one space between words
✔ Avoids trailing spaces

Step 3: Remove trailing space
    if (i > 0 && s[i - 1] == ' ') i--;
Just a safety cleanup.

Step 4: Return only valid portion
    return s.substr(0, i);
Because we modified the string in-place, the valid result is from 0 → i-1.

Why this works
    • Each character is touched once or twice → O(n)
    • No extra string or array → O(1) space
    • Extra spaces are automatically discarded while copying
*/
void reverse(string& s, int i, int j) {
    while (i < j)
        swap(s[i++], s[j--]);
}

string reverseWords(string s) {
    int n = s.length();
    reverse(s, 0, n-1);                     // Reverse the entire string

    int i = 0, j = 0, start = 0, end = 0;
    while (j < n) {
        // skip extra spaces - leading spaces & multiple spaces between words
        while (j < n && s[j] == ' ') j++;           
        if (j == n) break;       // if string has ended while skiping spaces, exit the loop

        start = i;               // start of the current word
        // copy the word forward
        while (j < n && s[j] != ' ') 
            s[i++] = s[j++];
        end = i - 1;            // end of the current word
        // Reverse the current word using start and end
        reverse(s, start, end); 

        // Add a space after the word if it's not the last word
        if (j < n) s[i++] = ' ';
    }

    // Remove trailing spaces if present
    if (i > 0 && s[i - 1] == ' ') i--;

    return s.substr(0, i);
}

int main() {
    string s = "a good   example";
    string reversed_words = reverseWords(s);
    cout << endl << reversed_words;

    return 0;
}