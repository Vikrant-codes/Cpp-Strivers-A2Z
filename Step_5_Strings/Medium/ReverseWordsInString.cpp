/*
Leetcode - 151. Reverse Words in a String : Medium

Given an input string s, reverse the order of the words.
A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words.
The returned string should only have a single space separating the words. Do not include any extra spaces.

Examples :-

Input: s = "the sky is blue"
Output: "blue is sky the"

Input: s = "  hello world  "
Output: "world hello"

Input: s = "a good   example"
Output: "example good a"

Constraints :- 1 <= s.length <= 10^4
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.

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
string reverseWordsNaive(string s)
{
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

// Another Approach :- Using Vector
string reverseWordsNaiveVector(string s) {
    vector<string> words;
    string word;
    for (int i=0; i<s.length(); i++) {
        char ch = s[i];
        if (ch != ' ') word += ch;
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

int main()
{
    string s = "I love C++ programming";
    string reversed_words = reverseWordsNaive(s);
    cout << reversed_words;

    return 0;
}