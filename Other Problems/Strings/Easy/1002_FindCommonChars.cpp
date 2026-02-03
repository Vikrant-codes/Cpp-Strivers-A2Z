/*
Leetcode - 1002. Find Common Characters : Easy

Given a string array words, return an array of all chars that show up in all strings within the words (including duplicates).
You may return the answer in any order.

Examples :-

Input: words = ["bella","label","roller"] __ Output: ["e","l","l"]

Input: words = ["cool","lock","cook"] __ Output: ["c","o"]
 
Constraints :-
- 1 <= words.length <= 100
- 1 <= words[i].length <= 100
- words[i] consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Hashing Based Approach :- Time Complexity : O(n * m) __ Space Complexity : O(1)
/*
🔹 Problem Restated Simply
You are given a list of words.
You must find all characters that appear in every word, including duplicates.
Example:
["bella","label","roller"]
→ ["e","l","l"]

🧠 Intuition
We can find common characters between two words using one/two frequency arrays of size 26 (26 lowercase alphabets). 
We can store the frequencies of chars from word1 in one array and word2 in another then compare them to get common frequencies.
But here we are given an array of words and we need to find all characters that appear in every word, including duplicates.
We definitely can't use 'n' 26-sized arrays to store frequencies of each word so instead we try to do this in 2 arrays.
We firstly store the frequencies of chars of the 1st word in an array say temp1 or freq1.
Now, we iterate all the remaining words one by one and for each word:
We store the current word's characters' frequencies in another array say temp2 or freq2.
Then, we compare freq1 & freq2 vectors to get the common freq and store this common freq in freq1 array.
This is done because we want freq1 vector to have the final common frequencies. 
So while traversing we keep the common freq in freq1 vector.

This way we can store the frequencies of all the common characters from all words in freq1 vector.
Now, we build the ans vector containing common chars from the freq1 vector which contains freq for all common chars.
Return the ans vector.

🧾 Algorithm (Step-by-Step)
1. Convert the first word into a frequency array freq1.
2. For each remaining word:
    • Compute its frequency array freq2
    • Find common freq from freq1 & freq2 :- For each i in [0,1,...,25]: 
        freq1[i] = min(freq1[i], freq2[i])
3. For each character a to z : Add it to the answer freq1[i] times.
4. Return the answer.

⏱️ Complexity Analysis
Let:
• n = number of words
• m = average length of a word

🔹 Time Complexity
• Frequency for one word → O(m)
• For all words → O(n * m)
• Comparing 26 characters each time → O(26 * n) ≈ constant
✅ Total Time: O(n * m)

🔹 Space Complexity
• Frequency arrays → O(26) (constant)
• Output storage → depends on result
✅ Auxiliary Space: O(1)

🧩 One-Line Intuition
|    “For each character, we keep the minimum frequency across all words, 
|    because a character can appear in the result only as many times as it appears in every word.”
*/
// Helper function, returns the frequencies of chars of the current word 
vector<int> getFreq(string& s) {
    vector<int> freq(26);
    for (char c : s) freq[c-'a']++;
    return freq;
}

vector<string> commonChars(vector<string>& words) {
    vector<int> freq1 = getFreq(words[0]);
    for (int i=1; i<words.size(); i++) {
        vector<int> freq2 = getFreq(words[i]);
        // find commmon frequencies of freq1 & freq2 and store them in freq1
        for (int k=0; k<26; k++) {
            freq1[k] = min(freq1[k], freq2[k]); 
        }
    }
    vector<string> ans;
    for (int i=0; i<26; i++) {
        char c = 'a' + i;
        string s = "";
        s += c;
        while (freq1[i]--) {
            ans.push_back(s);
        }
    }
    return ans;
}

int main() {
    return 0;
}