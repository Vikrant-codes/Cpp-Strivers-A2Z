/*
Leetcode - 2114. Maximum Number of Words Found in Sentences : Easy

A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
You are given an array of strings sentences, where each sentences[i] represents a single sentence.
Return the maximum number of words that appear in a single sentence.

Examples :-

Input: sentences = ["alice and bob love leetcode", "i think so too", "this is great thanks very much"]
Output: 6
Explanation: 
- The first sentence, "alice and bob love leetcode", has 5 words in total.
- The second sentence, "i think so too", has 4 words in total.
- The third sentence, "this is great thanks very much", has 6 words in total.
Thus, the maximum number of words in a single sentence comes from the third sentence, which has 6 words.

Input: sentences = ["please wait", "continue to fight", "continue to win"]
Output: 3
Explanation: It is possible that multiple sentences contain the same number of words. 
In this example, the second and third sentences (underlined) have the same number of words.


Constraints :-
• 1 <= sentences.length <= 100
• 1 <= sentences[i].length <= 100
• sentences[i] consists only of lowercase English letters and ' ' only.
• sentences[i] does not have leading or trailing spaces.
• All the words in sentences[i] are separated by a single space.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n * m) __ Space Complexity : O(1) , where n = size of sentences array, m = average sentence length
/*
Constraints Analysis :-
|   sentence does not have leading or trailing spaces & all words in a sentence are separated by a single space.
So, words have only a single space between them.

To find the maximum words in a sentence we can find the no. of words in each sentence and keep track of the maximum words
We know a word is continuous set of characters that don't have space in between them.
So, to find the words in a sentence we can simply count the spaces in the sentence and then the word count would be 
1 greater than the count of spaces (since sentence don't have leading/trailing spaces and single space between words)
*/

int mostWordsFound(vector<string>& sentences) {
    int ans = 0;
    for (string& sentence : sentences) {
        int spaces = 0;         // count spaces, no of words in sentences = spaces + 1
        for (char c : sentence) {
            if (c == ' ') spaces++;
        ans = max(ans, spaces + 1);
        }
    }
    return ans;
}

int main() {
    return 0;
}