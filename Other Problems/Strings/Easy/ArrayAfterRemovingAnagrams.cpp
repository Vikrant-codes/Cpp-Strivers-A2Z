/*
Leetcode - 2273. Find Resultant Array After Removing Anagrams : Easy

You are given a 0-indexed string array words, where words[i] consists of lowercase English letters.
In one operation, select any index i such that 0 < i < words.length and words[i - 1] and words[i] are anagrams, 
and delete words[i] from words.
Keep performing this operation as long as you can select an index that satisfies the conditions.
Return words after performing all operations. 
It can be shown that selecting the indices for each operation in any arbitrary order will lead to the same result.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase using all the original letters 
exactly once. For example, "dacb" is an anagram of "abdc".

Examples :- 

Input: words = ["abba","baba","bbaa","cd","cd"] __ Output: ["abba","cd"]
Explanation:
One of the ways we can obtain the resultant array is by using the following operations:
- Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index 2 and delete words[2].
  Now words = ["abba","baba","cd","cd"].
- Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index 1 and delete words[1].
  Now words = ["abba","cd","cd"].
- Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2 and delete words[2].
  Now words = ["abba","cd"].
We can no longer perform any operations, so ["abba","cd"] is the final answer.

Input: words = ["a","b","c","d","e"] __ Output: ["a","b","c","d","e"]

Constraints :-
1 <= words.length <= 100
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Hashing Approach :- Time Complexity : O(N * L) {N = words.size(), L = average word length} __ Space Complexity : O(1)
/*
🧠 Intuition

We need to remove consecutive words that are anagrams of each other from the given list.
So, as we iterate:
- Compare the current word with the last word kept in our result.
- If they are not anagrams, keep it.
- If they are anagrams, skip it.
This ensures we only keep the first word from each anagram group that appears consecutively.

⚙️ Reasoning / Algorithm

1. Start with the first word in the result array (ans).
2. For each next word:
- Check if it’s an anagram of the last added word using areAnagrams().
- If not anagram → push it into ans.
- Else → skip it.
3. Return ans after processing all words.

The areAnagrams() helper: Uses a fixed-size freq[26] array to check whether two strings are anagrams or not.

⏱️ Time Complexity : O(N * L)
- O(N) to iterate through all the words of the string
- areAnagrams(string s1, string s2) :- O(L) where L is the word length of s1/s2.
- Total : O(N * L)

🌌 Space Complexity :  O(1) {ans vector is not considered as it is resultant vector, also hash vector used is of fixed size}
*/
bool areAnagrams(string s1, string s2){
    if (s1.size() != s2.size()) return false;

    vector<int> freq(26, 0);

    for (int i=0; i<s1.size(); i++) {
        int x = s1[i] - 'a';
        int y = s2[i] - 'a';
        freq[x]++; freq[y]--;
    }
    for (int x : freq) 
        if (x != 0) return false;
    return true;
}

vector<string> removeAnagrams(vector<string>& words) {
    vector<string> ans;
    ans.push_back(words[0]);

    for (int i=1; i<words.size(); i++) {
        if (!areAnagrams(ans.back(), words[i])) 
            ans.push_back(words[i]);
    }

    return ans;
}

int main(){
    return 0;
}